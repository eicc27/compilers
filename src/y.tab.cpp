/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "parser.yacc"

#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  yywrap();
}


#line 86 "y.tab.cpp"

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

#include "y.tab.hpp"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ADD = 3,                        /* ADD  */
  YYSYMBOL_SUB = 4,                        /* SUB  */
  YYSYMBOL_MUL = 5,                        /* MUL  */
  YYSYMBOL_DIV = 6,                        /* DIV  */
  YYSYMBOL_SEMICOLON = 7,                  /* SEMICOLON  */
  YYSYMBOL_INT = 8,                        /* INT  */
  YYSYMBOL_FN = 9,                         /* FN  */
  YYSYMBOL_LET = 10,                       /* LET  */
  YYSYMBOL_STRUCT = 11,                    /* STRUCT  */
  YYSYMBOL_ARROW = 12,                     /* ARROW  */
  YYSYMBOL_RETURN = 13,                    /* RETURN  */
  YYSYMBOL_AND = 14,                       /* AND  */
  YYSYMBOL_OR = 15,                        /* OR  */
  YYSYMBOL_NOT = 16,                       /* NOT  */
  YYSYMBOL_EQ = 17,                        /* EQ  */
  YYSYMBOL_NEQ = 18,                       /* NEQ  */
  YYSYMBOL_GE = 19,                        /* GE  */
  YYSYMBOL_LE = 20,                        /* LE  */
  YYSYMBOL_GT = 21,                        /* GT  */
  YYSYMBOL_LT = 22,                        /* LT  */
  YYSYMBOL_IDENTIFIER = 23,                /* IDENTIFIER  */
  YYSYMBOL_INT_LITERAL = 24,               /* INT_LITERAL  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_COLON = 26,                     /* COLON  */
  YYSYMBOL_LPAREN = 27,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 28,                    /* RPAREN  */
  YYSYMBOL_LBRACKET = 29,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 30,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 31,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 32,                    /* RBRACE  */
  YYSYMBOL_COMMA = 33,                     /* COMMA  */
  YYSYMBOL_DOT = 34,                       /* DOT  */
  YYSYMBOL_CONTINUE = 35,                  /* CONTINUE  */
  YYSYMBOL_BREAK = 36,                     /* BREAK  */
  YYSYMBOL_IF = 37,                        /* IF  */
  YYSYMBOL_ELSE = 38,                      /* ELSE  */
  YYSYMBOL_WHILE = 39,                     /* WHILE  */
  YYSYMBOL_NEG = 40,                       /* NEG  */
  YYSYMBOL_YYACCEPT = 41,                  /* $accept  */
  YYSYMBOL_Program = 42,                   /* Program  */
  YYSYMBOL_ProgramElementList = 43,        /* ProgramElementList  */
  YYSYMBOL_ProgramElement = 44,            /* ProgramElement  */
  YYSYMBOL_ArithExpr = 45,                 /* ArithExpr  */
  YYSYMBOL_ArrayExpr = 46,                 /* ArrayExpr  */
  YYSYMBOL_MemberExpr = 47,                /* MemberExpr  */
  YYSYMBOL_ArithUExpr = 48,                /* ArithUExpr  */
  YYSYMBOL_ExprUnit = 49,                  /* ExprUnit  */
  YYSYMBOL_StructDef = 50,                 /* StructDef  */
  YYSYMBOL_VarDeclList = 51,               /* VarDeclList  */
  YYSYMBOL_VarDeclStmt = 52,               /* VarDeclStmt  */
  YYSYMBOL_Type = 53,                      /* Type  */
  YYSYMBOL_VarDecl = 54,                   /* VarDecl  */
  YYSYMBOL_BoolBiOpExpr = 55,              /* BoolBiOpExpr  */
  YYSYMBOL_BoolUOpExpr = 56,               /* BoolUOpExpr  */
  YYSYMBOL_ComExpr = 57,                   /* ComExpr  */
  YYSYMBOL_BoolUnit = 58,                  /* BoolUnit  */
  YYSYMBOL_BoolExpr = 59,                  /* BoolExpr  */
  YYSYMBOL_RightVal = 60,                  /* RightVal  */
  YYSYMBOL_LeftVal = 61,                   /* LeftVal  */
  YYSYMBOL_AssignStmt = 62,                /* AssignStmt  */
  YYSYMBOL_RightValList = 63,              /* RightValList  */
  YYSYMBOL_FnCall = 64,                    /* FnCall  */
  YYSYMBOL_VarDefScalar = 65,              /* VarDefScalar  */
  YYSYMBOL_VarDefArray = 66,               /* VarDefArray  */
  YYSYMBOL_VarDef = 67,                    /* VarDef  */
  YYSYMBOL_ParamDecl = 68,                 /* ParamDecl  */
  YYSYMBOL_FnDecl = 69,                    /* FnDecl  */
  YYSYMBOL_FnDeclStmt = 70,                /* FnDeclStmt  */
  YYSYMBOL_CallStmt = 71,                  /* CallStmt  */
  YYSYMBOL_IfStmt = 72,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 73,                 /* WhileStmt  */
  YYSYMBOL_ReturnStmt = 74,                /* ReturnStmt  */
  YYSYMBOL_CodeBlockStmt = 75,             /* CodeBlockStmt  */
  YYSYMBOL_CodeBlockStmtList = 76,         /* CodeBlockStmtList  */
  YYSYMBOL_CodeBlock = 77,                 /* CodeBlock  */
  YYSYMBOL_FnDef = 78                      /* FnDef  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
typedef yytype_uint8 yy_state_t;

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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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
#define YYFINAL  23
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   218

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  178

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   295


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   109,   109,   116,   121,   126,   130,   134,   138,   142,
     149,   153,   157,   161,   165,   170,   173,   175,   178,   183,
     187,   192,   197,   201,   205,   209,   213,   217,   221,   226,
     231,   235,   240,   244,   249,   253,   258,   262,   266,   270,
     275,   279,   284,   289,   293,   297,   301,   305,   309,   314,
     318,   322,   327,   331,   336,   340,   345,   349,   353,   359,
     364,   368,   373,   377,   382,   386,   391,   395,   399,   403,
     408,   412,   417,   422,   426,   430,   435,   440,   445,   449,
     453,   458,   463,   468,   472,   476,   480,   484,   488,   492,
     496,   500,   504,   509,   513,   518,   522,   527
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "ADD", "SUB", "MUL",
  "DIV", "SEMICOLON", "INT", "FN", "LET", "STRUCT", "ARROW", "RETURN",
  "AND", "OR", "NOT", "EQ", "NEQ", "GE", "LE", "GT", "LT", "IDENTIFIER",
  "INT_LITERAL", "ASSIGN", "COLON", "LPAREN", "RPAREN", "LBRACKET",
  "RBRACKET", "LBRACE", "RBRACE", "COMMA", "DOT", "CONTINUE", "BREAK",
  "IF", "ELSE", "WHILE", "NEG", "$accept", "Program", "ProgramElementList",
  "ProgramElement", "ArithExpr", "ArrayExpr", "MemberExpr", "ArithUExpr",
  "ExprUnit", "StructDef", "VarDeclList", "VarDeclStmt", "Type", "VarDecl",
  "BoolBiOpExpr", "BoolUOpExpr", "ComExpr", "BoolUnit", "BoolExpr",
  "RightVal", "LeftVal", "AssignStmt", "RightValList", "FnCall",
  "VarDefScalar", "VarDefArray", "VarDef", "ParamDecl", "FnDecl",
  "FnDeclStmt", "CallStmt", "IfStmt", "WhileStmt", "ReturnStmt",
  "CodeBlockStmt", "CodeBlockStmtList", "CodeBlock", "FnDef", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-90)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-59)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     167,   -90,    -5,    16,    21,    50,   -90,   167,   -90,   -90,
       3,   -90,   -90,    42,   135,    76,   -90,    41,   -13,   -90,
     -90,    78,    66,   -90,   -90,   -90,    83,   -90,    58,    68,
       5,   131,    87,    85,     5,   -90,   168,   121,   -90,    58,
     -90,   143,   107,   -90,   100,   132,   145,   152,   -90,   -90,
     146,   -90,   186,   -90,   -90,   -90,   -90,    10,   162,   -15,
     139,   -90,   163,   169,    90,    68,   107,   -90,    68,   184,
      48,    74,   -90,   164,   -90,   -90,   -90,   -90,   116,   -90,
     -90,   -90,   -90,   170,   171,   172,   -90,   105,   173,   174,
     175,   -90,   176,   -90,   192,   129,   -90,   -90,    68,    68,
      68,   -90,   -90,   -90,     5,     5,    58,   188,    90,   -90,
     164,   -90,    26,    84,    90,    90,    90,    90,    90,    90,
      90,    90,    90,    90,    68,    68,    68,   -90,   -90,   -90,
     177,   179,   178,   -90,   -90,   -90,   -90,   -90,   185,   110,
     112,   196,   -90,   -90,   -90,     5,   -90,   -90,   -90,   157,
     157,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   -90,   116,
     116,   -90,    68,   -90,   119,   -90,   181,   181,   -90,   -90,
     -90,   -90,   182,   180,   -90,   -90,   181,   -90
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     9,     0,     0,     0,     0,     2,     4,     6,     5,
       0,     7,     8,     0,    38,    57,    58,     0,     0,    71,
      70,     0,     0,     1,     3,    76,     0,    97,    73,     0,
       0,     0,     0,     0,     0,    32,     0,     0,    33,     0,
      84,     0,    56,    95,     0,     0,     0,     0,    57,    85,
       0,    86,     0,    87,    88,    89,    90,    94,     0,    38,
      39,    72,    30,     0,     0,     0,    23,    22,     0,    54,
      27,    26,    28,    14,    52,    51,    49,    53,    55,    65,
      25,    34,    35,    36,     0,     0,    19,     0,    37,     0,
       0,    20,     0,    83,     0,     0,    91,    92,     0,     0,
       0,    77,    93,    96,     0,     0,     0,    74,     0,    21,
       0,    42,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    16,    15,    69,
      60,     0,     0,    18,    17,    29,    82,    63,     0,     0,
       0,     0,    36,    37,    31,     0,    14,    24,    50,    10,
      11,    12,    13,    47,    48,    46,    44,    45,    43,    40,
      41,    64,     0,    68,     0,    62,     0,     0,    59,    75,
      61,    67,     0,    78,    81,    66,    80,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -90,   -90,   199,   -90,   -28,    -2,    -1,   -90,   -57,   -90,
     -30,   -22,   -34,   204,   -90,   -90,   -90,   150,   -46,   -26,
     -21,   -90,   -89,   -14,   -90,   -90,   -90,   -90,   -90,   -90,
     -90,   -90,   -90,   -90,   -90,   159,   -18,   -90
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,     6,     7,    69,    70,    71,    72,    73,     8,
      61,     9,    83,    62,    74,    75,    76,    77,    78,   130,
      18,    51,   131,    80,    19,    20,    21,    63,    10,    11,
      53,    54,    55,    56,    57,    58,    27,    12
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      88,    15,    16,    79,    49,    50,   138,   109,   110,    92,
      25,   104,    52,    81,    31,    94,    36,    40,    13,    32,
       3,    37,   113,    41,    48,    16,    60,    16,    82,   114,
     115,   116,   117,    42,    26,    49,    50,    60,    16,    14,
     112,   110,   110,    52,    22,    44,    45,    46,    35,    47,
      23,   146,   139,   140,   147,    48,    16,   146,   146,   146,
     146,   153,   154,   155,   156,   157,   158,   110,   110,    28,
     142,   143,    64,   170,   141,   172,   144,   -57,   159,   160,
     112,    59,   -57,   -39,    65,    38,   149,   150,   151,   152,
      40,    66,    67,     3,    64,    68,    41,    39,   124,   125,
     161,    33,    34,   -58,    60,    16,    42,    96,   -58,    64,
      86,   169,   148,    66,    67,    43,    87,   108,    44,    45,
      46,    65,    47,    64,   124,   125,   124,   125,    66,    67,
     124,   125,    68,    64,    95,    65,    31,   129,   166,    97,
     167,    32,    66,    67,    91,    65,    68,    64,   173,   174,
      93,   171,    66,    67,    84,    85,    68,   137,   177,    65,
      29,    30,   116,   117,    31,   105,    66,    67,   -57,    32,
      68,   100,    98,   -57,     1,    36,     2,     3,     4,    99,
      37,   118,   119,   120,   121,   122,   123,   114,   115,   116,
     117,    89,    90,   101,   103,   126,   106,   107,   132,   136,
     145,   127,   128,   168,   133,   134,    24,    17,   135,   164,
     162,   163,    26,   165,   175,   111,   102,     0,   176
};

static const yytype_int16 yycheck[] =
{
      34,     3,     3,    29,    26,    26,    95,    64,    65,    39,
       7,    26,    26,     8,    29,    41,    29,     7,    23,    34,
      10,    34,    68,    13,    26,    26,    28,    28,    23,     3,
       4,     5,     6,    23,    31,    57,    57,    39,    39,    23,
      68,    98,    99,    57,    23,    35,    36,    37,     7,    39,
       0,   108,    98,    99,    28,    57,    57,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,    27,
     104,   105,     4,   162,   100,   164,   106,    29,   124,   125,
     108,    23,    34,     7,    16,     7,   114,   115,   116,   117,
       7,    23,    24,    10,     4,    27,    13,    31,    14,    15,
     126,    25,    26,    29,   106,   106,    23,     7,    34,     4,
      23,   145,    28,    23,    24,    32,    31,    27,    35,    36,
      37,    16,    39,     4,    14,    15,    14,    15,    23,    24,
      14,    15,    27,     4,    27,    16,    29,    32,    28,     7,
      28,    34,    23,    24,    23,    16,    27,     4,   166,   167,
       7,    32,    23,    24,    23,    24,    27,    28,   176,    16,
      25,    26,     5,     6,    29,    26,    23,    24,    29,    34,
      27,    25,    27,    34,     7,    29,     9,    10,    11,    27,
      34,    17,    18,    19,    20,    21,    22,     3,     4,     5,
       6,    23,    24,     7,    32,    25,    33,    28,    25,     7,
      12,    30,    30,     7,    30,    30,     7,     3,    32,    31,
      33,    32,    31,    28,    32,    65,    57,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    10,    11,    42,    43,    44,    50,    52,
      69,    70,    78,    23,    23,    46,    47,    54,    61,    65,
      66,    67,    23,     0,    43,     7,    31,    77,    27,    25,
      26,    29,    34,    25,    26,     7,    29,    34,     7,    31,
       7,    13,    23,    32,    35,    36,    37,    39,    46,    52,
      61,    62,    64,    71,    72,    73,    74,    75,    76,    23,
      46,    51,    54,    68,     4,    16,    23,    24,    27,    45,
      46,    47,    48,    49,    55,    56,    57,    58,    59,    60,
      64,     8,    23,    53,    23,    24,    23,    31,    53,    23,
      24,    23,    51,     7,    60,    27,     7,     7,    27,    27,
      25,     7,    76,    32,    26,    26,    33,    28,    27,    49,
      49,    58,    45,    59,     3,     4,     5,     6,    17,    18,
      19,    20,    21,    22,    14,    15,    25,    30,    30,    32,
      60,    63,    25,    30,    30,    32,     7,    28,    63,    59,
      59,    60,    53,    53,    51,    12,    49,    28,    28,    45,
      45,    45,    45,    49,    49,    49,    49,    49,    49,    59,
      59,    60,    33,    32,    31,    28,    28,    28,     7,    53,
      63,    32,    63,    77,    77,    32,    38,    77
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    44,    44,    44,    44,
      45,    45,    45,    45,    45,    46,    46,    46,    46,    47,
      47,    48,    49,    49,    49,    49,    49,    49,    49,    50,
      51,    51,    52,    52,    53,    53,    54,    54,    54,    54,
      55,    55,    56,    57,    57,    57,    57,    57,    57,    58,
      58,    58,    59,    59,    60,    60,    61,    61,    61,    62,
      63,    63,    64,    64,    65,    65,    66,    66,    66,    66,
      67,    67,    68,    68,    69,    69,    70,    71,    72,    72,
      72,    73,    74,    74,    75,    75,    75,    75,    75,    75,
      75,    75,    75,    76,    76,    77,    77,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     4,     4,     4,     4,     3,
       3,     2,     1,     1,     3,     1,     1,     1,     1,     5,
       1,     3,     3,     3,     1,     1,     3,     3,     1,     1,
       3,     3,     2,     3,     3,     3,     3,     3,     3,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     4,
       1,     3,     4,     3,     5,     3,     7,     6,     5,     4,
       1,     1,     1,     0,     5,     7,     2,     2,     5,     7,
       6,     5,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     2,     2,     2,     1,     2,     3,     2
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* Program: ProgramElementList  */
#line 110 "parser.yacc"
{  
  root = A_Program((yyvsp[0].programElementList));
  (yyval.program) = A_Program((yyvsp[0].programElementList));
}
#line 1281 "y.tab.cpp"
    break;

  case 3: /* ProgramElementList: ProgramElement ProgramElementList  */
