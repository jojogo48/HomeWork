/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    LE_OP = 258,
    GE_OP = 259,
    INC_OP = 260,
    DEC_OP = 261,
    EQ_OP = 262,
    NE_OP = 263,
    AND_OP = 264,
    OR_OP = 265,
    BOOL = 266,
    EXTERN = 267,
    IDENTIFIER = 268,
    VOID = 269,
    CHAR = 270,
    SHORT = 271,
    INT = 272,
    LONG = 273,
    FLOAT = 274,
    DOUBLE = 275,
    SIGNED = 276,
    UNSIGNED = 277,
    INT_CONSTANT = 278,
    FLOAT_CONSTANT = 279,
    CHAR_CONSTANT = 280,
    STRING_LITERAL = 281,
    SIZEOF = 282,
    B_CONSTANT = 283,
    CONST = 284,
    VOLATILE = 285,
    PTR_OP = 286,
    LEFT_OP = 287,
    RIGHT_OP = 288,
    MUL_ASSIGN = 289,
    DIV_ASSIGN = 290,
    MOD_ASSIGN = 291,
    ADD_ASSIGN = 292,
    SUB_ASSIGN = 293,
    LEFT_ASSIGN = 294,
    RIGHT_ASSIGN = 295,
    AND_ASSIGN = 296,
    XOR_ASSIGN = 297,
    OR_ASSIGN = 298,
    TYPE_NAME = 299,
    TYPEDEF = 300,
    STATIC = 301,
    AUTO = 302,
    REGISTER = 303,
    STRUCT = 304,
    UNION = 305,
    ENUM = 306,
    ELLIPSIS = 307,
    CASE = 308,
    DEFAULT = 309,
    IF = 310,
    ELSE = 311,
    SWITCH = 312,
    WHILE = 313,
    DO = 314,
    FOR = 315,
    GOTO = 316,
    CONTINUE = 317,
    BREAK = 318,
    RETURN = 319,
    NOELSE = 320
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 22 "clang.y"

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

#line 139 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
