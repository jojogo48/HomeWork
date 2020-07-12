#ifndef LLVMCODE_HPP
#define LLVMCODE_HPP
#include "y.tab.hpp"
#include <stack>
#include <typeinfo>
#include <llvm/ADT/StringRef.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/IR/IRPrintingPasses.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Bitcode/BitcodeReader.h>
#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/MCJIT.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/raw_ostream.h>
#include <system_error>
using namespace std;
using namespace llvm;

class CodeGenBlock;

static LLVMContext llvmContext;
static stack<CodeGenBlock *> blocks;
static Module *module;


class CodeGenBlock {
public:
    BasicBlock *block;
    Value *returnValue;
    map<string, Value *> locals;
    CodeGenBlock *parent;
};

void pushBlock(BasicBlock *block) 
{
       CodeGenBlock* tempCB = new CodeGenBlock();
       tempCB->returnValue = NULL;
       tempCB->block = block;
       if (blocks.size() == 0) {
           tempCB->parent = nullptr;
       } else {
	   tempCB->parent = blocks.top();
       }
       blocks.push(tempCB);
}

void popBlock() 
{
        CodeGenBlock *top = blocks.top();
        blocks.pop();
        delete top;
}


extern BlockNode *programBlock;
extern "C"{
	extern int yylex(void);
	extern FILE *yyin;
	//extern int yyparse();
}


static Value *findIdentifierValue( string name) {

    if (blocks.size()==0) {
        //cout << "Checking global" << endl;
        goto checkglobal;
    } else if (blocks.top()->locals.find(name) != blocks.top()->locals.end()) {

        return blocks.top()->locals.find(name)->second;
    } else {
        // Search in parent block.
        CodeGenBlock *parentBlock = blocks.top();
        while (parentBlock->parent != nullptr) {
            if (parentBlock->parent->locals.find(name) !=
                parentBlock->parent->locals.end()) {
                return parentBlock->parent->locals.find(name)->second;;
            }
            parentBlock = parentBlock->parent;

        }
    }
    checkglobal:
    GlobalVariable *gvar = module->getNamedGlobal(name);
    GlobalValue *gval = module->getNamedValue(name);

    if (gvar) {
        return gval;
    } else {
        cerr << "**** Error Undeclared Variable: " << name << endl;
        return nullptr;
    }

    cerr << "**** Error Undeclared Variable: " << name << endl;
    return nullptr;
}

static Type *typeOf(const string& name, bool isPtr) {
    //cout << "Getting the type of: " << name << endl;
    if (name.compare("long") == 0) {
        if (isPtr)
            return Type::getInt64PtrTy(llvmContext);
        return Type::getInt64Ty(llvmContext);
    } else if (name.compare("int") == 0) {
        if (isPtr)
            return Type::getInt32PtrTy(llvmContext);
        return Type::getInt32Ty(llvmContext);
    } else if ((name.compare("double") == 0) ||(name.compare("float") == 0)) {
        if (isPtr)
            return Type::getDoublePtrTy(llvmContext);
        return Type::getDoubleTy(llvmContext);
    } else if (name.compare("char") == 0) {
        if (isPtr)
            return Type::getInt8PtrTy(llvmContext);
        return Type::getInt8Ty(llvmContext);
    } else if (name.compare("void") == 0) {
        return Type::getVoidTy(llvmContext);
    } else if (name.compare("bool") == 0) {
        return Type::getInt1Ty(llvmContext);
    }
    return Type::getVoidTy(llvmContext);
}

string genIndent(int l)
{
	std::string str("");
	for(int  i=0;i<8*l;i++)
	{
		if(i%8==0)
		{
			str+="|";
		}else{
		str += " ";}
	}
	return str;
}

Value *ASTNode::codeGen(int l){return NULL;}

Value *BlockNode::codeGen(int l) 
{
    
    /*if(l==0)
	cout <<genIndent(l)<< "Program" << endl;
    else
    	cout <<genIndent(l)<< "BlockNode" << endl;*/
    StatementList::const_iterator it;
    Value *last = NULL;
  
    for (it = statements.begin(); it != statements.end(); it++) {
        //cout <<genIndent(l)<<"Generating code for " << typeid(**it).name() << endl;
        last = (**it).codeGen(l+1);
    }
   

    return last;
}