#line 117 "parser.yacc"
{
  (yyval.programElementList) = A_ProgramElementList((yyvsp[-1].programElement), (yyvsp[0].programElementList));
}
#line 1289 "y.tab.cpp"
    break;

  case 4: /* ProgramElementList: %empty  */
#line 121 "parser.yacc"
{
  (yyval.programElementList) = NULL;
}
#line 1297 "y.tab.cpp"
    break;

  case 5: /* ProgramElement: VarDeclStmt  */
#line 127 "parser.yacc"
{
  (yyval.programElement) = A_ProgramVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1305 "y.tab.cpp"
    break;

  case 6: /* ProgramElement: StructDef  */
#line 131 "parser.yacc"
{
  (yyval.programElement) = A_ProgramStructDef((yyvsp[0].structDef)->pos, (yyvsp[0].structDef));
}
#line 1313 "y.tab.cpp"
    break;

  case 7: /* ProgramElement: FnDeclStmt  */
#line 135 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDeclStmt((yyvsp[0].fnDeclStmt)->pos, (yyvsp[0].fnDeclStmt));
}
#line 1321 "y.tab.cpp"
    break;

  case 8: /* ProgramElement: FnDef  */
#line 139 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDef((yyvsp[0].fnDef)->pos, (yyvsp[0].fnDef));
}
#line 1329 "y.tab.cpp"
    break;

  case 9: /* ProgramElement: SEMICOLON  */
