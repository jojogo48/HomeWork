#ifndef ProgramTree_HPP
#define ProgramTree_HPP
#include <iostream>
#include <vector>
#include <llvm/IR/Value.h>
#include <typeinfo>
#define llvmGen Value*codeGen(int l);
#define trav void traversal();
using namespace std;
using namespace llvm;

class CodeGenContext;

class StmtNode;

class ExprNode;

class VariableDeclaration;

typedef vector<StmtNode *> StatementList;
typedef vector<ExprNode *> ExpressionList;
typedef vector<VariableDeclaration *> VariableList;

class ASTNode 
{
public:
  virtual llvmGen
};

class StmtNode : public ASTNode 
{
};

class ExprNode : public ASTNode 
{
};

class IdentifierNode : public ExprNode
{
public:
	string name;
	IdentifierNode(const string &name):name(name){}
	IdentifierNode(ExprNode &idexpr):name(((const IdentifierNode &)idexpr).name) {}
	virtual llvmGen
};
class CommonDeclarationNode : public ExprNode {
public:
    bool isFunc = false;
    bool isPtr = false;

    void setIsPtr(bool isPtr) {
        CommonDeclarationNode::isPtr = isPtr;
    }

    void setIsFunc(bool isFunc) {
        CommonDeclarationNode::isFunc = isFunc;
    }

};

class BoolNode : public ExprNode {
public:
    bool value = false;

    BoolNode(string &name) {
        if (name.compare("true") == 0) {
            value = true;
        } else {
            value = false;
        }
    }

    BoolNode(bool val) {
        value = val;
    }

    virtual llvmGen
};



class BinaryOperatorNode : public ExprNode {
public:

    ExprNode &lhs;
    ExprNode &rhs;
    int op;
    BinaryOperatorNode(ExprNode &lhs, int op, ExprNode &rhs) :
            lhs(lhs), rhs(rhs), op(op) {
    }
    virtual llvmGen
    
};


class AssignmentNode : public CommonDeclarationNode {
    IdentifierNode *backup;
    IdentifierNode &id;
    bool isBackup = false;

public:
    ExprNode *assignmentExpr;
    int op;

    void setOp(int op) {
        AssignmentNode::op = op;
    }

    IdentifierNode &getId() {
        if (isBackup)
            return *backup;
        else
            return id;
    }

    AssignmentNode(IdentifierNode *identifier, bool _isPtr = false) :
        id(*identifier) {
        isPtr = _isPtr;
    }

    AssignmentNode(IdentifierNode &id, ExprNode *assignmentExpr, bool _isptr = false) :
            id(id), assignmentExpr(assignmentExpr) {
    isPtr = _isptr;
    }
	
    AssignmentNode(ExprNode &expression, ExprNode *assignmentExpr) :
            id(((AssignmentNode *) &expression)->id), assignmentExpr(assignmentExpr) {

        if (dynamic_cast<AssignmentNode *>(&expression)) {
            isPtr = ((AssignmentNode *) &expression)->isPtr;
        } else if (dynamic_cast<IdentifierNode *>(&expression)) {
            backup = ((IdentifierNode *) &expression);
            isBackup = true;     
        }
    }
    virtual llvmGen

};

class FunctionCallNode : public ExprNode {
public:
    const IdentifierNode &id;
    ExpressionList arguments;

    FunctionCallNode(const ExprNode &id, ExpressionList &arguments) :
            id((const IdentifierNode &) id), arguments(arguments) {}

    FunctionCallNode(const ExprNode &id) : id((const IdentifierNode &) id) {}

    virtual llvmGen
};

class UnaryOperatorNode:public ExprNode{
public:

    int op;
    ExprNode &lhs;
    bool onleft = false;

    UnaryOperatorNode(ExprNode &lhs, int op, bool _onleft = false) :
            lhs(lhs), op(op) 
    {
        onleft = _onleft;
    }
    
    virtual llvmGen
};



class DoubleNode : public ExprNode {
public:
    double value;

    DoubleNode(double value) : value(value) {/*cout << "DOUBLENODE: " << value << endl;*/}

    DoubleNode(int uop, ExprNode *exprNode) {
        value = ((DoubleNode *) exprNode)->value;
        switch (uop) {
            case '-':
                value = -1 * value;
            default:;
        }
    }
    virtual llvmGen
};

class CharNode : public ExprNode {
public:
    char value;
    CharNode(char value) : value(value) {/*cout << "CHARNODE: " << value << endl;*/}
};