Value *UnaryOperatorNode::codeGen(int l) {
    std::cout<<genIndent(l-1)<<"|---" << "UnaryOperationNode ";

    switch (op) {
        case INC_OP: {
            cout << "++" << endl;
	    cout<<genIndent(l) <<"Is on left: "<<onleft<<endl;
            Value *lhsvali = lhs.codeGen(l+1);
            IRBuilder<> builder(blocks.top()->block);
            Value *inci = builder.CreateAdd(lhsvali, builder.getInt32(1), "");
            Value *stri = builder.CreateStore(inci, findIdentifierValue(((IdentifierNode *) &lhs)->name));
            if (onleft)
                return inci;
            return lhsvali;
        }
        case DEC_OP: {
            cout << "--" << endl;
	    cout<<genIndent(l) <<"Is on left: "<<onleft<<endl;
            Value *lhsvald = lhs.codeGen(l+1);
            IRBuilder<> builder(blocks.top()->block);
            Value *incd = builder.CreateSub(lhsvald, builder.getInt32(1), "");
            Value *strd = builder.CreateStore(incd, findIdentifierValue(((IdentifierNode *) &lhs)->name));
            if (onleft)
                return incd;
            return lhsvald;

        }
	case '!': {
	    cout<<"!"<<endl;
	    Value *lval = lhs.codeGen(l+1);
	    IRBuilder<> builder(blocks.top()->block);
    	    Instruction::BinaryOps instr;
	    instr = Instruction::Xor;
    	    Value *ret = BinaryOperator::Create(instr, lval,
                              ConstantInt::get(Type::getInt1Ty(llvmContext), 1, true), "", blocks.top()->block);
            return ret;
	}
        default:
            cerr << "UNARY OPERATOR NOT SUPPORTED" << endl;
    }
    return NULL;
}

Value *FunctionDeclarationNode::codeGen(int l) 
{
    cout<<genIndent(l-1)<<"|---"<<"FunctionDeclarationNode"<<endl;
    cout<<genIndent(l)<<"Name: "<< id.name<<endl;
    cout<<genIndent(l)<<"Type: "<<storageType->type->name<<endl;
    cout<<genIndent(l)<<"hasEllipsis: "<<hasEllipsis<<endl;
    /*cout <<genIndent(l)<< "isPtr: " << isPtr << endl;*/
    vector<Type*> argTypes;
    VariableList::const_iterator it;
    for(it = arguments.begin();it !=arguments.end();it++)
    {
	cout<<genIndent(l)<<"ArgType: "<<(**it).storageType->type->name<<endl;
	argTypes.push_back(typeOf((**it).storageType->type->name, (**it).isPtr));
    }
    FunctionType *ftype = FunctionType::get(typeOf((storageType->type)->name, isPtr),
                                            makeArrayRef(argTypes), hasEllipsis);
    GlobalValue::LinkageTypes lt;
    if (storageType->storage)
        lt = GlobalValue::ExternalLinkage;
    else
        lt =  GlobalValue::ExternalLinkage ;
    Function *function = Function::Create(ftype, lt, id.name.c_str(), module);
    function->setCallingConv(llvm::CallingConv::C);
    return function;
}

Value *BoolNode::codeGen(int l) 
{
    cout <<genIndent(l-1)<<"|---"<< "BoolNode " ;
    IRBuilder<> builder(blocks.top()->block);
    if (value){
	cout<<"true"<< endl;
        return builder.getTrue();}
    else{
        cout<<"false"<< endl;
        return builder.getFalse();}
}


