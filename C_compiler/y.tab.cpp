/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "clang.y"

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


#line 91 "y.tab.cpp"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 225 "y.tab.cpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  46
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   1187

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  88
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  65
/* YYNRULES -- Number of rules.  */
#define YYNRULES  209
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  338

#define YYUNDEFTOK  2
#define YYMAXUTOK   320


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,     2,     2,     2,    11,     5,     2,
      78,    79,     8,     7,    80,     9,     2,    10,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    82,    83,
      12,     6,    13,    81,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    86,     2,    87,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    84,     3,    85,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    14,    15,
      16,    17,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    69,    69,    73,    74,    84,    88,    92,    93,    94,
      98,    99,   100,   101,   102,   106,   107,   111,   112,   113,
     114,   129,   130,   131,   132,   136,   137,   138,   139,   143,
     144,   145,   149,   150,   151,   155,   156,   157,   158,   159,
     163,   164,   165,   168,   169,   172,   173,   177,   178,   182,
     183,   187,   188,   192,   193,   198,   199,   203,   204,   211,
     212,   213,   214,   215,   216,   217,   218,   219,   220,   221,
     225,   226,   230,   234,   235,   245,   246,   247,   248,   249,
     250,   254,   255,   259,   260,   268,   269,   270,   271,   272,
     276,   277,   278,   279,   280,   281,   282,   283,   284,   285,
     286,   287,   288,   292,   293,   294,   298,   299,   303,   304,
     308,   312,   313,   314,   315,   319,   320,   324,   325,   326,
     330,   331,   332,   336,   337,   341,   342,   346,   347,   351,
     352,   356,   357,   358,   359,   360,   365,   366,   370,   371,
     372,   373,   377,   378,   383,   384,   388,   389,   393,   394,
     395,   399,   400,   404,   405,   406,   410,   411,   412,   413,
     414,   415,   416,   417,   418,   422,   423,   424,   428,   429,
     433,   434,   435,   436,   437,   438,   442,   443,   444,   448,
     449,   453,   454,   457,   458,   462,   463,   467,   468,   472,
     473,   474,   478,   479,   480,   481,   482,   483,   487,   488,
     489,   490,   491,   495,   496,   500,   501,   505,   509,   510
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "'|'", "'^'", "'&'", "'='", "'+'", "'*'",
  "'-'", "'/'", "'%'", "'<'", "'>'", "LE_OP", "GE_OP", "INC_OP", "DEC_OP",
  "'!'", "EQ_OP", "NE_OP", "AND_OP", "OR_OP", "BOOL", "EXTERN",
  "IDENTIFIER", "VOID", "CHAR", "SHORT", "INT", "LONG", "FLOAT", "DOUBLE",
  "SIGNED", "UNSIGNED", "INT_CONSTANT", "FLOAT_CONSTANT", "CHAR_CONSTANT",
  "STRING_LITERAL", "SIZEOF", "B_CONSTANT", "CONST", "VOLATILE", "PTR_OP",
  "LEFT_OP", "RIGHT_OP", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN",
  "ADD_ASSIGN", "SUB_ASSIGN", "LEFT_ASSIGN", "RIGHT_ASSIGN", "AND_ASSIGN",
  "XOR_ASSIGN", "OR_ASSIGN", "TYPE_NAME", "TYPEDEF", "STATIC", "AUTO",
  "REGISTER", "STRUCT", "UNION", "ENUM", "ELLIPSIS", "CASE", "DEFAULT",
  "IF", "ELSE", "SWITCH", "WHILE", "DO", "FOR", "GOTO", "CONTINUE",
  "BREAK", "RETURN", "NOELSE", "'('", "')'", "','", "'?'", "':'", "';'",
  "'{'", "'}'", "'['", "']'", "$accept", "program", "primary_expression",
  "postfix_expression", "argument_expression_list", "unary_expression",
  "unary_operator", "multiplicative_expression", "additive_expression",
  "shift_expression", "relational_expression", "equality_expression",
  "unary_Equexpression", "and_expression", "exclusive_or_expression",
  "inclusive_or_expression", "logical_and_expression",
  "logical_or_expression", "conditional_expression",
  "assignment_expression", "assignment_operator", "expression",
  "constant_expression", "declaration", "declaration_specifiers",
  "init_declarator_list", "init_declarator", "storage_class_specifier",
  "type_specifier", "struct_or_union_specifier", "struct_or_union",
  "struct_declaration_list", "struct_declaration",
  "specifier_qualifier_list", "struct_declarator_list",
  "struct_declarator", "enum_specifier", "enumerator_list", "enumerator",
  "type_qualifier", "declarator", "direct_declarator", "pointer",
  "type_qualifier_list", "parameter_type_list", "parameter_list",
  "parameter_declaration", "identifier_list", "abstract_declarator",
  "direct_abstract_declarator", "initializer", "initializer_list",
  "statement", "labeled_statement", "block_item_list", "block_item",
  "compound_statement", "declaration_list", "expression_statement",
  "selection_statement", "iteration_statement", "jump_statement",
  "translation_unit", "external_declaration", "function_definition", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   124,    94,    38,    61,    43,    42,    45,
      47,    37,    60,    62,   258,   259,   260,   261,    33,   262,
     263,   264,   265,   266,   267,   268,   269,   270,   271,   272,
     273,   274,   275,   276,   277,   278,   279,   280,   281,   282,
     283,   284,   285,   286,   287,   288,   289,   290,   291,   292,
     293,   294,   295,   296,   297,   298,   299,   300,   301,   302,
     303,   304,   305,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   315,   316,   317,   318,   319,   320,    40,    41,
      44,    63,    58,    59,   123,   125,    91,    93
};
# endif