class StringNode : public ExprNode {
public:
    string value;
    StringNode(string value) : value(value) {}
    virtual llvmGen
};

class IntNode : public ExprNode
{
public:
	int value;
	IntNode(int value):value(value){/*cout << "INTNODE: " << value << endl;*/}
	IntNode(int uop,ExprNode *exprNode)
	{
		value = ((IntNode*)exprNode)->value;
		switch(uop)
		{
			case '-':
			value = -1*value;
		default:;
		}
	}	
    	virtual llvmGen
};

class LongNode : public ExprNode {
public:
    long value;

    LongNode(long _value) : value(_value) { /*cout << "LongNode: " << value << endl;*/}

    LongNode(int uop, ExprNode *exprNode) {
        value = ((LongNode *) exprNode)->value;
        switch (uop) {
            case '-':
                value = -1 * value;
            default:;
        }
    }
};



class BlockNode:public ExprNode
{
public: 
	StatementList statements;
	BlockNode() {} 
	virtual llvmGen
};

class QualStorageTypeNode :public ExprNode
{
public:
	IdentifierNode *storage;
	IdentifierNode *type;
	IdentifierNode *qualifier;

    	QualStorageTypeNode() 
	{
        qualifier = NULL;
        storage = NULL;
        type = NULL;
    	}	
	
/*   	QualStorageTypeNode(IdentifierNode *qual, IdentifierNode *_stor, IdentifierNode *_type) :
            qualifier(qual), storage(_stor), type(_type) {
 
    	}*/


 	QualStorageTypeNode(IdentifierNode *qual, IdentifierNode *_stor, QualStorageTypeNode *_type) :
            qualifier(qual), storage(_stor), type(_type->type) {
        	if (_type->qualifier) {
            	qualifier = _type->qualifier;
        	}
    	}

	void setStorage(IdentifierNode *storage) 
	{
        QualStorageTypeNode::storage = storage;
	}

   	void setType(IdentifierNode *type) 
	{
        QualStorageTypeNode::type = type;
    	}

    	void setQualifier(IdentifierNode *qualifier) 
	{
        QualStorageTypeNode::qualifier = qualifier;
    	}
};


class NIdentifierParam : public CommonDeclarationNode {
public:
    IdentifierNode *id;
    VariableList arguments;
    bool ellipsis = false;

    void setEllipsis(bool ellipsis) {
        NIdentifierParam::ellipsis = ellipsis;
    }

    void setId(ExprNode *_id) {
        NIdentifierParam::id = &dynamic_cast<AssignmentNode *>(_id)->getId();
    }

    NIdentifierParam(const VariableList &_arguments) :
            arguments(_arguments) {
        isFunc = true;
    }

    NIdentifierParam(ExprNode &id, const bool _isF = false) :
            id(&((AssignmentNode *) &id)->getId()) {
        isFunc = _isF;
    }
};


class VariableDeclaration : public StmtNode {
public:
    bool isPtr = false;
    QualStorageTypeNode *storageType;
    IdentifierNode &id;
    ExprNode *assignmentExpr;

    VariableDeclaration(QualStorageTypeNode &storageType, ExprNode &assig) :
            storageType(&storageType),
            id(((AssignmentNode *) &assig)->getId()) 
    {
  	assignmentExpr = ((AssignmentNode *) &assig)->assignmentExpr;
        isPtr = ((AssignmentNode *) &assig)->isPtr;

        if (dynamic_cast<IntNode *>(assignmentExpr)) {
            if (storageType.type->name.compare("double") == 0) {
                cout << "Correction needed" << endl;
                assignmentExpr = new DoubleNode(((IntNode *) assignmentExpr)->value);
            }
        } else if (dynamic_cast<DoubleNode *>(assignmentExpr)) {
            if (storageType.type->name.compare("int") == 0) {
                cout << "Correction needed" << endl;
                assignmentExpr = new IntNode(((DoubleNode *) assignmentExpr)->value);
            }
        }
    }

    virtual llvmGen 
};

class FunctionDeclarationNode : public StmtNode {
public:
    bool isPtr = false;
    const IdentifierNode &id;
    QualStorageTypeNode *storageType;
    VariableList arguments;
    bool hasEllipsis = false;