Value *FunctionDefinitionNode::codeGen(int l) 
{
    cout <<genIndent(l-1)<<"|---"<< "Function Definition" << endl;

    cout <<genIndent(l)<< "Name: " << id.name << endl;
    cout <<genIndent(l)<< "Return Type: " << storageType->type->name << endl;
    cout<<genIndent(l)<<"hasEllipsis: "<<hasEllipsis<<endl;
    Function *function = module->getFunction(id.name.c_str());
    VariableList::const_iterator it;
    if (function == NULL) {
        vector<Type *> argTypes;

        for (it = arguments.begin(); it != arguments.end(); it++) {
	    cout<<genIndent(l)<<"Arg Name: "<<(**it).id.name<<endl;
	    cout<<genIndent(l)<<"Arg type: "<<(**it).storageType->type->name<<endl;
	    
            argTypes.push_back(typeOf((**it).storageType->type->name, (**it).isPtr));
        }
        FunctionType *ftype = FunctionType::get(typeOf(storageType->type->name, isPtr),
                                                makeArrayRef(argTypes), hasEllipsis);
        function = Function::Create(ftype,
                                    GlobalValue::ExternalLinkage ,
                                    id.name.c_str(),module);
	
    }

    BasicBlock *bblock = BasicBlock::Create(llvmContext, "entry", function, 0);
    pushBlock(bblock);


    Function::arg_iterator argsValues = function->arg_begin();
    Value *argumentValue;

    for (it = arguments.begin(); it != arguments.end(); it++) {
        (**it).codeGen(l+1);
        argumentValue = &*argsValues++;
        argumentValue->setName(((*it)->id.name).c_str());
        StoreInst *inst = new StoreInst(argumentValue, (blocks.top()->locals)[(*it)->id.name],
                                        false, bblock);
	
    }
    block.codeGen(l);
    ReturnInst::Create(llvmContext, blocks.top()->returnValue, blocks.top()->block);
    popBlock();
    return function;
}

Value * IntNode::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "IntNode"<< "   value: "<<value<< endl ;
    return ConstantInt::get(Type::getInt32Ty(llvmContext), value, true);
}

Value *WhileLoopNode::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "WhileLoop" << endl;
    Function *function = blocks.top()->block->getParent();

    BasicBlock *CondBB = BasicBlock::Create(llvmContext, "whlcond", function);
    BasicBlock *LoopBB = BasicBlock::Create(llvmContext, "whlloop");
    BasicBlock *AfterBB = BasicBlock::Create(llvmContext, "whlafter");

    function->getBasicBlockList().push_back(CondBB);
    function->getBasicBlockList().push_back(LoopBB);
    function->getBasicBlockList().push_back(AfterBB);

    BranchInst::Create(CondBB, blocks.top()->block);

    //comnd
    pushBlock(CondBB);
    cout<<genIndent(l)<<"Condition"<<endl;
    Value *startval = cond->codeGen(l+1);
    BranchInst::Create(LoopBB, AfterBB, startval, blocks.top()->block);
    popBlock();

    //loopblock
    pushBlock(LoopBB);
    cout<<genIndent(l)<<"LoopBlock"<<endl;
    Value *loopval = block->codeGen(l+1);
    BranchInst::Create(CondBB, blocks.top()->block);
    popBlock();
    //---------

    //afterbb
    pushBlock(AfterBB);

    return NULL;

}
Value *DoubleNode::codeGen(int l) {
    cout<<genIndent(l-1)<<"|---"<< "DoubleNode"<< "   value: "<<value<< endl ;
    return ConstantFP::get(Type::getDoubleTy(llvmContext), value);
}

Value * StringNode::codeGen(int l){
    cout<<genIndent(l-1)<<"|---"<< "StringNode"<< "   value: "<<value<< endl ;
    size_t pos = value.find("\\n");
    if(pos != string::npos)
         value.replace(pos,2,1,'\n');
    pos = value.find("\"");
    value.erase(pos,1);
    pos = value.find("\"");
    value.erase(pos,1);
    const char *constValue = value.c_str();
    llvm::Constant *format_const =
            llvm::ConstantDataArray::getString(llvmContext, constValue);
    llvm::GlobalVariable *var =
            new llvm::GlobalVariable(
                    *module, llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8),
                                                          strlen(constValue) + 1),
                    true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
    llvm::Constant *zero =
            llvm::Constant::getNullValue(llvm::IntegerType::getInt32Ty(llvmContext));
    std::vector<llvm::Constant *> indices;
    indices.push_back(zero);
    indices.push_back(zero);
    llvm::Constant *var_ref = llvm::ConstantExpr::getGetElementPtr(
            llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8), strlen(constValue) + 1),
            var, indices);

    return var_ref;
}