#line 143 "parser.yacc"
{
  (yyval.programElement) = A_ProgramNullStmt((yyvsp[0].pos));
}
#line 1337 "y.tab.cpp"
    break;

  case 10: /* ArithExpr: ArithExpr ADD ArithExpr  */
#line 150 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_add, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1345 "y.tab.cpp"
    break;

  case 11: /* ArithExpr: ArithExpr SUB ArithExpr  */
#line 154 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_sub, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1353 "y.tab.cpp"
    break;

  case 12: /* ArithExpr: ArithExpr MUL ArithExpr  */
#line 158 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_mul, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1361 "y.tab.cpp"
    break;

  case 13: /* ArithExpr: ArithExpr DIV ArithExpr  */
#line 162 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_div, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1369 "y.tab.cpp"
    break;

  case 14: /* ArithExpr: ExprUnit  */
#line 166 "parser.yacc"
{
  (yyval.arithExpr) = A_ExprUnit((yyvsp[0].exprUnit)->pos, (yyvsp[0].exprUnit));
}
#line 1377 "y.tab.cpp"
    break;

  case 15: /* ArrayExpr: IDENTIFIER LBRACKET INT_LITERAL RBRACKET  */
#line 171 "parser.yacc"
{
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].indexExpr)->pos, A_IdExprLVal((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id), A_NumIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.num));
}
#line 1385 "y.tab.cpp"
    break;

  case 16: /* ArrayExpr: IDENTIFIER LBRACKET IDENTIFIER RBRACKET  */