#define YYPACT_NINF (-216)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     814,    70,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
    -216,  -216,  -216,    22,    47,    48,  -216,    24,  1083,  1083,
    -216,    31,  -216,  1083,   918,   -63,   -14,   814,  -216,  -216,
    -216,  -216,    70,   -53,    -3,     4,  -216,  -216,   124,  -216,
       7,  -216,  -216,    -5,  1124,  -216,   288,  -216,    24,  -216,
     918,   959,    92,   -63,  -216,  -216,  -216,    -3,    61,    54,
    -216,  -216,    47,  -216,   471,  -216,  1124,  1124,   855,  -216,
      55,  1124,  -216,  -216,  -216,  -216,   791,   791,   752,     5,
    -216,  -216,  -216,  -216,  -216,   752,    16,    36,    43,    58,
     457,    62,   151,   123,   129,   645,   752,  -216,  -216,  -216,
       3,   583,   791,   186,    59,    14,   160,   180,  -216,   212,
     218,   223,   227,    35,  -216,  -216,   144,  -216,  -216,  -216,
     360,  -216,  -216,  -216,  -216,  -216,  -216,   244,  -216,  -216,
    -216,  -216,    45,   203,   204,  -216,   113,  -216,  -216,  -216,
    -216,   198,    84,   752,    -3,  -216,  -216,   471,  -216,  -216,
     872,  -216,  -216,  -216,   752,   154,  -216,   201,  -216,  -216,
    -216,  -216,   457,   205,   457,   752,   752,   752,   216,   543,
     215,  -216,  -216,  -216,   159,   161,  -216,  -216,   695,  -216,
    -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,  -216,
     752,  -216,   791,   791,   791,   791,   791,   791,   791,   791,
     791,   791,   791,   791,   791,   752,   752,   752,   752,   752,
     752,   752,  -216,  -216,  -216,   586,   173,  -216,    -4,  -216,
     -32,  -216,  1041,  -216,   274,  -216,  -216,  -216,  -216,  -216,
     103,  -216,  -216,    55,  -216,   752,  -216,   457,  -216,   176,
     178,   185,   222,   651,   651,  -216,  -216,  -216,  -216,   187,
    -216,  -216,  -216,  -216,  -216,   186,   186,    59,    59,    14,
      14,    14,    14,   160,   160,  -216,   212,   218,   223,   227,
     153,  -216,  -216,   224,   228,  -216,   214,   -32,  1000,   254,
    -216,  -216,  -216,   432,  -216,  -216,  -216,  -216,   457,   457,
     457,   752,   701,   746,  -216,   752,   752,  -216,  -216,  -216,
    -216,   229,  -216,   240,  -216,  -216,   234,  -216,  -216,   189,
     457,   194,   457,   196,  -216,  -216,  -216,  -216,   457,   226,
    -216,   457,  -216,   457,  -216,  -216,  -216,  -216
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,   138,    99,    86,   131,    90,    91,    92,    93,    94,
      95,    96,    97,    98,   127,   128,   102,    85,    87,    88,
      89,   106,   107,     0,     0,     0,   206,     0,    75,    77,
     100,     0,   101,    79,     0,   130,     0,     2,   203,   205,
     142,   140,   139,   122,     0,     0,     1,    73,     0,    81,
      83,    76,    78,   105,     0,    80,     0,   185,     0,   209,
       0,     0,     0,   129,   204,   143,   141,     0,   125,     0,
     123,   132,     0,    74,     0,   207,     0,   112,     0,   108,
       0,   114,    21,    23,    22,    24,     0,     0,     0,     3,
       4,     6,     5,     7,     8,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   187,   183,    10,
      17,    25,     0,    29,    32,    35,    40,    43,    45,    47,
      49,    51,    53,    55,    57,    70,     0,   181,   182,   170,
       0,   179,   171,   172,   173,   174,   175,    83,   186,   208,
     151,   137,   150,     0,   144,   146,     0,     3,   134,    25,
      72,     0,     0,     0,     0,   120,    82,     0,   165,    84,
       0,   111,   104,   109,     0,     0,   115,   117,   113,    18,
      19,    44,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   199,   200,   201,     0,     0,    13,    14,     0,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   188,   184,   180,     0,     0,   148,   153,   149,
     154,   135,     0,   136,     0,   133,   121,   126,   124,   168,
       0,   103,   118,     0,   110,     0,   176,     0,   178,     0,
       0,     0,     0,     0,     0,   198,   202,     9,    11,     0,
      15,    58,    26,    27,    28,    30,    31,    33,    34,    36,
      37,    38,    39,    41,    42,    46,    48,    50,    52,    54,
       0,    71,   161,     0,     0,   157,     0,   155,     0,     0,
     145,   147,   152,     0,   166,   116,   119,   177,     0,     0,
       0,     0,     0,     0,    12,     0,     0,   162,   156,   158,
     163,     0,   159,     0,   167,   169,   189,   191,   192,     0,
       0,     0,     0,     0,    16,    56,   164,   160,     0,     0,
     196,     0,   194,     0,   190,   193,   197,   195
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -216,  -216,  -216,  -216,  -216,   -61,  -216,    72,    73,     9,
      39,  -216,   -80,    94,   114,   115,   116,  -216,   -60,   -62,
    -216,  -100,   -59,   -17,     0,  -216,   262,  -216,   -36,  -216,
    -216,   260,   -64,   -12,  -216,    95,  -216,   270,   188,     8,
     -20,   -33,    29,  -216,  -215,  -216,   107,  -216,   118,   112,
    -133,  -216,   -84,  -216,  -216,   245,   127,  -216,  -135,  -216,
    -216,  -216,  -216,   315,  -216
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,   109,   110,   259,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     200,   126,   151,    26,    58,    48,    49,    28,    29,    30,
      31,    78,    79,    80,   165,   166,    32,    69,    70,    33,
      34,    35,    36,    42,   143,   144,   145,   146,   229,   230,
     159,   240,   128,   129,   130,   131,   132,    60,   133,   134,
     135,   136,    37,    38,    39
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      27,   149,   150,    63,    45,   184,   185,    50,   171,    40,
     283,     4,   158,    74,   163,    61,   178,    57,    77,   186,
     187,     4,    68,    62,   239,   169,   170,   149,    51,    52,
      41,    67,     1,    55,   149,   150,   173,    27,   137,   127,
      77,    77,    77,   138,   254,    77,   288,    43,    46,     4,
      65,   201,   137,     1,   289,     1,    53,   219,   207,   208,
     167,   142,    81,     1,    24,   161,   205,   153,   206,   168,
       4,    66,     4,   311,   225,   249,   250,   251,     1,    76,
       4,   188,   226,    71,    81,    81,    81,   172,   246,    81,
     248,    56,   149,   150,   237,   158,   163,    82,   174,    83,
      84,    85,    24,   149,   150,   242,    44,    47,    86,    87,
      88,    14,    15,   127,   175,    54,   220,   147,   302,   303,
     280,   176,   227,   225,    77,    24,   260,    90,    91,    92,
      93,   226,    94,    24,   154,   275,   177,   164,   261,   155,
     179,   262,   263,   264,   149,   149,   149,   149,   149,   149,
     149,   149,   149,   149,   149,   149,   149,   149,   149,   281,
     315,    59,   253,   297,   154,   149,   150,   286,    81,   236,
     106,   228,   209,   210,   211,   212,   180,    75,    82,   148,
      83,    84,    85,   293,   149,   150,   296,   139,   294,    86,
      87,    88,   233,   234,   202,    63,   203,   204,   147,   213,
     214,   319,   321,   323,    72,    45,   181,    73,    90,    91,
      92,    93,   182,    94,   316,   317,   318,   215,   269,   270,
     271,   272,   216,   167,   221,   142,   217,   222,   149,   150,
     313,   158,   142,   221,   243,   306,   330,   244,   332,   221,
     257,   221,   256,   324,   334,   149,   325,   336,   218,   337,
      74,   106,   273,   274,   228,   298,   221,   299,   221,    82,
     285,    83,    84,    85,   300,   221,   304,   305,   329,   221,
      86,    87,    88,   331,   221,   333,   221,   265,   266,   147,
     267,   268,   231,   245,   232,   235,   252,   247,   142,    90,
      91,    92,    93,    82,    94,    83,    84,    85,   255,   292,
     301,   309,   328,   307,    86,    87,    88,   308,   326,   335,
     276,     2,     3,    89,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    90,    91,    92,    93,   327,    94,    14,
      15,   277,   106,   278,   156,   279,   160,   152,   295,   291,
     287,   312,   238,   284,    16,    17,    18,    19,    20,    21,
      22,    23,    64,    95,    96,    97,     0,    98,    99,   100,
     101,   102,   103,   104,   105,    82,   106,    83,    84,    85,
       0,   107,    56,   108,     0,   224,    86,    87,    88,     0,
       0,     0,     0,     2,     3,    89,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    90,    91,    92,    93,     0,
      94,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,     0,    95,    96,    97,     0,    98,
      99,   100,   101,   102,   103,   104,   105,    82,   106,    83,
      84,    85,     0,   107,    56,   223,     0,     0,    86,    87,
      88,     0,     0,     0,     0,     0,     0,   147,     0,     0,
       0,     0,    82,     0,    83,    84,    85,    90,    91,    92,
      93,     0,    94,    86,    87,    88,    82,     0,    83,    84,
      85,     0,    89,     0,     0,     0,     0,    86,    87,    88,
       0,     0,    90,    91,    92,    93,   147,    94,     0,     0,
       0,     0,     0,     0,     0,     0,    90,    91,    92,    93,
     106,    94,     0,     0,     0,     0,   157,   314,     0,     0,
       0,     0,    95,    96,    97,     0,    98,    99,   100,   101,
     102,   103,   104,   105,     0,   106,     0,     0,     0,     0,
     107,    56,     0,     0,     0,     0,     0,     0,    82,   106,
      83,    84,    85,     0,     0,   157,     0,     0,     0,    86,
      87,    88,     0,     0,     0,     0,     2,     3,   147,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    90,    91,
      92,    93,     0,    94,    14,    15,     0,     0,     0,   189,
       0,     0,     0,     0,     1,     0,     0,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,     0,     0,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,   106,     0,     0,     0,     0,   107,    14,    15,   190,
     191,   192,   193,   194,   195,   196,   197,   198,   199,     0,
       0,     0,    16,    17,    18,    19,    20,    21,    22,    23,
      82,     0,    83,    84,    85,     0,    82,     0,    83,    84,
      85,    86,    87,    88,   225,   282,     0,    86,    87,    88,
     147,     0,   226,     0,     0,     0,   147,     0,     0,     0,
      90,    91,    92,    93,     0,    94,    90,    91,    92,    93,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
      82,     0,    83,    84,    85,     0,    82,     0,    83,    84,
      85,    86,    87,    88,     0,     0,     0,    86,    87,    88,
     147,     0,     0,   106,     0,     0,   147,     0,   183,   106,
      90,    91,    92,    93,   107,    94,    90,    91,    92,    93,
       0,    94,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    82,     0,    83,    84,    85,     0,    82,     0,    83,
      84,    85,    86,    87,    88,     0,     0,     0,    86,    87,
      88,   147,     0,   106,   258,     0,     0,   147,     0,   106,
     320,    90,    91,    92,    93,     0,    94,    90,    91,    92,
      93,     0,    94,     0,     0,     0,    82,     0,    83,    84,
      85,     0,     0,     0,     0,     0,     0,    86,    87,     0,
       0,     0,     0,     0,     0,     0,   147,     0,     0,     0,
       0,     0,     1,     0,   106,   322,    90,    91,    92,    93,
     106,    94,     0,     0,     0,     0,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   106,
      16,    17,    18,    19,    20,    21,    22,    23,     2,     0,
       0,     5,     6,     7,     8,     9,    10,    11,    12,    13,
       0,     0,    24,     0,     0,     2,    14,    15,     5,     6,
       7,     8,     9,    10,    11,    12,    13,     0,     0,     0,
       0,    16,     0,    14,    15,     0,    21,    22,    23,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
       0,     0,     0,    21,    22,    23,     0,     0,     0,     0,
     162,     2,     3,     0,     5,     6,     7,     8,     9,    10,
      11,    12,    13,     0,     0,     0,     0,   241,     0,    14,
      15,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    16,    17,    18,    19,    20,    21,
      22,    23,     2,     3,   140,     5,     6,     7,     8,     9,
      10,    11,    12,    13,     0,     0,     0,     0,     0,     0,
      14,    15,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    16,    17,    18,    19,    20,
      21,    22,    23,     2,     3,     0,     5,     6,     7,     8,
       9,    10,    11,    12,    13,     0,     0,     0,   141,     0,
       0,    14,    15,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    16,    17,    18,    19,
      20,    21,    22,    23,     2,     3,     0,     5,     6,     7,
       8,     9,    10,    11,    12,    13,     0,     0,     0,   310,
       0,     0,    14,    15,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    17,    18,
      19,    20,    21,    22,    23,   290,     2,     3,     0,     5,
       6,     7,     8,     9,    10,    11,    12,    13,     0,     0,
       0,     0,     0,     0,    14,    15,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      17,    18,    19,    20,    21,    22,    23,     2,     0,     0,
       5,     6,     7,     8,     9,    10,    11,    12,    13,     0,
       0,     0,     0,     0,     0,    14,    15,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      16,     0,     0,     0,     0,    21,    22,    23
};