Value *ExprBoolNode::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "ExprBoolNode";
    IRBuilder<> builder(blocks.top()->block);
    switch (op) {
        case EQ_OP:
            cout<<" =="<<endl;
            return builder.CreateICmpEQ(lhs->codeGen(l+1), rhs->codeGen(l+1));
        case NE_OP:
	    cout<<" !="<<endl;
            return builder.CreateICmpNE(lhs->codeGen(l+1), rhs->codeGen(l+1));
        default:
            cout << "ERROR..." << endl;
            return nullptr;
    }
}

Value *IfNode::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "IFNODE" << endl;
    Function *function = blocks.top()->block->getParent();

    BasicBlock *thenBlock = BasicBlock::Create(llvmContext, "then", function);
    BasicBlock *elseBlock = BasicBlock::Create(llvmContext, "else");
    BasicBlock *mergeBlock = BasicBlock::Create(llvmContext, "cont");

    //function->getBasicBlockList().push_back(thenBlock);
    cout <<genIndent(l)<< "Condition:" << endl;
    Value *condValue;
    if(!isUnary)
    	 condValue= cond->codeGen(l+1);
    else
	 condValue = ucond->codeGen(l+1);
    
    if (falsecond != nullptr)
        BranchInst::Create(thenBlock, elseBlock, condValue, blocks.top()->block);
    else
        BranchInst::Create(thenBlock, mergeBlock, condValue,blocks.top()->block);

    // This is required so the the variables can be matched.
    cout <<genIndent(l)<< "True:" << endl;
    pushBlock(thenBlock);
    Value *thenValue = truecond->codeGen(l+1);
    BranchInst::Create(mergeBlock, blocks.top()->block);
    popBlock();

    // create else block
    if (falsecond != nullptr) {
        function->getBasicBlockList().push_back(elseBlock);
        // This is required so the the variables can be matched.
	cout <<genIndent(l)<< "False:" << endl;
        pushBlock(elseBlock);
        Value *elseValue = falsecond->codeGen(l+1);
        BranchInst::Create(mergeBlock, blocks.top()->block);
        popBlock();
    }

    // create PHI node
    function->getBasicBlockList().push_back(mergeBlock);
    pushBlock(mergeBlock);


    return NULL;
}

Value *VariableDeclaration::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "Variable declaration: " << endl;
    cout <<genIndent(l)<< "Var: Type: " << storageType->type->name << endl;
    cout <<genIndent(l)<< "Var: Name: " << id.name << endl;
    
    if (!(blocks.size() == 0)) {
        AllocaInst *alloc = new AllocaInst(typeOf(storageType->type->name, isPtr),0, id.name.c_str(),blocks.top()->block);
        if (blocks.top()->locals.find(id.name) == blocks.top()->locals.end()) {
            blocks.top()->locals[id.name] = alloc;
        }  else {
            cout<<"Variable Already defined";
	    exit(0);
        }
        if (assignmentExpr != NULL) {
            AssignmentNode assn(id, assignmentExpr, isPtr);
            assn.codeGen(l+1);
        }
        return alloc;
    } else {
        module->getOrInsertGlobal(id.name, typeOf(storageType->type->name, isPtr));
        GlobalVariable *gVar = module->getNamedGlobal(id.name);

        if (!storageType->storage) {
            gVar->setLinkage(GlobalValue::InternalLinkage);
        } else {
            gVar->setLinkage(GlobalValue::ExternalLinkage);
        }

        if (storageType && storageType->qualifier) {
//            if (storageType->qualifier->name.compare("const") == 0) {
            gVar->setConstant(true);
//            }
        }

        if (assignmentExpr != NULL) {
            AssignmentNode assn(id, assignmentExpr, isPtr);
            assn.codeGen(l+1);
        }
        return NULL;
    }

}

