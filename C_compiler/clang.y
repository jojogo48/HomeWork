%{
#include <stdio.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include "programTree.hpp"
#include "llvmCode.hpp"
using namespace std;

extern char yytext[];
extern int column;
BlockNode *programBlock;
extern "C"{
	void yyerror(const char *s);
}

%}

%union {
	BlockNode *block;
	ExprNode *expr;
	StmtNode *stmt;
	IdentifierNode *ident;
	QualStorageTypeNode *var_stor;
	CommonDeclarationNode *common_dec;
	VariableDeclaration *var_decl;
	AssignmentNode *var_init;
	NIdentifierParam * identparam;
	std::vector<VariableDeclaration*> *varvec;
	std::vector<ExprNode*> *exprvec;
	std::string *string;
	int token;
} 
%token <token> '|' '^' '&' '=' '+' '*' '-' '/' '%'   '<' '>' LE_OP GE_OP INC_OP DEC_OP '!' EQ_OP  NE_OP AND_OP OR_OP
%token <string> BOOL EXTERN IDENTIFIER VOID CHAR SHORT INT LONG FLOAT DOUBLE SIGNED UNSIGNED INT_CONSTANT FLOAT_CONSTANT CHAR_CONSTANT STRING_LITERAL SIZEOF B_CONSTANT
 CONST  VOLATILE 
%token PTR_OP  LEFT_OP RIGHT_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF STATIC AUTO REGISTER
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <block> 	 	translation_unit block_item_list compound_statement statement
%type <stmt> 	 	iteration_statement selection_statement external_declaration block_item declaration function_definition jump_statement
%type <ident> 		type_specifier storage_class_specifier type_qualifier
%type <var_stor> 	declaration_specifiers
%type <common_dec> 	direct_declarator
%type <var_decl> 	parameter_declaration
%type <varvec>   	parameter_list
%type <identparam>   	parameter_type_list
%type <expr> 		expression_statement unary_Equexpression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression and_expression equality_expression unary_expression shift_expression  relational_expression postfix_expression declarator primary_expression expression initializer   assignment_expression multiplicative_expression additive_expression
%type <var_init>        init_declarator init_declarator_list
%type <exprvec>         argument_expression_list
%type <token> 		unary_operator assignment_operator 

%nonassoc NOELSE
%nonassoc ELSE


%start program
%%
program : translation_unit { programBlock = $1; };


primary_expression
	: IDENTIFIER  {$$ = new IdentifierNode(*$1);delete $1; }
	| INT_CONSTANT    
	{
		long val = atol($1->c_str());
		if(val > 2147483647){
			$$ = new LongNode(val);
		}else{
			$$ = new IntNode(atoi($1->c_str()));
	 	}
		delete $1;
	}
	|CHAR_CONSTANT
	{
	$$ = new CharNode(($1->c_str())[1]);
	}
	|FLOAT_CONSTANT
	{
	$$ = new DoubleNode(atof($1->c_str())); delete $1;
	}
	| STRING_LITERAL {$$ = new StringNode(*$1); delete $1; }
	| B_CONSTANT  { $$ = new BoolNode(*$1); delete $1; }
	| '(' expression ')' {$$=$2;}
	;

postfix_expression
	: primary_expression
	| postfix_expression '(' ')' { $$ = new FunctionCallNode(*$1); }
	| postfix_expression '(' argument_expression_list ')'{ $$ = new FunctionCallNode(*$1, *$3) ; }
	| postfix_expression INC_OP {$$ = new UnaryOperatorNode(*$1, $2, false);}
	| postfix_expression DEC_OP {$$ = new UnaryOperatorNode(*$1, $2, false);}
	;

argument_expression_list
	: assignment_expression {$$ = new ExpressionList(); $$->push_back($<expr>1);}
	| argument_expression_list ',' assignment_expression { $1->push_back($<expr>3);}
	;

unary_expression
	: postfix_expression
	| INC_OP unary_expression { $$ = new UnaryOperatorNode(*$2, $1, true); }
	| DEC_OP unary_expression { $$ = new UnaryOperatorNode(*$2, $1, true); }
	| unary_operator unary_expression { 
         if(dynamic_cast<IntNode *>($2)){
		 $$ = new IntNode($1, $2) ;
	 }else if(dynamic_cast<DoubleNode *>($2)){
		 $$ = new DoubleNode($1, $2) ;
	 }else if(dynamic_cast<LongNode *>($2)){
		 $$ = new LongNode($1, $2) ;
	 }else{
		 cout<<" ERRROR Here in parser\n";
		 exit(0);
	 }
	}
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	;