static const yytype_int16 yycheck[] =
{
       0,    62,    62,    36,    24,   105,   106,    27,    88,     1,
     225,    25,    74,     6,    78,    78,   100,    34,    54,    16,
      17,    25,    25,    86,   157,    86,    87,    88,    28,    29,
       1,    84,     8,    33,    95,    95,    95,    37,    58,    56,
      76,    77,    78,    60,   179,    81,    78,    25,     0,    25,
      42,   112,    72,     8,    86,     8,    25,    22,    44,    45,
      80,    61,    54,     8,    78,    77,     7,     6,     9,    81,
      25,    42,    25,   288,    78,   175,   176,   177,     8,    84,
      25,    78,    86,    79,    76,    77,    78,    82,   172,    81,
     174,    84,   153,   153,   153,   157,   160,     5,    82,     7,
       8,     9,    78,   164,   164,   164,    84,    83,    16,    17,
      18,    41,    42,   130,    78,    84,    81,    25,   253,   254,
     220,    78,   142,    78,   160,    78,   188,    35,    36,    37,
      38,    86,    40,    78,    80,   215,    78,    82,   200,    85,
      78,   202,   203,   204,   205,   206,   207,   208,   209,   210,
     211,   212,   213,   214,   215,   216,   217,   218,   219,   221,
     293,    34,   179,   247,    80,   226,   226,   226,   160,    85,
      78,   142,    12,    13,    14,    15,    25,    50,     5,    87,
       7,     8,     9,    80,   245,   245,   245,    60,    85,    16,
      17,    18,    79,    80,     8,   228,    10,    11,    25,    19,
      20,   301,   302,   303,    80,   225,    83,    83,    35,    36,
      37,    38,    83,    40,   298,   299,   300,     5,   209,   210,
     211,   212,     4,   243,    80,   225,     3,    83,   289,   289,
     289,   293,   232,    80,    80,    82,   320,    83,   322,    80,
      79,    80,    83,   305,   328,   306,   306,   331,    21,   333,
       6,    78,   213,   214,   225,    79,    80,    79,    80,     5,
      87,     7,     8,     9,    79,    80,    79,    80,    79,    80,
      16,    17,    18,    79,    80,    79,    80,   205,   206,    25,
     207,   208,    79,    82,    80,    87,    70,    82,   288,    35,
      36,    37,    38,     5,    40,     7,     8,     9,    83,    25,
      78,    87,    68,    79,    16,    17,    18,    79,    79,    83,
     216,    23,    24,    25,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    87,    40,    41,
      42,   217,    78,   218,    72,   219,    76,    67,   243,   232,
     228,    87,   154,   225,    56,    57,    58,    59,    60,    61,
      62,    63,    37,    65,    66,    67,    -1,    69,    70,    71,
      72,    73,    74,    75,    76,     5,    78,     7,     8,     9,
      -1,    83,    84,    85,    -1,   130,    16,    17,    18,    -1,
      -1,    -1,    -1,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    -1,
      40,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    -1,    65,    66,    67,    -1,    69,
      70,    71,    72,    73,    74,    75,    76,     5,    78,     7,
       8,     9,    -1,    83,    84,    85,    -1,    -1,    16,    17,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,
      -1,    -1,     5,    -1,     7,     8,     9,    35,    36,    37,
      38,    -1,    40,    16,    17,    18,     5,    -1,     7,     8,
       9,    -1,    25,    -1,    -1,    -1,    -1,    16,    17,    18,
      -1,    -1,    35,    36,    37,    38,    25,    40,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    35,    36,    37,    38,
      78,    40,    -1,    -1,    -1,    -1,    84,    85,    -1,    -1,
      -1,    -1,    65,    66,    67,    -1,    69,    70,    71,    72,
      73,    74,    75,    76,    -1,    78,    -1,    -1,    -1,    -1,
      83,    84,    -1,    -1,    -1,    -1,    -1,    -1,     5,    78,
       7,     8,     9,    -1,    -1,    84,    -1,    -1,    -1,    16,
      17,    18,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    -1,    40,    41,    42,    -1,    -1,    -1,     6,
      -1,    -1,    -1,    -1,     8,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    -1,    -1,    23,
      24,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    78,    -1,    -1,    -1,    -1,    83,    41,    42,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,    -1,
      -1,    -1,    56,    57,    58,    59,    60,    61,    62,    63,
       5,    -1,     7,     8,     9,    -1,     5,    -1,     7,     8,
       9,    16,    17,    18,    78,    79,    -1,    16,    17,    18,
      25,    -1,    86,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      35,    36,    37,    38,    -1,    40,    35,    36,    37,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
       5,    -1,     7,     8,     9,    -1,     5,    -1,     7,     8,
       9,    16,    17,    18,    -1,    -1,    -1,    16,    17,    18,
      25,    -1,    -1,    78,    -1,    -1,    25,    -1,    83,    78,
      35,    36,    37,    38,    83,    40,    35,    36,    37,    38,
      -1,    40,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,     5,    -1,     7,     8,     9,    -1,     5,    -1,     7,
       8,     9,    16,    17,    18,    -1,    -1,    -1,    16,    17,
      18,    25,    -1,    78,    79,    -1,    -1,    25,    -1,    78,
      79,    35,    36,    37,    38,    -1,    40,    35,    36,    37,
      38,    -1,    40,    -1,    -1,    -1,     5,    -1,     7,     8,
       9,    -1,    -1,    -1,    -1,    -1,    -1,    16,    17,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    25,    -1,    -1,    -1,
      -1,    -1,     8,    -1,    78,    79,    35,    36,    37,    38,
      78,    40,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
      56,    57,    58,    59,    60,    61,    62,    63,    23,    -1,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      -1,    -1,    78,    -1,    -1,    23,    41,    42,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    -1,    -1,    -1,
      -1,    56,    -1,    41,    42,    -1,    61,    62,    63,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    -1,
      -1,    -1,    -1,    61,    62,    63,    -1,    -1,    -1,    -1,
      85,    23,    24,    -1,    26,    27,    28,    29,    30,    31,
      32,    33,    34,    -1,    -1,    -1,    -1,    85,    -1,    41,
      42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,    61,
      62,    63,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,    -1,
      41,    42,    84,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,    60,
      61,    62,    63,    23,    24,    -1,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    79,    -1,
      -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,    59,
      60,    61,    62,    63,    23,    24,    -1,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    -1,    -1,    -1,    79,
      -1,    -1,    41,    42,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    23,    24,    -1,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    -1,    -1,
      -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    56,
      57,    58,    59,    60,    61,    62,    63,    23,    -1,    -1,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    -1,
      -1,    -1,    -1,    -1,    -1,    41,    42,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      56,    -1,    -1,    -1,    -1,    61,    62,    63
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     8,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    41,    42,    56,    57,    58,    59,
      60,    61,    62,    63,    78,    89,   111,   112,   115,   116,
     117,   118,   124,   127,   128,   129,   130,   150,   151,   152,
     127,   130,   131,    25,    84,   128,     0,    83,   113,   114,
     128,   112,   112,    25,    84,   112,    84,   111,   112,   144,
     145,    78,    86,   129,   151,   127,   130,    84,    25,   125,
     126,    79,    80,    83,     6,   144,    84,   116,   119,   120,
     121,   127,     5,     7,     8,     9,    16,    17,    18,    25,
      35,    36,    37,    38,    40,    65,    66,    67,    69,    70,
      71,    72,    73,    74,    75,    76,    78,    83,    85,    90,
      91,    93,    94,    95,    96,    97,    98,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   109,   111,   140,   141,
     142,   143,   144,   146,   147,   148,   149,   128,   111,   144,
      25,    79,   112,   132,   133,   134,   135,    25,    87,    93,
     106,   110,   125,     6,    80,    85,   114,    84,   107,   138,
     119,   121,    85,   120,    82,   122,   123,   128,   121,    93,
      93,   100,    82,   110,    82,    78,    78,    78,   140,    78,
      25,    83,    83,    83,   109,   109,    16,    17,    78,     6,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     108,    93,     8,    10,    11,     7,     9,    44,    45,    12,
      13,    14,    15,    19,    20,     5,     4,     3,    21,    22,
      81,    80,    83,    85,   143,    78,    86,   128,   130,   136,
     137,    79,    80,    79,    80,    87,    85,   110,   126,   138,
     139,    85,   110,    80,    83,    82,   140,    82,   140,   109,
     109,   109,    70,   111,   146,    83,    83,    79,    79,    92,
     107,   107,    93,    93,    93,    95,    95,    96,    96,    97,
      97,    97,    97,    98,    98,   100,   101,   102,   103,   104,
     109,   107,    79,   132,   136,    87,   110,   137,    78,    86,
      64,   134,    25,    80,    85,   123,   110,   140,    79,    79,
      79,    78,   146,   146,    79,    80,    82,    79,    79,    87,
      79,   132,    87,   110,    85,   138,   140,   140,   140,   109,
      79,   109,    79,   109,   107,   106,    79,    87,    68,    79,
     140,    79,   140,    79,   140,    83,   140,   140
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    88,    89,    90,    90,    90,    90,    90,    90,    90,
      91,    91,    91,    91,    91,    92,    92,    93,    93,    93,
      93,    94,    94,    94,    94,    95,    95,    95,    95,    96,
      96,    96,    97,    97,    97,    98,    98,    98,    98,    98,
      99,    99,    99,   100,   100,   101,   101,   102,   102,   103,
     103,   104,   104,   105,   105,   106,   106,   107,   107,   108,
     108,   108,   108,   108,   108,   108,   108,   108,   108,   108,
     109,   109,   110,   111,   111,   112,   112,   112,   112,   112,
     112,   113,   113,   114,   114,   115,   115,   115,   115,   115,
     116,   116,   116,   116,   116,   116,   116,   116,   116,   116,
     116,   116,   116,   117,   117,   117,   118,   118,   119,   119,
     120,   121,   121,   121,   121,   122,   122,   123,   123,   123,
     124,   124,   124,   125,   125,   126,   126,   127,   127,   128,
     128,   129,   129,   129,   129,   129,   129,   129,   130,   130,
     130,   130,   131,   131,   132,   132,   133,   133,   134,   134,
     134,   135,   135,   136,   136,   136,   137,   137,   137,   137,
     137,   137,   137,   137,   137,   138,   138,   138,   139,   139,
     140,   140,   140,   140,   140,   140,   141,   141,   141,   142,
     142,   143,   143,   144,   144,   145,   145,   146,   146,   147,
     147,   147,   148,   148,   148,   148,   148,   148,   149,   149,
     149,   149,   149,   150,   150,   151,   151,   152,   152,   152
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     3,     4,     2,     2,     1,     3,     1,     2,     2,
       2,     1,     1,     1,     1,     1,     3,     3,     3,     1,
       3,     3,     1,     3,     3,     1,     3,     3,     3,     3,
       1,     3,     3,     1,     2,     1,     3,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     2,     3,     1,     2,     1,     2,     1,
       2,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     5,     4,     2,     1,     1,     1,     2,
       3,     2,     1,     2,     1,     1,     3,     1,     2,     3,
       4,     5,     2,     1,     3,     1,     3,     1,     1,     2,
       1,     1,     3,     4,     3,     4,     4,     3,     1,     2,
       2,     3,     1,     2,     1,     3,     1,     3,     2,     2,
       1,     1,     3,     1,     1,     2,     3,     2,     3,     3,
       4,     2,     3,     3,     4,     1,     3,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     4,     3,     1,
       2,     1,     1,     2,     3,     1,     2,     1,     2,     5,
       7,     5,     5,     7,     6,     7,     6,     7,     3,     2,
       2,     2,     3,     1,     2,     1,     1,     3,     3,     2
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 69 "clang.y"
                           { programBlock = (yyvsp[0].block); }
#line 1841 "y.tab.cpp"
    break;

  case 3:
#line 73 "clang.y"
                      {(yyval.expr) = new IdentifierNode(*(yyvsp[0].string));delete (yyvsp[0].string); }
#line 1847 "y.tab.cpp"
    break;

  case 4:
#line 75 "clang.y"
        {
		long val = atol((yyvsp[0].string)->c_str());
		if(val > 2147483647){
			(yyval.expr) = new LongNode(val);
		}else{
			(yyval.expr) = new IntNode(atoi((yyvsp[0].string)->c_str()));
	 	}
		delete (yyvsp[0].string);
	}
#line 1861 "y.tab.cpp"
    break;

  case 5:
#line 85 "clang.y"
        {
	(yyval.expr) = new CharNode(((yyvsp[0].string)->c_str())[1]);
	}
#line 1869 "y.tab.cpp"
    break;

  case 6:
#line 89 "clang.y"
        {
	(yyval.expr) = new DoubleNode(atof((yyvsp[0].string)->c_str())); delete (yyvsp[0].string);
	}
#line 1877 "y.tab.cpp"
    break;

  case 7:
#line 92 "clang.y"
                         {(yyval.expr) = new StringNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1883 "y.tab.cpp"
    break;

  case 8:
#line 93 "clang.y"
                      { (yyval.expr) = new BoolNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 1889 "y.tab.cpp"
    break;

  case 9:
#line 94 "clang.y"
                             {(yyval.expr)=(yyvsp[-1].expr);}
#line 1895 "y.tab.cpp"
    break;

  case 11:
#line 99 "clang.y"
                                     { (yyval.expr) = new FunctionCallNode(*(yyvsp[-2].expr)); }
#line 1901 "y.tab.cpp"
    break;

  case 12:
#line 100 "clang.y"
                                                             { (yyval.expr) = new FunctionCallNode(*(yyvsp[-3].expr), *(yyvsp[-1].exprvec)) ; }
#line 1907 "y.tab.cpp"
    break;

  case 13:
#line 101 "clang.y"
                                    {(yyval.expr) = new UnaryOperatorNode(*(yyvsp[-1].expr), (yyvsp[0].token), false);}
#line 1913 "y.tab.cpp"
    break;

  case 14:
#line 102 "clang.y"
                                    {(yyval.expr) = new UnaryOperatorNode(*(yyvsp[-1].expr), (yyvsp[0].token), false);}
#line 1919 "y.tab.cpp"
    break;

  case 15:
#line 106 "clang.y"
                                {(yyval.exprvec) = new ExpressionList(); (yyval.exprvec)->push_back((yyvsp[0].expr));}
#line 1925 "y.tab.cpp"
    break;

  case 16:
#line 107 "clang.y"
                                                             { (yyvsp[-2].exprvec)->push_back((yyvsp[0].expr));}
#line 1931 "y.tab.cpp"
    break;

  case 18:
#line 112 "clang.y"
                                  { (yyval.expr) = new UnaryOperatorNode(*(yyvsp[0].expr), (yyvsp[-1].token), true); }
#line 1937 "y.tab.cpp"
    break;

  case 19:
#line 113 "clang.y"
                                  { (yyval.expr) = new UnaryOperatorNode(*(yyvsp[0].expr), (yyvsp[-1].token), true); }
#line 1943 "y.tab.cpp"
    break;

  case 20:
#line 114 "clang.y"
                                          { 
         if(dynamic_cast<IntNode *>((yyvsp[0].expr))){
		 (yyval.expr) = new IntNode((yyvsp[-1].token), (yyvsp[0].expr)) ;
	 }else if(dynamic_cast<DoubleNode *>((yyvsp[0].expr))){
		 (yyval.expr) = new DoubleNode((yyvsp[-1].token), (yyvsp[0].expr)) ;
	 }else if(dynamic_cast<LongNode *>((yyvsp[0].expr))){
		 (yyval.expr) = new LongNode((yyvsp[-1].token), (yyvsp[0].expr)) ;
	 }else{
		 cout<<" ERRROR Here in parser\n";
		 exit(0);
	 }
	}
#line 1960 "y.tab.cpp"
    break;

  case 26:
#line 137 "clang.y"
                                                         {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1966 "y.tab.cpp"
    break;

  case 27:
#line 138 "clang.y"
                                                         {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1972 "y.tab.cpp"
    break;

  case 28:
#line 139 "clang.y"
                                                         {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1978 "y.tab.cpp"
    break;

  case 30:
#line 144 "clang.y"
                                                            {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1984 "y.tab.cpp"
    break;

  case 31:
#line 145 "clang.y"
                                                            {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1990 "y.tab.cpp"
    break;

  case 36:
#line 156 "clang.y"
                                                        { (yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 1996 "y.tab.cpp"
    break;

  case 37:
#line 157 "clang.y"
                                                        { (yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2002 "y.tab.cpp"
    break;

  case 38:
#line 158 "clang.y"
                                                        { (yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2008 "y.tab.cpp"
    break;

  case 39:
#line 159 "clang.y"
                                                        { (yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2014 "y.tab.cpp"
    break;

  case 41:
#line 164 "clang.y"
                                                          { (yyval.expr) = new ExprBoolNode( (yyvsp[-1].token), (yyvsp[-2].expr), (yyvsp[0].expr));}
#line 2020 "y.tab.cpp"
    break;

  case 42:
#line 165 "clang.y"
                                                          { (yyval.expr) = new ExprBoolNode( (yyvsp[-1].token), (yyvsp[-2].expr) , (yyvsp[0].expr));}
#line 2026 "y.tab.cpp"
    break;

  case 44:
#line 169 "clang.y"
                                   { (yyval.expr) = new UnaryOperatorNode(*(yyvsp[0].expr), (yyvsp[-1].token), true); }
#line 2032 "y.tab.cpp"
    break;

  case 46:
#line 173 "clang.y"
                                                 {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2038 "y.tab.cpp"
    break;

  case 48:
#line 178 "clang.y"
                                                     {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2044 "y.tab.cpp"
    break;

  case 50:
#line 183 "clang.y"
                                                              {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2050 "y.tab.cpp"
    break;

  case 52:
#line 188 "clang.y"
                                                                {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2056 "y.tab.cpp"
    break;

  case 54:
#line 193 "clang.y"
                                                             {(yyval.expr) = new BinaryOperatorNode(*(yyvsp[-2].expr), (yyvsp[-1].token), *(yyvsp[0].expr));}
#line 2062 "y.tab.cpp"
    break;

  case 57:
#line 203 "clang.y"
                                 {}
#line 2068 "y.tab.cpp"
    break;

  case 58:
#line 204 "clang.y"
                                                                    {
		(yyval.expr) = new AssignmentNode(*(yyvsp[-2].expr), (yyvsp[0].expr));
		((AssignmentNode *)(yyval.expr))->setOp((yyvsp[-1].token));
	}
#line 2077 "y.tab.cpp"
    break;

  case 73:
#line 234 "clang.y"
                                     {(yyval.stmt) = (yyvsp[-1].stmt);}
#line 2083 "y.tab.cpp"
    break;

  case 74:
#line 236 "clang.y"
        {
	if((new CHK_TYPE())->isFunc(*(yyvsp[-1].var_init)))
		(yyval.stmt) = new FunctionDeclarationNode(*(yyvsp[-2].var_stor), *(yyvsp[-1].var_init));
	else
		(yyval.stmt) = new VariableDeclaration(*(yyvsp[-2].var_stor), *(yyvsp[-1].var_init));
	}
#line 2094 "y.tab.cpp"
    break;

  case 75:
#line 245 "clang.y"
                                                { (yyval.var_stor) = new QualStorageTypeNode(); (yyval.var_stor)->setStorage((yyvsp[0].ident));}
#line 2100 "y.tab.cpp"
    break;

  case 76:
#line 246 "clang.y"
                                                         { (yyval.var_stor) = new QualStorageTypeNode(NULL, (yyvsp[-1].ident), (yyvsp[0].var_stor)); (yyval.var_stor)->setStorage((yyvsp[-1].ident));}
#line 2106 "y.tab.cpp"
    break;

  case 77:
#line 247 "clang.y"
                                                { (yyval.var_stor) = new QualStorageTypeNode(); (yyval.var_stor)->setType((yyvsp[0].ident)); }
#line 2112 "y.tab.cpp"
    break;

  case 78:
#line 248 "clang.y"
                                                { (yyvsp[0].var_stor)->setType((yyvsp[-1].ident));(yyval.var_stor) = (yyvsp[0].var_stor);}
#line 2118 "y.tab.cpp"
    break;

  case 79:
#line 249 "clang.y"
                                                { (yyval.var_stor) = new QualStorageTypeNode(); (yyval.var_stor)->setQualifier((yyvsp[0].ident));}
#line 2124 "y.tab.cpp"
    break;

  case 80:
#line 250 "clang.y"
                                                { (yyvsp[0].var_stor)->setQualifier((yyvsp[-1].ident)); (yyval.var_stor) =  (yyvsp[0].var_stor);}
#line 2130 "y.tab.cpp"
    break;

  case 81:
#line 254 "clang.y"
                          {}
#line 2136 "y.tab.cpp"
    break;

  case 83:
#line 259 "clang.y"
                     {}
#line 2142 "y.tab.cpp"
    break;

  case 84:
#line 261 "clang.y"
        {
	(yyval.var_init) = new AssignmentNode(*(yyvsp[-2].expr), (yyvsp[0].expr));
	(yyval.var_init)->setOp((yyvsp[-1].token));
	}
#line 2151 "y.tab.cpp"
    break;

  case 86:
#line 269 "clang.y"
                 { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string);  }
#line 2157 "y.tab.cpp"
    break;

  case 90:
#line 276 "clang.y"
               { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2163 "y.tab.cpp"
    break;

  case 91:
#line 277 "clang.y"
               { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2169 "y.tab.cpp"
    break;

  case 92:
#line 278 "clang.y"
                { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2175 "y.tab.cpp"
    break;

  case 93:
#line 279 "clang.y"
              { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2181 "y.tab.cpp"
    break;

  case 94:
#line 280 "clang.y"
               { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2187 "y.tab.cpp"
    break;

  case 95:
#line 281 "clang.y"
                { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2193 "y.tab.cpp"
    break;

  case 96:
#line 282 "clang.y"
                 { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2199 "y.tab.cpp"
    break;

  case 97:
#line 283 "clang.y"
                 { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2205 "y.tab.cpp"
    break;

  case 98:
#line 284 "clang.y"
                   { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2211 "y.tab.cpp"
    break;

  case 99:
#line 285 "clang.y"
               { (yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string); }
#line 2217 "y.tab.cpp"
    break;

  case 127:
#line 346 "clang.y"
                 {(yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string);}
#line 2223 "y.tab.cpp"
    break;

  case 128:
#line 347 "clang.y"
                   {(yyval.ident) = new IdentifierNode(*(yyvsp[0].string)); delete (yyvsp[0].string);}
#line 2229 "y.tab.cpp"
    break;

  case 129:
#line 351 "clang.y"
                                    { (yyvsp[0].common_dec)->setIsPtr(true); (yyval.expr) = (yyvsp[0].common_dec);}
#line 2235 "y.tab.cpp"
    break;

  case 130:
#line 352 "clang.y"
                            { (yyval.expr) = (yyvsp[0].common_dec);}
#line 2241 "y.tab.cpp"
    break;

  case 131:
#line 356 "clang.y"
                        {  (yyval.common_dec) = new AssignmentNode(new IdentifierNode(*(yyvsp[0].string))); delete (yyvsp[0].string);}
#line 2247 "y.tab.cpp"
    break;

  case 135:
#line 360 "clang.y"
                                                        {
		 (yyvsp[-1].identparam)->setId((yyvsp[-3].common_dec));
		 (yyval.common_dec) = (yyvsp[-1].identparam);

	 }
#line 2257 "y.tab.cpp"
    break;

  case 137:
#line 366 "clang.y"
                                     { (yyval.common_dec) =new NIdentifierParam(*(yyvsp[-2].common_dec),true); }
#line 2263 "y.tab.cpp"
    break;

  case 144:
#line 383 "clang.y"
                          { (yyval.identparam) = new NIdentifierParam(*(yyvsp[0].varvec));}
#line 2269 "y.tab.cpp"
    break;

  case 145:
#line 384 "clang.y"
                                      { (yyval.identparam) = new NIdentifierParam(*(yyvsp[-2].varvec)); (yyval.identparam)->setEllipsis(true);}
#line 2275 "y.tab.cpp"
    break;

  case 146:
#line 388 "clang.y"
                                {(yyval.varvec) = new VariableList(); (yyval.varvec)->push_back((yyvsp[0].var_decl));}
#line 2281 "y.tab.cpp"
    break;

  case 147:
#line 389 "clang.y"
                                                   { (yyvsp[-2].varvec)->push_back((yyvsp[0].var_decl));}
#line 2287 "y.tab.cpp"
    break;

  case 148:
#line 393 "clang.y"
                                             { (yyval.var_decl) = new VariableDeclaration(*(yyvsp[-1].var_stor), *(yyvsp[0].expr));}
#line 2293 "y.tab.cpp"
    break;

  case 173:
#line 436 "clang.y"
                              {}
#line 2299 "y.tab.cpp"
    break;

  case 174:
#line 437 "clang.y"
                              {}
#line 2305 "y.tab.cpp"
    break;

  case 175:
#line 438 "clang.y"
                         {}
#line 2311 "y.tab.cpp"
    break;

  case 179:
#line 448 "clang.y"
                     { (yyval.block) = new BlockNode(); (yyval.block)->statements.push_back((yyvsp[0].stmt)); }
#line 2317 "y.tab.cpp"
    break;

  case 180:
#line 449 "clang.y"
                                     { (yyvsp[-1].block)->statements.push_back((yyvsp[0].stmt)); }
#line 2323 "y.tab.cpp"
    break;

  case 181:
#line 453 "clang.y"
                      {}
#line 2329 "y.tab.cpp"
    break;

  case 182:
#line 454 "clang.y"
                    {}
#line 2335 "y.tab.cpp"
    break;

  case 183:
#line 457 "clang.y"
                   { (yyval.block) = new BlockNode(); }
#line 2341 "y.tab.cpp"
    break;

  case 184:
#line 458 "clang.y"
                                    { (yyval.block)  = (yyvsp[-1].block); }
#line 2347 "y.tab.cpp"
    break;

  case 187:
#line 467 "clang.y"
              {}
#line 2353 "y.tab.cpp"
    break;

  case 188:
#line 468 "clang.y"
                         {}
#line 2359 "y.tab.cpp"
    break;

  case 189:
#line 472 "clang.y"
                                                       { (yyval.stmt) = new IfNode((yyvsp[-2].expr),(yyvsp[0].block));}
#line 2365 "y.tab.cpp"
    break;

  case 190:
#line 473 "clang.y"
                                                         { (yyval.stmt) = new IfNode((yyvsp[-4].expr),(yyvsp[-2].block),(yyvsp[0].block)); }
#line 2371 "y.tab.cpp"
    break;

  case 192:
#line 478 "clang.y"
                                             {(yyval.stmt) = new WhileLoopNode((yyvsp[-2].expr),(yyvsp[0].block));}
#line 2377 "y.tab.cpp"
    break;

  case 194:
#line 480 "clang.y"
                                                                          {(yyval.stmt) = new ForLoopNode((yyvsp[-3].expr),(yyvsp[-2].expr),NULL,(yyvsp[0].block));}
#line 2383 "y.tab.cpp"
    break;

  case 195:
#line 481 "clang.y"
                                                                                     { (yyval.stmt) = new ForLoopNode((yyvsp[-4].expr),(yyvsp[-3].expr),(yyvsp[-2].expr),(yyvsp[0].block));}
#line 2389 "y.tab.cpp"
    break;

  case 196:
#line 482 "clang.y"
                                                                {(yyval.stmt) = new ForLoopNode((yyvsp[-3].stmt),(yyvsp[-2].expr),NULL,(yyvsp[0].block));}
#line 2395 "y.tab.cpp"
    break;

  case 197:
#line 483 "clang.y"
                                                                            {(yyval.stmt) = new ForLoopNode((yyvsp[-4].stmt),(yyvsp[-3].expr),(yyvsp[-2].expr),(yyvsp[0].block));}
#line 2401 "y.tab.cpp"
    break;

  case 201:
#line 490 "clang.y"
                      {(yyval.stmt) = new ReturnStatementNode();}
#line 2407 "y.tab.cpp"
    break;

  case 202:
#line 491 "clang.y"
                                {(yyval.stmt) = new ReturnStatementNode((yyvsp[-1].expr));}
#line 2413 "y.tab.cpp"
    break;

  case 203:
#line 495 "clang.y"
                                {(yyval.block)=new BlockNode(); (yyval.block)->statements.push_back((yyvsp[0].stmt)); }
#line 2419 "y.tab.cpp"
    break;

  case 204:
#line 496 "clang.y"
                                                {(yyvsp[-1].block)->statements.push_back((yyvsp[0].stmt));}
#line 2425 "y.tab.cpp"
    break;

  case 205:
#line 500 "clang.y"
                               {}
#line 2431 "y.tab.cpp"
    break;

  case 206:
#line 501 "clang.y"
                       {}
#line 2437 "y.tab.cpp"
    break;

  case 207:
#line 506 "clang.y"
        {
	(yyval.stmt) = new FunctionDefinitionNode(*(yyvsp[-2].var_stor), *(yyvsp[-1].expr), *(yyvsp[0].block));
	}
#line 2445 "y.tab.cpp"
    break;


#line 2449 "y.tab.cpp"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 513 "clang.y"

void yyerror(const char *s)
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}