    FunctionDeclarationNode(QualStorageTypeNode &type, ExprNode &assig) :
            id(*((NIdentifierParam *) &assig)->id),
            storageType(&type) {
        if (dynamic_cast<NIdentifierParam *>(&assig)) {
            arguments = ((NIdentifierParam *) &assig)->arguments;
            isPtr = ((NIdentifierParam *) &assig)->isPtr;
            hasEllipsis = ((NIdentifierParam *) &assig)->ellipsis;
        }
    }
    virtual llvmGen
};

class ExprBoolNode : public ExprNode {
public:
    ExprNode *lhs;
    ExprNode *rhs;
    int op;

    ExprBoolNode(int _op, ExprNode *_lhs, ExprNode *_rhs) {
        op = _op;
        lhs = _lhs;
        rhs = _rhs;
    }

    virtual llvmGen;
};

class IfNode : public StmtNode {
public:
    BlockNode *truecond;
    BlockNode *falsecond;
    ExprBoolNode *cond;
    UnaryOperatorNode *ucond;
    bool isUnary = false;

    IfNode(ExprNode *exprNode, BlockNode *true_blockNode, BlockNode *false_blockNode) {
        if (dynamic_cast<IntNode *>(exprNode)) {
            IntNode *intNode = dynamic_cast<IntNode *>(exprNode);
            if (intNode->value > 0) {
                cond = reinterpret_cast<ExprBoolNode *>(new BoolNode(true));
            } else {
                cond = reinterpret_cast<ExprBoolNode *>(new BoolNode(false));
            } 
        } else if(dynamic_cast<UnaryOperatorNode *>(exprNode)){
	    isUnary = true;
	    ucond = dynamic_cast<UnaryOperatorNode *>(exprNode);
	}else{
            cond = (ExprBoolNode *) exprNode;
        }
        truecond = true_blockNode;
        falsecond = false_blockNode;
    }

    IfNode(ExprNode *exprNode, BlockNode *true_blockNode) {
	if(dynamic_cast<ExprBoolNode *>(exprNode))
	{
	    cond = dynamic_cast<ExprBoolNode *>(exprNode);
        }else if(dynamic_cast<UnaryOperatorNode *>(exprNode))
	{
	    isUnary = true;
	    ucond = dynamic_cast<UnaryOperatorNode *>(exprNode);
	}
	truecond = true_blockNode;
        falsecond = nullptr;
    }

    virtual llvmGen
};

class ForLoopNode : public StmtNode {
public:
    StmtNode *declaration;
    ExprNode *expr_dec;
    ExprNode *condition;
    ExprNode *progress;
    BlockNode *block;

    ForLoopNode(ExprNode *expr_dec, ExprNode *condition,
                ExprNode *progress, BlockNode *block) : declaration(nullptr),expr_dec(
            expr_dec), condition(condition), progress(progress), block(block) {
    }

    ForLoopNode(StmtNode *declaration, ExprNode *condition,
                ExprNode *progress, BlockNode *block)
            : declaration(declaration),expr_dec(nullptr), condition(condition),
              progress(progress), block(block) {
    }

    virtual llvmGen

};


class FunctionDefinitionNode : public StmtNode {
public:
    bool isPtr = false;
    const IdentifierNode &id;
    VariableList arguments;
    BlockNode &block;
    QualStorageTypeNode *storageType;
    bool hasEllipsis = false;

    FunctionDefinitionNode(QualStorageTypeNode &type, ExprNode &idm, BlockNode &block) :
            id(*((NIdentifierParam *) &idm)->id),
            arguments(((NIdentifierParam *) &idm)->arguments),
            block(block) {

        storageType = &type;
        isPtr = ((NIdentifierParam *) &idm)->isPtr;
        hasEllipsis = ((NIdentifierParam *) &idm)->ellipsis;

    }
    virtual llvmGen
};

class CHK_TYPE {
public:
    static bool isFunc(ExprNode &assig) {
        return ((CommonDeclarationNode *) &assig)->isFunc;
    }
};

class ReturnStatementNode : public StmtNode {
public:
    ExprNode *expression;

    ReturnStatementNode() {
        expression = NULL;
    }

    ReturnStatementNode(ExprNode *vexpression) { expression = vexpression; }

    virtual llvmGen
};

class WhileLoopNode : public StmtNode {
public:
    ExprBoolNode *cond;
    BlockNode *block;


    WhileLoopNode(ExprNode *exprNode, BlockNode *_block) {
        cond = (ExprBoolNode *) exprNode;
        block = _block;
    }
    virtual llvmGen
};
#endif