Value *AssignmentNode::codeGen(int l) {
    cout <<genIndent(l-1)<<"|---"<< "AssignmentNode " << endl;
    cout <<genIndent(l)<< "Name: " << getId().name << endl;

    Value *id_val;
    if (blocks.size()==0) {
        GlobalVariable *gvar = module->getNamedGlobal(getId().name);
        id_val = module->getNamedValue(getId().name);
        if (gvar) {
            cout <<genIndent(l)<< "It is global" << endl;
            if (!gvar->hasInitializer()) {
               // cout << "isptr: " << isPtr << endl;
              //  cout << assignmentExpr << endl;
              //  cout << "isptr: " << isPtr << endl;
                if (!isPtr) {
                    gvar->setInitializer(dyn_cast<Constant>(assignmentExpr->codeGen(l+1)));
                } else {
                    const char *constValue = ((IdentifierNode *) assignmentExpr)->name.c_str();;
                    llvm::Constant *format_const =
                            llvm::ConstantDataArray::getString(llvmContext, constValue);
                    llvm::GlobalVariable *var =
                            new llvm::GlobalVariable(
                                    *module, llvm::ArrayType::get(llvm::IntegerType::get(llvmContext, 8),strlen(constValue) + 1),true, llvm::GlobalValue::PrivateLinkage, format_const, ".str");
                    gvar->setInitializer(var);
                }
                return gvar;
            } 
        } else {
            std::cerr << "undeclared variable " << id.name << endl;
            return NULL;
        }
    }
  
    
    id_val = findIdentifierValue(getId().name); 
     
    if (id_val == nullptr)
        return NULL;
    IRBuilder<> builder(blocks.top()->block);
    LoadInst *loadInst = builder.CreateLoad(id_val, "");
    Value *inci;

    return new StoreInst(assignmentExpr->codeGen(l+1),
                         id_val, false, blocks.top()->block);
}