multiplicative_expression
	: unary_expression
	| multiplicative_expression '*' unary_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| multiplicative_expression '/' unary_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| multiplicative_expression '%' unary_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| additive_expression '-' multiplicative_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression	{ $$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| relational_expression '>' shift_expression	{ $$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| relational_expression LE_OP shift_expression	{ $$ = new BinaryOperatorNode(*$1, $2, *$3);}
	| relational_expression GE_OP shift_expression	{ $$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

equality_expression
	: relational_expression 
	| equality_expression EQ_OP relational_expression { $$ = new ExprBoolNode( $2, $1, $3);}
	| equality_expression NE_OP relational_expression { $$ = new ExprBoolNode( $2, $1 , $3);}
	;
unary_Equexpression
	: equality_expression
	| '!'  unary_Equexpression { $$ = new UnaryOperatorNode(*$2, $1, true); }
	;
and_expression
	: unary_Equexpression
	| and_expression '&' unary_Equexpression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression {$$ = new BinaryOperatorNode(*$1, $2, *$3);}
	;


conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression {}
	| unary_expression assignment_operator assignment_expression{
		$$ = new AssignmentNode(*$1, $3);
		((AssignmentNode *)$$)->setOp($2);
	}
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';' {$$ = $<stmt>1;} /*can clear*/
	| declaration_specifiers init_declarator_list ';' 
	{
	if((new CHK_TYPE())->isFunc(*$2))
		$$ = new FunctionDeclarationNode(*$1, *$2);
	else
		$$ = new VariableDeclaration(*$1, *$2);
	}
	;

declaration_specifiers
	: storage_class_specifier               { $$ = new QualStorageTypeNode(); $$->setStorage($1);}
	| storage_class_specifier declaration_specifiers { $$ = new QualStorageTypeNode(NULL, $1, $2); $$->setStorage($1);}
	| type_specifier 			{ $$ = new QualStorageTypeNode(); $$->setType($1); }
	| type_specifier declaration_specifiers { $2->setType($1);$$ = $2;}
	| type_qualifier 			{ $$ = new QualStorageTypeNode(); $$->setQualifier($1);}
	| type_qualifier declaration_specifiers { $2->setQualifier($1); $$ =  $2;}
	;

init_declarator_list
	: init_declarator {}
	| init_declarator_list ',' init_declarator
	;

init_declarator
	: declarator {}
	| declarator '=' initializer 
	{
	$$ = new AssignmentNode(*$1, $3);
	$$->setOp($2);
	}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN { $$ = new IdentifierNode(*$1); delete $1;  }
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID { $$ = new IdentifierNode(*$1); delete $1; }
	| CHAR { $$ = new IdentifierNode(*$1); delete $1; }
	| SHORT { $$ = new IdentifierNode(*$1); delete $1; }
	| INT { $$ = new IdentifierNode(*$1); delete $1; }
	| LONG { $$ = new IdentifierNode(*$1); delete $1; }
	| FLOAT { $$ = new IdentifierNode(*$1); delete $1; }
	| DOUBLE { $$ = new IdentifierNode(*$1); delete $1; }
	| SIGNED { $$ = new IdentifierNode(*$1); delete $1; }
	| UNSIGNED { $$ = new IdentifierNode(*$1); delete $1; }
        | BOOL { $$ = new IdentifierNode(*$1); delete $1; }
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier 
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST  {$$ = new IdentifierNode(*$1); delete $1;}
	| VOLATILE {$$ = new IdentifierNode(*$1); delete $1;}
	;

declarator
	: pointer direct_declarator { $2->setIsPtr(true); $$ = $2;}
	| direct_declarator { $$ = $1;}
	;

direct_declarator
	: IDENTIFIER	{  $$ = new AssignmentNode(new IdentifierNode(*$1)); delete $1;}
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')' {
		 $3->setId($1);
		 $$ = $3;

	 }
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'  { $$ =new NIdentifierParam(*$1,true); }
	;

pointer
	: '*' 
	| '*' type_qualifier_list 
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list  { $$ = new NIdentifierParam(*$1);}
	| parameter_list ',' ELLIPSIS { $$ = new NIdentifierParam(*$1); $$->setEllipsis(true);}
	;

parameter_list
	: parameter_declaration {$$ = new VariableList(); $$->push_back($1);}
	| parameter_list ',' parameter_declaration { $1->push_back($3);}
	;

parameter_declaration
	: declaration_specifiers declarator  { $$ = new VariableDeclaration(*$1, *$2);}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement {}
	| iteration_statement {}
	| jump_statement {}
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

block_item_list
	: block_item { $$ = new BlockNode(); $$->statements.push_back($1); }
	| block_item_list block_item { $1->statements.push_back($2); }
	;

block_item
	: declaration {}
	| statement {}
	;
compound_statement
	: '{' '}'  { $$ = new BlockNode(); }
	| '{'  block_item_list '}'  { $$  = $2; }
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

expression_statement
	: ';' {}
	| expression ';' {}
	;

selection_statement
	: IF '(' expression ')' statement %prec NOELSE { $$ = new IfNode($3,$5);}
	| IF '(' expression ')' statement ELSE statement { $$ = new IfNode($3,$5,$7); }
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement {$$ = new WhileLoopNode($3,$5);}
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement {$$ = new ForLoopNode($3,$4,NULL,$6);}
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new ForLoopNode($3,$4,$5,$7);}
	| FOR '(' declaration expression_statement ')' statement{$$ = new ForLoopNode($3,$4,NULL,$6);}
	| FOR '(' declaration expression_statement expression ')' statement {$$ = new ForLoopNode($3,$4,$5,$7);}
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'  {$$ = new ReturnStatementNode();}
	| RETURN expression ';' {$$ = new ReturnStatementNode($2);}
	;

translation_unit
	: external_declaration  {$$=new BlockNode(); $$->statements.push_back($1); }
	| translation_unit external_declaration {$1->statements.push_back($2);}
	;

external_declaration
	: function_definition  {}
	| declaration  {}
	;

function_definition
	: declaration_specifiers declarator compound_statement  
	{
	$$ = new FunctionDefinitionNode(*$1, *$2, *$3);
	}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%
void yyerror(const char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