#line 173 "parser.yacc"
                                          {
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].indexExpr)->pos, A_IdExprLVal((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id), A_IdIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.id));
}
#line 1393 "y.tab.cpp"
    break;

  case 17: /* ArrayExpr: LeftVal LBRACKET INT_LITERAL RBRACKET  */
#line 176 "parser.yacc"
{
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), A_NumIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.num));
}
#line 1401 "y.tab.cpp"
    break;

  case 18: /* ArrayExpr: LeftVal LBRACKET IDENTIFIER RBRACKET  */
#line 179 "parser.yacc"
{
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), A_IdIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.id));
}
#line 1409 "y.tab.cpp"
    break;

  case 19: /* MemberExpr: IDENTIFIER DOT IDENTIFIER  */
#line 184 "parser.yacc"
{
  (yyval.memberExpr) = A_MemberExpr((yyvsp[-2].indexExpr)->pos, A_IdExprLVal((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id), (yyvsp[0].indexExpr)->u.id);
}
#line 1417 "y.tab.cpp"
    break;

  case 20: /* MemberExpr: LeftVal DOT IDENTIFIER  */
#line 188 "parser.yacc"
{
  (yyval.memberExpr) = A_MemberExpr((yyvsp[-2].leftVal)->pos, (yyvsp[-2].leftVal), (yyvsp[0].indexExpr)->u.id);
}
#line 1425 "y.tab.cpp"
    break;

  case 21: /* ArithUExpr: SUB ExprUnit  */
#line 193 "parser.yacc"
{
  (yyval.arithUExpr) = A_ArithUExpr((yyvsp[-1].pos), A_neg, (yyvsp[0].exprUnit));
}
#line 1433 "y.tab.cpp"
    break;

  case 22: /* ExprUnit: INT_LITERAL  */
#line 198 "parser.yacc"
{
  (yyval.exprUnit) = A_NumExprUnit((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.num);
}
#line 1441 "y.tab.cpp"
    break;

  case 23: /* ExprUnit: IDENTIFIER  */
#line 202 "parser.yacc"
{
  (yyval.exprUnit) = A_IdExprUnit((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1449 "y.tab.cpp"
    break;

  case 24: /* ExprUnit: LPAREN ArithExpr RPAREN  */
#line 206 "parser.yacc"
{
  (yyval.exprUnit) = A_ArithExprUnit((yyvsp[-2].pos), (yyvsp[-1].arithExpr));
}
#line 1457 "y.tab.cpp"
    break;

  case 25: /* ExprUnit: FnCall  */
#line 210 "parser.yacc"
{
  (yyval.exprUnit) = A_CallExprUnit((yyvsp[0].fnCall)->pos, (yyvsp[0].fnCall));
}
#line 1465 "y.tab.cpp"
    break;

  case 26: /* ExprUnit: MemberExpr  */
#line 214 "parser.yacc"
{
  (yyval.exprUnit) = A_MemberExprUnit((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr));
}
#line 1473 "y.tab.cpp"
    break;

  case 27: /* ExprUnit: ArrayExpr  */
#line 218 "parser.yacc"
{
  (yyval.exprUnit) = A_ArrayExprUnit((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr));
}
#line 1481 "y.tab.cpp"
    break;

  case 28: /* ExprUnit: ArithUExpr  */
#line 222 "parser.yacc"
{
  (yyval.exprUnit) = A_ArithUExprUnit((yyvsp[0].arithUExpr)->pos, (yyvsp[0].arithUExpr));
}
#line 1489 "y.tab.cpp"
    break;

  case 29: /* StructDef: STRUCT IDENTIFIER LBRACE VarDeclList RBRACE  */
#line 227 "parser.yacc"
{
  (yyval.structDef) = A_StructDef((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].varDeclList));
}
#line 1497 "y.tab.cpp"
    break;

  case 30: /* VarDeclList: VarDecl  */
#line 232 "parser.yacc"
{
  (yyval.varDeclList) = A_VarDeclList((yyvsp[0].varDecl), NULL);
}
#line 1505 "y.tab.cpp"
    break;

  case 31: /* VarDeclList: VarDecl COMMA VarDeclList  */
#line 236 "parser.yacc"
{
  (yyval.varDeclList) = A_VarDeclList((yyvsp[-2].varDecl), (yyvsp[0].varDeclList));
}
#line 1513 "y.tab.cpp"
    break;

  case 32: /* VarDeclStmt: LET VarDecl SEMICOLON  */
#line 241 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDeclStmt((yyvsp[-1].varDecl)->pos, (yyvsp[-1].varDecl));
}
#line 1521 "y.tab.cpp"
    break;

  case 33: /* VarDeclStmt: LET VarDef SEMICOLON  */
#line 245 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDefStmt((yyvsp[-1].varDef)->pos, (yyvsp[-1].varDef));
}
#line 1529 "y.tab.cpp"
    break;

  case 34: /* Type: INT  */
#line 250 "parser.yacc"
{
  (yyval.type) = A_NativeType((yyvsp[0].pos), A_intTypeKind);
}
#line 1537 "y.tab.cpp"
    break;

  case 35: /* Type: IDENTIFIER  */
#line 254 "parser.yacc"
{
  (yyval.type) = A_StructType((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1545 "y.tab.cpp"
    break;

  case 36: /* VarDecl: IDENTIFIER COLON Type  */
#line 259 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Scalar((yyvsp[-2].indexExpr)->pos, A_VarDeclScalar((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, (yyvsp[0].type)));
}
#line 1553 "y.tab.cpp"
    break;

  case 37: /* VarDecl: ArrayExpr COLON Type  */
#line 263 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Array((yyvsp[-2].arrayExpr)->pos, A_VarDeclArray((yyvsp[-2].arrayExpr)->pos, (yyvsp[-2].arrayExpr)->arr->u.id, (yyvsp[-2].arrayExpr)->idx->u.num, (yyvsp[0].type)));
}
#line 1561 "y.tab.cpp"
    break;

  case 38: /* VarDecl: IDENTIFIER  */
#line 267 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Scalar((yyvsp[0].indexExpr)->pos, A_VarDeclScalar((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id, NULL));
}
#line 1569 "y.tab.cpp"
    break;

  case 39: /* VarDecl: ArrayExpr  */
#line 271 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Array((yyvsp[0].arrayExpr)->pos, A_VarDeclArray((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr)->arr->u.id, (yyvsp[0].arrayExpr)->idx->u.num, NULL));
}
#line 1577 "y.tab.cpp"
    break;

  case 40: /* BoolBiOpExpr: BoolExpr AND BoolExpr  */
#line 276 "parser.yacc"
{
  (yyval.boolBiOpExpr) = A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos, A_and, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
}
#line 1585 "y.tab.cpp"
    break;

  case 41: /* BoolBiOpExpr: BoolExpr OR BoolExpr  */
#line 280 "parser.yacc"
{
  (yyval.boolBiOpExpr) = A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos, A_or, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
}
#line 1593 "y.tab.cpp"
    break;

  case 42: /* BoolUOpExpr: NOT BoolUnit  */
#line 285 "parser.yacc"
{
  (yyval.boolUOpExpr) = A_BoolUOpExpr((yyvsp[-1].pos), A_not, (yyvsp[0].boolUnit));
}
#line 1601 "y.tab.cpp"
    break;

  case 43: /* ComExpr: ExprUnit LT ExprUnit  */
#line 290 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_lt, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1609 "y.tab.cpp"
    break;

  case 44: /* ComExpr: ExprUnit LE ExprUnit  */
#line 294 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_le, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1617 "y.tab.cpp"
    break;

  case 45: /* ComExpr: ExprUnit GT ExprUnit  */
#line 298 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_gt, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1625 "y.tab.cpp"
    break;

  case 46: /* ComExpr: ExprUnit GE ExprUnit  */
#line 302 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_ge, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1633 "y.tab.cpp"
    break;

  case 47: /* ComExpr: ExprUnit EQ ExprUnit  */
#line 306 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_eq, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1641 "y.tab.cpp"
    break;

  case 48: /* ComExpr: ExprUnit NEQ ExprUnit  */
#line 310 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_ne, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1649 "y.tab.cpp"
    break;

  case 49: /* BoolUnit: ComExpr  */
#line 315 "parser.yacc"
{
  (yyval.boolUnit) = A_ComExprUnit((yyvsp[0].comExpr)->pos, (yyvsp[0].comExpr));
}
#line 1657 "y.tab.cpp"
    break;

  case 50: /* BoolUnit: LPAREN BoolExpr RPAREN  */
#line 319 "parser.yacc"
{
  (yyval.boolUnit) = A_BoolExprUnit((yyvsp[-2].pos), (yyvsp[-1].boolExpr));
}
#line 1665 "y.tab.cpp"
    break;

  case 51: /* BoolUnit: BoolUOpExpr  */
#line 323 "parser.yacc"
{
  (yyval.boolUnit) = A_BoolUOpExprUnit((yyvsp[0].boolUOpExpr)->pos, (yyvsp[0].boolUOpExpr));
}
#line 1673 "y.tab.cpp"
    break;

  case 52: /* BoolExpr: BoolBiOpExpr  */
#line 328 "parser.yacc"
{
  (yyval.boolExpr) = A_BoolBiOp_Expr((yyvsp[0].boolBiOpExpr)->pos, (yyvsp[0].boolBiOpExpr));
}
#line 1681 "y.tab.cpp"
    break;

  case 53: /* BoolExpr: BoolUnit  */
#line 332 "parser.yacc"
{
  (yyval.boolExpr) = A_BoolExpr((yyvsp[0].boolUnit)->pos, (yyvsp[0].boolUnit));
}
#line 1689 "y.tab.cpp"
    break;

  case 54: /* RightVal: ArithExpr  */
#line 337 "parser.yacc"
{
  (yyval.rightVal) = A_ArithExprRVal((yyvsp[0].arithExpr)->pos, (yyvsp[0].arithExpr));
}
#line 1697 "y.tab.cpp"
    break;

  case 55: /* RightVal: BoolExpr  */
#line 341 "parser.yacc"
{
  (yyval.rightVal) = A_BoolExprRVal((yyvsp[0].boolExpr)->pos, (yyvsp[0].boolExpr));
}
#line 1705 "y.tab.cpp"
    break;

  case 56: /* LeftVal: IDENTIFIER  */
#line 346 "parser.yacc"
{
  (yyval.leftVal) = A_IdExprLVal((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1713 "y.tab.cpp"
    break;

  case 57: /* LeftVal: ArrayExpr  */
#line 350 "parser.yacc"
{
  (yyval.leftVal) = A_ArrExprLVal((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr));
}
#line 1721 "y.tab.cpp"
    break;

  case 58: /* LeftVal: MemberExpr  */
#line 354 "parser.yacc"
{
  (yyval.leftVal) = A_MemberExprLVal((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr));
}
#line 1729 "y.tab.cpp"
    break;

  case 59: /* AssignStmt: LeftVal ASSIGN RightVal SEMICOLON  */
#line 360 "parser.yacc"
{
  (yyval.assignStmt) = A_AssignStmt((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), (yyvsp[-1].rightVal));
}
#line 1737 "y.tab.cpp"
    break;

  case 60: /* RightValList: RightVal  */
#line 365 "parser.yacc"
{
  (yyval.rightValList) = A_RightValList((yyvsp[0].rightVal), NULL);
}
#line 1745 "y.tab.cpp"
    break;

  case 61: /* RightValList: RightVal COMMA RightValList  */
#line 369 "parser.yacc"
{
  (yyval.rightValList) = A_RightValList((yyvsp[-2].rightVal), (yyvsp[0].rightValList));
}
#line 1753 "y.tab.cpp"
    break;

  case 62: /* FnCall: IDENTIFIER LPAREN RightValList RPAREN  */
#line 374 "parser.yacc"
{
  (yyval.fnCall) = A_FnCall((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].rightValList));
}
#line 1761 "y.tab.cpp"
    break;

  case 63: /* FnCall: IDENTIFIER LPAREN RPAREN  */
#line 378 "parser.yacc"
{
  (yyval.fnCall) = A_FnCall((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, NULL);
}
#line 1769 "y.tab.cpp"
    break;

  case 64: /* VarDefScalar: IDENTIFIER COLON Type ASSIGN RightVal  */
#line 383 "parser.yacc"
{
  (yyval.varDefScalar) = A_VarDefScalar((yyvsp[-4].indexExpr)->pos, (yyvsp[-4].indexExpr)->u.id, (yyvsp[-2].type), (yyvsp[0].rightVal));
}
#line 1777 "y.tab.cpp"
    break;

  case 65: /* VarDefScalar: IDENTIFIER ASSIGN RightVal  */
#line 387 "parser.yacc"
{
  (yyval.varDefScalar) = A_VarDefScalar((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, NULL, (yyvsp[0].rightVal));
}
#line 1785 "y.tab.cpp"
    break;

  case 66: /* VarDefArray: ArrayExpr COLON Type ASSIGN LBRACE RightValList RBRACE  */
#line 392 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-6].arrayExpr)->pos, (yyvsp[-6].arrayExpr)->arr->u.id, (yyvsp[-6].arrayExpr)->idx->u.num, (yyvsp[-4].type), (yyvsp[-1].rightValList));
}
#line 1793 "y.tab.cpp"
    break;

  case 67: /* VarDefArray: ArrayExpr COLON Type ASSIGN LBRACE RBRACE  */
#line 396 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-5].arrayExpr)->pos, (yyvsp[-5].arrayExpr)->arr->u.id, (yyvsp[-5].arrayExpr)->idx->u.num, (yyvsp[-3].type), NULL);
}
#line 1801 "y.tab.cpp"
    break;

  case 68: /* VarDefArray: ArrayExpr ASSIGN LBRACE RightValList RBRACE  */
#line 400 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-4].arrayExpr)->pos, (yyvsp[-4].arrayExpr)->arr->u.id, (yyvsp[-4].arrayExpr)->idx->u.num, NULL, (yyvsp[-1].rightValList));
}
#line 1809 "y.tab.cpp"
    break;

  case 69: /* VarDefArray: ArrayExpr ASSIGN LBRACE RBRACE  */
#line 404 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-3].arrayExpr)->pos, (yyvsp[-3].arrayExpr)->arr->u.id, (yyvsp[-3].arrayExpr)->idx->u.num, NULL, NULL);
}
#line 1817 "y.tab.cpp"
    break;

  case 70: /* VarDef: VarDefArray  */
#line 409 "parser.yacc"
{
  (yyval.varDef) = A_VarDef_Array((yyvsp[0].varDefArray)->pos, (yyvsp[0].varDefArray));
}
#line 1825 "y.tab.cpp"
    break;

  case 71: /* VarDef: VarDefScalar  */
#line 413 "parser.yacc"
{
  (yyval.varDef) = A_VarDef_Scalar((yyvsp[0].varDefScalar)->pos, (yyvsp[0].varDefScalar));
}
#line 1833 "y.tab.cpp"
    break;

  case 72: /* ParamDecl: VarDeclList  */
#line 418 "parser.yacc"
{
  (yyval.paramDecl) = A_ParamDecl((yyvsp[0].varDeclList));
}
#line 1841 "y.tab.cpp"
    break;

  case 73: /* ParamDecl: %empty  */
#line 422 "parser.yacc"
{
  (yyval.paramDecl) = A_ParamDecl(NULL);
}
#line 1849 "y.tab.cpp"
    break;

  case 74: /* FnDecl: FN IDENTIFIER LPAREN ParamDecl RPAREN  */
#line 427 "parser.yacc"
{
  (yyval.fnDecl) = A_FnDecl((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].paramDecl), NULL);
}
#line 1857 "y.tab.cpp"
    break;

  case 75: /* FnDecl: FN IDENTIFIER LPAREN ParamDecl RPAREN ARROW Type  */