Value *BinaryOperatorNode::codeGen(int l) {
    
    std::cout <<genIndent(l-1)<<"|---"<< "Binary operation " ;
    IRBuilder<> builder(blocks.top()->block);
    Instruction::BinaryOps instr;
    switch (op) {
        case '+':
            cout<< "+" << endl;
            instr = Instruction::Add;
            goto math;
        case '-':
            cout<< "-" << endl;
            instr = Instruction::Sub;
            goto math;
        case '*':
            cout<< "*" << endl;
            instr = Instruction::Mul;
            goto math;
        case '/':
            cout<< "/" << endl;
            instr = Instruction::SDiv;
            goto math;
        case '%':
            cout<< "%" << endl;
            instr = Instruction::SRem;
            goto math;
        case '&':
            cout<< "&" << endl;
            instr = Instruction::And;
            goto math;
        case '|':
            cout<< "|" << endl;
            instr = Instruction::Or;
            goto math;
        case '^':
            cout<< "^" << endl;
            instr = Instruction::Xor;
            goto math;
	case NE_OP:
            cout<< "!=" << endl;
            return builder.CreateICmpNE(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        case EQ_OP:
            cout<< "==" << endl;
            return builder.CreateICmpEQ(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        case LE_OP:
            cout<< "<=" << endl;
            return builder.CreateICmpSLE(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        case GE_OP:
            cout<< ">=" << endl;
            return builder.CreateICmpSGE(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        case '>':
            cout<< ">" << endl;
            return builder.CreateICmpSGT(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        case '<':
            cout<< "<" << endl;
            return builder.CreateICmpSLT(lhs.codeGen(l+1), rhs.codeGen(l+1), "");
        default:
            cerr << "BINARY OPERATOR NOT SUPPORTED" << endl;
            ;
    }        

    math:
    Value *lval = lhs.codeGen(l+1);
    Value *rval = rhs.codeGen(l+1);

    Value *ret = BinaryOperator::Create(instr, lval,
                                        rval, "", blocks.top()->block);
    return ret;
}

Value *IdentifierNode::codeGen(int l) {
    std::cout <<genIndent(l-1)<<"|---"<< "IdentifierNode: " << name << endl;
    Value *ident_ptr = findIdentifierValue(name);
    if (ident_ptr == nullptr) {
        cerr << "Error: Variable is not defined" << endl;
	exit(1);
        return NULL;
    }
    return new LoadInst(ident_ptr, "", false, blocks.top()->block);
}


Value *ReturnStatementNode::codeGen(int l) {
    cout<<genIndent(l-1)<<"|---"<< "RETURN node: " << endl;
    if (expression != NULL) {
        Value *returnValue = expression->codeGen(l+1);
	if(blocks.size()==0){
            cerr<<"ERROR"<<endl;
		exit(1);
        }
        blocks.top()->returnValue = returnValue;
        return returnValue;
    } else
        return NULL;

}


Value *FunctionCallNode::codeGen(int l) {
   cout<<genIndent(l-1)<<"|---"<<"FunctionCallNode"<<endl;
   cout<<genIndent(l)<<"Name: "<<id.name<<endl;
   
   Function *function = module->getFunction(id.name.c_str());
   if (function == NULL) {
        std::cerr << genIndent(l)<< "no such function " << id.name << endl;
        return NULL;
   } 
   std::vector<Value *> args;
   ExpressionList::const_iterator it;

   for(it = arguments.begin();it != arguments.end();it++)
   {
	args.push_back((**it).codeGen(l+1));
   }
   
   CallInst *call = CallInst::Create(function, makeArrayRef(args), "",
                                      blocks.top()->block);
   return call;
}
Value *ForLoopNode::codeGen(int l) 
{
    cout <<genIndent(l-1)<<"|---"<< "Forloop " << endl;
    Function *function = blocks.top()->block->getParent();
    // declaration
    if (declaration != nullptr)
        declaration->codeGen(l+1);
    else if (expr_dec != nullptr)
        expr_dec->codeGen(l+1);

    BasicBlock *CondBB = BasicBlock::Create(llvmContext, "cond", function);
    BasicBlock *LoopBB = BasicBlock::Create(llvmContext, "loop");
    BasicBlock *ProgressBB = BasicBlock::Create(llvmContext, "progress");
    BasicBlock *AfterBB = BasicBlock::Create(llvmContext, "after");
    function->getBasicBlockList().push_back(LoopBB);
    function->getBasicBlockList().push_back(ProgressBB);
    function->getBasicBlockList().push_back(AfterBB);


    BranchInst::Create(CondBB, blocks.top()->block);

    //cond
    cout<<genIndent(l)<<"Condition"<<endl;
    pushBlock(CondBB);
    Value *startval = condition->codeGen(l+1);
    BranchInst::Create(LoopBB, AfterBB, startval, blocks.top()->block);
    popBlock();
    //


    //loopblock
    cout<<genIndent(l)<<"Loop"<<endl;
    pushBlock(LoopBB);
    Value *loopval = block->codeGen(l+1);
    BranchInst::Create(ProgressBB, blocks.top()->block);
    popBlock();
    
   


    //progress
    cout<<genIndent(l)<<"Progress"<<endl;
    pushBlock(ProgressBB);
    if (progress != NULL)
        progress->codeGen(l+1);
    BranchInst::Create(CondBB, blocks.top()->block);
    popBlock();
   
   

    pushBlock(AfterBB);

    
    return NULL;

}


int main(int argc, char **argv)
{
   	if (argc < 2) {
        	cout <<"Usage: Compiler <prog.c> <ll_file_out.ll>\n";
        	exit(1);
    	}
    	char const *filename = argv[1];
    	yyin = fopen(filename, "r");
    	assert(yyin);
    
	yyparse();

	std::error_code OutErrorInfo ,ok;

 	std::string str(argv[2]);
	llvm::StringRef ref(str);
	llvm::raw_fd_ostream rfo(ref, OutErrorInfo, llvm::sys::fs::F_None);
	if(OutErrorInfo != ok)
	{
		llvm::errs() << "Could not create file\n";
		exit(1);
	}else
	{
		llvm::outs()<<"Successful create\n";
	}	

	module = new Module("main", llvmContext);
	cout<<"Program"<<endl;
	programBlock->codeGen(0);

	module->print(rfo, nullptr);
	

	cout<<endl<<endl;

	return 0;
}

#endif
