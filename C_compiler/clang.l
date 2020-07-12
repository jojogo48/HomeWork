D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			[Ee][+-]?{D}+
FS			(f|F|l|L)
IS			(u|U|l|L)*

%{
#include  <cstdio>
#include  <cstdlib>
#include <iostream>
#include <string>
#include "programTree.hpp"
#include "y.tab.hpp"

#define SAVE_STR_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define SAVE_CHAR_TOKEN yylval.token = yytext[0]
#define SAVE_SYM_TOKEN(t)  yylval.token = t
extern "C"{
int yywrap(void);
int yylex(void);
int check_type();
extern void yyerror(const char *s);
void comment();
void count();
}



%}

%%
"/*"			{ comment(); }
"//".*                  { }
"auto"			{ count(); return(AUTO); }
"break"			{ count(); return(BREAK); }
"case"			{ count(); return(CASE); }
"const"			{ SAVE_STR_TOKEN; count(); return(CONST); }
"continue"		{ count(); return(CONTINUE); }
"default"		{ count(); return(DEFAULT); }
"do"			{ count(); return(DO); }
"else"			{ count(); return(ELSE); }
"enum"			{ count(); return(ENUM); }
"extern"		{ SAVE_STR_TOKEN; count(); return(EXTERN); }
"for"			{ count(); return(FOR); }
"goto"			{ count(); return(GOTO); }
"if"			{ count(); return(IF); }
"register"		{ count(); return(REGISTER); }
"return"		{ count(); return(RETURN); }
"sizeof"		{ count(); return(SIZEOF); }
"static"		{ count(); return(STATIC); }
"struct"		{ count(); return(STRUCT); }
"switch"		{ count(); return(SWITCH); }
"typedef"		{ count(); return(TYPEDEF); }
"union"			{ count(); return(UNION); }

"volatile"		{ SAVE_STR_TOKEN; count(); return(VOLATILE); }
"while"			{ count(); return(WHILE); }


"void"			{ SAVE_STR_TOKEN; count(); return(VOID); }
"char"			{ SAVE_STR_TOKEN; count(); return(CHAR); }
"short"			{ SAVE_STR_TOKEN; count(); return(SHORT); }
"int"			{ SAVE_STR_TOKEN; count(); return(INT); }
"long"			{ SAVE_STR_TOKEN; count(); return(LONG); }
"float"			{ SAVE_STR_TOKEN; count(); return(FLOAT); }
"double"		{ SAVE_STR_TOKEN; count(); return(DOUBLE); }
"signed"		{ SAVE_STR_TOKEN; count(); return(SIGNED); }
"unsigned"		{ SAVE_STR_TOKEN; count(); return(UNSIGNED); }
"bool"                  { SAVE_STR_TOKEN; return (BOOL); }
"true"                  { SAVE_STR_TOKEN; return B_CONSTANT;}
"false"                 { SAVE_STR_TOKEN; return B_CONSTANT;}
{L}({L}|{D})*		{ SAVE_STR_TOKEN; count(); return(IDENTIFIER); }

0[xX]{H}+{IS}?		{ SAVE_STR_TOKEN; count(); return(INT_CONSTANT); }
0{D}+{IS}?		{ SAVE_STR_TOKEN; count(); return(INT_CONSTANT); }
{D}+{IS}?		{ SAVE_STR_TOKEN; count(); return(INT_CONSTANT); }

L?'(\\.|[^\\'])+'	{ SAVE_STR_TOKEN; count(); return(CHAR_CONSTANT); }

{D}+{E}{FS}?		{ SAVE_STR_TOKEN; count(); return(FLOAT_CONSTANT); }
{D}*"."{D}+({E})?{FS}?	{ SAVE_STR_TOKEN; count(); return(FLOAT_CONSTANT); }
{D}+"."{D}*({E})?{FS}?	{ SAVE_STR_TOKEN; count(); return(FLOAT_CONSTANT); }



L?\"(\\.|[^\\"])*\"	{ SAVE_STR_TOKEN; count(); return(STRING_LITERAL); }

"..."			{ count(); return(ELLIPSIS); }
">>="			{ count(); return(RIGHT_ASSIGN); }
"<<="			{ count(); return(LEFT_ASSIGN); }
"+="			{ count(); return(ADD_ASSIGN); }
"-="			{ count(); return(SUB_ASSIGN); }
"*="			{ count(); return(MUL_ASSIGN); }
"/="			{ count(); return(DIV_ASSIGN); }
"%="			{ count(); return(MOD_ASSIGN); }
"&="			{ count(); return(AND_ASSIGN); }
"^="			{ count(); return(XOR_ASSIGN); }
"|="			{ count(); return(OR_ASSIGN); }
">>"			{ count(); return(RIGHT_OP); }
"<<"			{ count(); return(LEFT_OP); }
"++"			{ SAVE_SYM_TOKEN(INC_OP); count(); return(INC_OP); }
"--"			{ SAVE_SYM_TOKEN(DEC_OP); count(); return(DEC_OP); }
"->"			{ count(); return(PTR_OP); }
"&&"			{ SAVE_SYM_TOKEN(AND_OP);count(); return(AND_OP); }
"||"			{ SAVE_SYM_TOKEN(OR_OP); count(); return(OR_OP); }
"<="			{ SAVE_SYM_TOKEN(LE_OP); count(); return(LE_OP); }
">="			{ SAVE_SYM_TOKEN(GE_OP); count(); return(GE_OP); }
"=="			{ SAVE_SYM_TOKEN(EQ_OP); count(); return(EQ_OP); }
"!="			{ SAVE_SYM_TOKEN(NE_OP); count(); return(NE_OP); }
";"			{ count(); return(';'); }
("{"|"<%")		{ count(); return('{'); }
("}"|"%>")		{ count(); return('}'); }
","			{ count(); return(','); }
":"			{ count(); return(':'); }
"="			{ SAVE_CHAR_TOKEN; count(); return('='); }
"("			{ count(); return('('); }
")"			{ count(); return(')'); }
("["|"<:")		{ count(); return('['); }
("]"|":>")		{ count(); return(']'); }
"."			{ count(); return('.'); }
"&"			{ SAVE_CHAR_TOKEN; count(); return('&'); }
"!"			{ SAVE_CHAR_TOKEN; count(); return('!'); }
"-"			{ SAVE_CHAR_TOKEN; count(); return('-'); }
"+"			{ SAVE_CHAR_TOKEN; count(); return('+'); }
"*"			{ SAVE_CHAR_TOKEN; count(); return('*'); }
"/"			{ SAVE_CHAR_TOKEN; count(); return('/'); }
"%"			{ SAVE_CHAR_TOKEN; count(); return('%'); }
"<"			{ SAVE_CHAR_TOKEN; count(); return('<'); }
">"			{ SAVE_CHAR_TOKEN; count(); return('>'); }
"^"			{ SAVE_CHAR_TOKEN; count(); return('^'); }
"|"			{ SAVE_CHAR_TOKEN; count(); return('|'); }
"?"			{ count(); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* ignore bad characters */ }

%%

int yywrap()
{
	return(1);
}


void comment()
{
    int c;

    while ((c = yyinput()) != 0)
        if (c == '*')
        {
            while ((c = yyinput()) == '*')
                ;

            if (c == '/')
                return;

            if (c == 0)
                break;
        }
}


int column = 0;

void count()
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;
}


int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

/*
*	it actually will only return IDENTIFIER
*/
	SAVE_STR_TOKEN;
	return(IDENTIFIER);
}