#line 431 "parser.yacc"
{
  (yyval.fnDecl) = A_FnDecl((yyvsp[-5].indexExpr)->pos, (yyvsp[-5].indexExpr)->u.id, (yyvsp[-3].paramDecl), (yyvsp[0].type));
}
#line 1865 "y.tab.cpp"
    break;

  case 76: /* FnDeclStmt: FnDecl SEMICOLON  */
#line 436 "parser.yacc"
{
  (yyval.fnDeclStmt) = A_FnDeclStmt((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl));
}
#line 1873 "y.tab.cpp"
    break;

  case 77: /* CallStmt: FnCall SEMICOLON  */
#line 441 "parser.yacc"
{
  (yyval.callStmt) = A_CallStmt((yyvsp[-1].fnCall)->pos, (yyvsp[-1].fnCall));
}
#line 1881 "y.tab.cpp"
    break;

  case 78: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock  */
#line 446 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-4].pos), (yyvsp[-2].boolExpr), (yyvsp[0].codeBlockStmtList), NULL);
}
#line 1889 "y.tab.cpp"
    break;

  case 79: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock ELSE CodeBlock  */
#line 450 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-6].pos), (yyvsp[-4].boolExpr), (yyvsp[-2].codeBlockStmtList), (yyvsp[0].codeBlockStmtList));
}
#line 1897 "y.tab.cpp"
    break;

  case 80: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock ELSE  */
#line 454 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-5].pos), (yyvsp[-3].boolExpr), (yyvsp[-1].codeBlockStmtList), NULL);
}
#line 1905 "y.tab.cpp"
    break;

  case 81: /* WhileStmt: WHILE LPAREN BoolExpr RPAREN CodeBlock  */
#line 459 "parser.yacc"
{
  (yyval.whileStmt) = A_WhileStmt((yyvsp[-4].pos), (yyvsp[-2].boolExpr), (yyvsp[0].codeBlockStmtList));
}
#line 1913 "y.tab.cpp"
    break;

  case 82: /* ReturnStmt: RETURN RightVal SEMICOLON  */
#line 464 "parser.yacc"
{
  (yyval.returnStmt) = A_ReturnStmt((yyvsp[-2].pos), (yyvsp[-1].rightVal));
}
#line 1921 "y.tab.cpp"
    break;

  case 83: /* ReturnStmt: RETURN SEMICOLON  */
#line 468 "parser.yacc"
                 {
  (yyval.returnStmt) = A_ReturnStmt((yyvsp[-1].pos), NULL);
}
#line 1929 "y.tab.cpp"
    break;

  case 84: /* CodeBlockStmt: SEMICOLON  */
#line 473 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockNullStmt((yyvsp[0].pos));
}
#line 1937 "y.tab.cpp"
    break;

  case 85: /* CodeBlockStmt: VarDeclStmt  */
#line 477 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1945 "y.tab.cpp"
    break;

  case 86: /* CodeBlockStmt: AssignStmt  */
#line 481 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockAssignStmt((yyvsp[0].assignStmt)->pos, (yyvsp[0].assignStmt));
}
#line 1953 "y.tab.cpp"
    break;

  case 87: /* CodeBlockStmt: CallStmt  */
#line 485 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockCallStmt((yyvsp[0].callStmt)->pos, (yyvsp[0].callStmt));
}
#line 1961 "y.tab.cpp"
    break;

  case 88: /* CodeBlockStmt: IfStmt  */
#line 489 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockIfStmt((yyvsp[0].ifStmt)->pos, (yyvsp[0].ifStmt));
}
#line 1969 "y.tab.cpp"
    break;

  case 89: /* CodeBlockStmt: WhileStmt  */
#line 493 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockWhileStmt((yyvsp[0].whileStmt)->pos, (yyvsp[0].whileStmt));
}
#line 1977 "y.tab.cpp"
    break;

  case 90: /* CodeBlockStmt: ReturnStmt  */
#line 497 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockReturnStmt((yyvsp[0].returnStmt)->pos, (yyvsp[0].returnStmt));
}
#line 1985 "y.tab.cpp"
    break;

  case 91: /* CodeBlockStmt: CONTINUE SEMICOLON  */
#line 501 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockContinueStmt((yyvsp[-1].pos));
}
#line 1993 "y.tab.cpp"
    break;

  case 92: /* CodeBlockStmt: BREAK SEMICOLON  */
#line 505 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockBreakStmt((yyvsp[-1].pos));
}
#line 2001 "y.tab.cpp"
    break;

  case 93: /* CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList  */
#line 510 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[-1].codeBlockStmt), (yyvsp[0].codeBlockStmtList));
}
#line 2009 "y.tab.cpp"
    break;

  case 94: /* CodeBlockStmtList: CodeBlockStmt  */
#line 514 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[0].codeBlockStmt), NULL);
}
#line 2017 "y.tab.cpp"
    break;

  case 95: /* CodeBlock: LBRACE RBRACE  */
#line 519 "parser.yacc"
{
  (yyval.codeBlockStmtList) = NULL;
}
#line 2025 "y.tab.cpp"
    break;

  case 96: /* CodeBlock: LBRACE CodeBlockStmtList RBRACE  */
#line 523 "parser.yacc"
{
  (yyval.codeBlockStmtList) = (yyvsp[-1].codeBlockStmtList);
}
#line 2033 "y.tab.cpp"
    break;

  case 97: /* FnDef: FnDecl CodeBlock  */
#line 528 "parser.yacc"
{
  (yyval.fnDef) = A_FnDef((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl), (yyvsp[0].codeBlockStmtList));
}
#line 2041 "y.tab.cpp"
    break;


#line 2045 "y.tab.cpp"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 532 "parser.yacc"



extern "C"{
void yyerror(char * s)
{
  fprintf(stderr, "%s\n",s);
}
int yywrap()
{
  return(1);
}
}


