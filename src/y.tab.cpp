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
  YYSYMBOL_YYACCEPT = 40,                  /* $accept  */
  YYSYMBOL_Program = 41,                   /* Program  */
  YYSYMBOL_ProgramElementList = 42,        /* ProgramElementList  */
  YYSYMBOL_ProgramElement = 43,            /* ProgramElement  */
  YYSYMBOL_ArithExpr = 44,                 /* ArithExpr  */
  YYSYMBOL_ArrayExpr = 45,                 /* ArrayExpr  */
  YYSYMBOL_MemberExpr = 46,                /* MemberExpr  */
  YYSYMBOL_ArithUExpr = 47,                /* ArithUExpr  */
  YYSYMBOL_ExprUnit = 48,                  /* ExprUnit  */
  YYSYMBOL_StructDef = 49,                 /* StructDef  */
  YYSYMBOL_VarDeclList = 50,               /* VarDeclList  */
  YYSYMBOL_VarDeclStmt = 51,               /* VarDeclStmt  */
  YYSYMBOL_Type = 52,                      /* Type  */
  YYSYMBOL_VarDecl = 53,                   /* VarDecl  */
  YYSYMBOL_BoolBiOpExpr = 54,              /* BoolBiOpExpr  */
  YYSYMBOL_BoolUOpExpr = 55,               /* BoolUOpExpr  */
  YYSYMBOL_ComExpr = 56,                   /* ComExpr  */
  YYSYMBOL_BoolUnit = 57,                  /* BoolUnit  */
  YYSYMBOL_BoolExpr = 58,                  /* BoolExpr  */
  YYSYMBOL_RightVal = 59,                  /* RightVal  */
  YYSYMBOL_LeftVal = 60,                   /* LeftVal  */
  YYSYMBOL_AssignStmt = 61,                /* AssignStmt  */
  YYSYMBOL_RightValList = 62,              /* RightValList  */
  YYSYMBOL_FnCall = 63,                    /* FnCall  */
  YYSYMBOL_VarDefScalar = 64,              /* VarDefScalar  */
  YYSYMBOL_VarDefArray = 65,               /* VarDefArray  */
  YYSYMBOL_VarDef = 66,                    /* VarDef  */
  YYSYMBOL_ParamDecl = 67,                 /* ParamDecl  */
  YYSYMBOL_FnDecl = 68,                    /* FnDecl  */
  YYSYMBOL_FnDeclStmt = 69,                /* FnDeclStmt  */
  YYSYMBOL_CallStmt = 70,                  /* CallStmt  */
  YYSYMBOL_IfStmt = 71,                    /* IfStmt  */
  YYSYMBOL_WhileStmt = 72,                 /* WhileStmt  */
  YYSYMBOL_ReturnStmt = 73,                /* ReturnStmt  */
  YYSYMBOL_CodeBlockStmt = 74,             /* CodeBlockStmt  */
  YYSYMBOL_CodeBlockStmtList = 75,         /* CodeBlockStmtList  */
  YYSYMBOL_CodeBlock = 76,                 /* CodeBlock  */
  YYSYMBOL_FnDef = 77                      /* FnDef  */
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
#define YYFINAL  21
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   189

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  38
/* YYNRULES -- Number of rules.  */
#define YYNRULES  93
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  169

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   105,   105,   112,   117,   122,   126,   130,   134,   138,
     145,   149,   153,   157,   161,   166,   169,   173,   178,   183,
     187,   191,   195,   199,   203,   207,   212,   217,   221,   226,
     230,   235,   239,   244,   248,   252,   256,   261,   265,   270,
     275,   279,   283,   287,   291,   295,   300,   304,   308,   313,
     317,   322,   326,   331,   335,   339,   344,   349,   353,   358,
     362,   367,   371,   376,   380,   384,   388,   393,   397,   402,
     407,   411,   415,   420,   425,   430,   434,   438,   443,   448,
     453,   457,   461,   465,   469,   473,   477,   481,   485,   490,
     494,   499,   503,   508
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
  "IF", "ELSE", "WHILE", "$accept", "Program", "ProgramElementList",
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

#define YYPACT_NINF (-84)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     128,   -84,   -11,    -3,     7,    14,   -84,   128,   -84,   -84,
       2,   -84,   -84,    13,   100,    50,    42,   -84,   -84,    57,
      63,   -84,   -84,   -84,     6,   -84,    77,   126,     0,    59,
      75,     0,   -84,   -84,    77,   -84,   126,    90,   -84,   109,
     115,   105,   107,   -84,   -84,   -84,   118,   -84,   141,   -84,
     -84,   -84,   -84,    74,   119,    72,   138,   -84,   133,   124,
      65,   126,    90,   -84,   126,   157,   -84,   -84,   -84,   137,
     -84,   -84,   -84,   -84,   132,   -84,   -84,   -84,   -84,   140,
     139,   142,    91,   143,   135,   163,   117,   148,   -84,   -84,
     126,   126,   126,   -84,   -84,   -84,     0,     0,    77,   161,
      65,   -84,   137,   -84,    22,     3,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,   126,   126,   126,   -84,
     -84,   -84,   144,   146,   145,   -84,   -84,   -84,   147,   -84,
      71,    76,   167,   -84,   -84,   -84,     0,   -84,   -84,   -84,
     157,   157,   157,   157,   -84,   -84,   -84,   -84,   -84,   -84,
     132,   132,   -84,   126,   -84,   104,   -84,   149,   149,   -84,
     -84,   -84,   -84,   150,   151,   -84,   -84,   149,   -84
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     9,     0,     0,     0,     0,     2,     4,     6,     5,
       0,     7,     8,     0,    35,    36,     0,    68,    67,     0,
       0,     1,     3,    73,     0,    93,    70,     0,     0,     0,
       0,     0,    29,    30,     0,    80,     0,    53,    91,     0,
       0,     0,     0,    54,    55,    81,     0,    82,     0,    83,
      84,    85,    86,    90,     0,    35,    36,    69,    27,     0,
       0,     0,    20,    19,     0,    51,    24,    23,    25,    14,
      49,    48,    46,    50,    52,    62,    22,    31,    32,    33,
       0,     0,     0,    34,     0,     0,     0,     0,    87,    88,
       0,     0,     0,    74,    89,    92,     0,     0,     0,    71,
       0,    18,     0,    39,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    16,
      15,    66,    57,     0,     0,    26,    79,    60,     0,    17,
       0,     0,     0,    33,    34,    28,     0,    14,    21,    47,
      10,    11,    12,    13,    44,    45,    43,    41,    42,    40,
      37,    38,    61,     0,    65,     0,    59,     0,     0,    56,
      72,    58,    64,     0,    75,    78,    63,    77,    76
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -84,   -84,   172,   -84,   -29,    -2,   -19,   -84,   -54,   -84,
     -30,   -14,   -31,   178,   -84,   -84,   -84,   122,   -43,   -25,
     -84,   -84,   -83,    -9,   -84,   -84,   -84,   -84,   -84,   -84,
     -84,   -84,   -84,   -84,   -84,   131,   -55,   -84
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     5,     6,     7,    65,    66,    67,    68,    69,     8,
      57,     9,    79,    58,    70,    71,    72,    73,    74,   122,
      46,    47,   123,    76,    17,    18,    19,    59,    10,    11,
      49,    50,    51,    52,    53,    54,    25,    12
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      83,    15,    75,   128,    84,    44,   101,   102,    77,    23,
      45,    85,    13,    35,    21,    48,     3,   116,   117,    36,
      14,   105,    43,    78,    56,   106,   107,   108,   109,    37,
      20,   139,    56,    24,    44,   104,   102,   102,    38,    45,
      26,    39,    40,    41,    48,    42,   137,   130,   131,    32,
     138,    43,   137,   137,   137,   137,   144,   145,   146,   147,
     148,   149,   102,   102,    33,   133,   134,   132,   135,    60,
     161,   104,   163,   150,   151,    30,    31,   140,   141,   142,
     143,    35,    80,    81,     3,   116,   117,    36,    62,    63,
     116,   117,   100,   152,    34,    60,    56,    37,    96,   157,
      55,    29,   164,   165,   158,   160,    82,    61,    60,    39,
      40,    41,   168,    42,    62,    63,    88,    86,    64,    29,
      61,    60,    89,   121,    87,    27,    28,    62,    63,    29,
      60,    64,    90,    61,    91,     1,   162,     2,     3,     4,
      62,    63,    61,    92,    64,   127,   116,   117,    93,    62,
      63,    95,    99,    64,   110,   111,   112,   113,   114,   115,
     106,   107,   108,   109,    97,   118,    98,   125,   124,   119,
     126,   129,   120,   136,   159,   156,   155,   153,   154,    22,
      24,    16,   166,   103,    94,     0,     0,     0,     0,   167
};

static const yytype_int16 yycheck[] =
{
      31,     3,    27,    86,    34,    24,    60,    61,     8,     7,
      24,    36,    23,     7,     0,    24,    10,    14,    15,    13,
      23,    64,    24,    23,    26,     3,     4,     5,     6,    23,
      23,    28,    34,    31,    53,    64,    90,    91,    32,    53,
      27,    35,    36,    37,    53,    39,   100,    90,    91,     7,
      28,    53,   106,   107,   108,   109,   110,   111,   112,   113,
     114,   115,   116,   117,     7,    96,    97,    92,    98,     4,
     153,   100,   155,   116,   117,    25,    26,   106,   107,   108,
     109,     7,    23,    24,    10,    14,    15,    13,    23,    24,
      14,    15,    27,   118,    31,     4,    98,    23,    26,    28,
      23,    29,   157,   158,    28,   136,    31,    16,     4,    35,
      36,    37,   167,    39,    23,    24,     7,    27,    27,    29,
      16,     4,     7,    32,    34,    25,    26,    23,    24,    29,
       4,    27,    27,    16,    27,     7,    32,     9,    10,    11,
      23,    24,    16,    25,    27,    28,    14,    15,     7,    23,
      24,    32,    28,    27,    17,    18,    19,    20,    21,    22,
       3,     4,     5,     6,    26,    25,    33,    32,    25,    30,
       7,    23,    30,    12,     7,    28,    31,    33,    32,     7,
      31,     3,    32,    61,    53,    -1,    -1,    -1,    -1,    38
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     7,     9,    10,    11,    41,    42,    43,    49,    51,
      68,    69,    77,    23,    23,    45,    53,    64,    65,    66,
      23,     0,    42,     7,    31,    76,    27,    25,    26,    29,
      25,    26,     7,     7,    31,     7,    13,    23,    32,    35,
      36,    37,    39,    45,    46,    51,    60,    61,    63,    70,
      71,    72,    73,    74,    75,    23,    45,    50,    53,    67,
       4,    16,    23,    24,    27,    44,    45,    46,    47,    48,
      54,    55,    56,    57,    58,    59,    63,     8,    23,    52,
      23,    24,    31,    52,    50,    59,    27,    34,     7,     7,
      27,    27,    25,     7,    75,    32,    26,    26,    33,    28,
      27,    48,    48,    57,    44,    58,     3,     4,     5,     6,
      17,    18,    19,    20,    21,    22,    14,    15,    25,    30,
      30,    32,    59,    62,    25,    32,     7,    28,    62,    23,
      58,    58,    59,    52,    52,    50,    12,    48,    28,    28,
      44,    44,    44,    44,    48,    48,    48,    48,    48,    48,
      58,    58,    59,    33,    32,    31,    28,    28,    28,     7,
      52,    62,    32,    62,    76,    76,    32,    38,    76
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    40,    41,    42,    42,    43,    43,    43,    43,    43,
      44,    44,    44,    44,    44,    45,    45,    46,    47,    48,
      48,    48,    48,    48,    48,    48,    49,    50,    50,    51,
      51,    52,    52,    53,    53,    53,    53,    54,    54,    55,
      56,    56,    56,    56,    56,    56,    57,    57,    57,    58,
      58,    59,    59,    60,    60,    60,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    65,    65,    66,    66,    67,
      67,    68,    68,    69,    70,    71,    71,    71,    72,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      75,    76,    76,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     1,     4,     4,     3,     2,     1,
       1,     3,     1,     1,     1,     1,     5,     1,     3,     3,
       3,     1,     1,     3,     3,     1,     1,     3,     3,     2,
       3,     3,     3,     3,     3,     3,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     1,     3,     4,
       3,     5,     3,     7,     6,     5,     4,     1,     1,     1,
       0,     5,     7,     2,     2,     5,     7,     6,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     2,     2,     2,
       1,     2,     3,     2
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
#line 106 "parser.yacc"
{  
  root = A_Program((yyvsp[0].programElementList));
  (yyval.program) = A_Program((yyvsp[0].programElementList));
}
#line 1271 "y.tab.cpp"
    break;

  case 3: /* ProgramElementList: ProgramElement ProgramElementList  */
#line 113 "parser.yacc"
{
  (yyval.programElementList) = A_ProgramElementList((yyvsp[-1].programElement), (yyvsp[0].programElementList));
}
#line 1279 "y.tab.cpp"
    break;

  case 4: /* ProgramElementList: %empty  */
#line 117 "parser.yacc"
{
  (yyval.programElementList) = NULL;
}
#line 1287 "y.tab.cpp"
    break;

  case 5: /* ProgramElement: VarDeclStmt  */
#line 123 "parser.yacc"
{
  (yyval.programElement) = A_ProgramVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1295 "y.tab.cpp"
    break;

  case 6: /* ProgramElement: StructDef  */
#line 127 "parser.yacc"
{
  (yyval.programElement) = A_ProgramStructDef((yyvsp[0].structDef)->pos, (yyvsp[0].structDef));
}
#line 1303 "y.tab.cpp"
    break;

  case 7: /* ProgramElement: FnDeclStmt  */
#line 131 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDeclStmt((yyvsp[0].fnDeclStmt)->pos, (yyvsp[0].fnDeclStmt));
}
#line 1311 "y.tab.cpp"
    break;

  case 8: /* ProgramElement: FnDef  */
#line 135 "parser.yacc"
{
  (yyval.programElement) = A_ProgramFnDef((yyvsp[0].fnDef)->pos, (yyvsp[0].fnDef));
}
#line 1319 "y.tab.cpp"
    break;

  case 9: /* ProgramElement: SEMICOLON  */
#line 139 "parser.yacc"
{
  (yyval.programElement) = A_ProgramNullStmt((yyvsp[0].pos));
}
#line 1327 "y.tab.cpp"
    break;

  case 10: /* ArithExpr: ArithExpr ADD ArithExpr  */
#line 146 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_add, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1335 "y.tab.cpp"
    break;

  case 11: /* ArithExpr: ArithExpr SUB ArithExpr  */
#line 150 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_sub, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1343 "y.tab.cpp"
    break;

  case 12: /* ArithExpr: ArithExpr MUL ArithExpr  */
#line 154 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_mul, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1351 "y.tab.cpp"
    break;

  case 13: /* ArithExpr: ArithExpr DIV ArithExpr  */
#line 158 "parser.yacc"
{
  (yyval.arithExpr) = A_ArithBiOp_Expr((yyvsp[-2].arithExpr)->pos, A_ArithBiOpExpr((yyvsp[-2].arithExpr)->pos, A_div, (yyvsp[-2].arithExpr), (yyvsp[0].arithExpr)));
}
#line 1359 "y.tab.cpp"
    break;

  case 14: /* ArithExpr: ExprUnit  */
#line 162 "parser.yacc"
{
  (yyval.arithExpr) = A_ExprUnit((yyvsp[0].exprUnit)->pos, (yyvsp[0].exprUnit));
}
#line 1367 "y.tab.cpp"
    break;

  case 15: /* ArrayExpr: IDENTIFIER LBRACKET INT_LITERAL RBRACKET  */
#line 167 "parser.yacc"
{
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].indexExpr)->pos, A_IdExprLVal((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id), A_NumIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.num));
}
#line 1375 "y.tab.cpp"
    break;

  case 16: /* ArrayExpr: IDENTIFIER LBRACKET IDENTIFIER RBRACKET  */
#line 169 "parser.yacc"
                                          {
  (yyval.arrayExpr) = A_ArrayExpr((yyvsp[-3].indexExpr)->pos, A_IdExprLVal((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id), A_IdIndexExpr((yyvsp[-1].indexExpr)->pos, (yyvsp[-1].indexExpr)->u.id));
}
#line 1383 "y.tab.cpp"
    break;

  case 17: /* MemberExpr: IDENTIFIER DOT IDENTIFIER  */
#line 174 "parser.yacc"
{
  (yyval.memberExpr) = A_MemberExpr((yyvsp[-2].indexExpr)->pos, A_IdExprLVal((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id), (yyvsp[0].indexExpr)->u.id);
}
#line 1391 "y.tab.cpp"
    break;

  case 18: /* ArithUExpr: SUB ExprUnit  */
#line 179 "parser.yacc"
{
  (yyval.arithUExpr) = A_ArithUExpr((yyvsp[-1].pos), A_neg, (yyvsp[0].exprUnit));
}
#line 1399 "y.tab.cpp"
    break;

  case 19: /* ExprUnit: INT_LITERAL  */
#line 184 "parser.yacc"
{
  (yyval.exprUnit) = A_NumExprUnit((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.num);
}
#line 1407 "y.tab.cpp"
    break;

  case 20: /* ExprUnit: IDENTIFIER  */
#line 188 "parser.yacc"
{
  (yyval.exprUnit) = A_IdExprUnit((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1415 "y.tab.cpp"
    break;

  case 21: /* ExprUnit: LPAREN ArithExpr RPAREN  */
#line 192 "parser.yacc"
{
  (yyval.exprUnit) = A_ArithExprUnit((yyvsp[-2].pos), (yyvsp[-1].arithExpr));
}
#line 1423 "y.tab.cpp"
    break;

  case 22: /* ExprUnit: FnCall  */
#line 196 "parser.yacc"
{
  (yyval.exprUnit) = A_CallExprUnit((yyvsp[0].fnCall)->pos, (yyvsp[0].fnCall));
}
#line 1431 "y.tab.cpp"
    break;

  case 23: /* ExprUnit: MemberExpr  */
#line 200 "parser.yacc"
{
  (yyval.exprUnit) = A_MemberExprUnit((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr));
}
#line 1439 "y.tab.cpp"
    break;

  case 24: /* ExprUnit: ArrayExpr  */
#line 204 "parser.yacc"
{
  (yyval.exprUnit) = A_ArrayExprUnit((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr));
}
#line 1447 "y.tab.cpp"
    break;

  case 25: /* ExprUnit: ArithUExpr  */
#line 208 "parser.yacc"
{
  (yyval.exprUnit) = A_ArithUExprUnit((yyvsp[0].arithUExpr)->pos, (yyvsp[0].arithUExpr));
}
#line 1455 "y.tab.cpp"
    break;

  case 26: /* StructDef: STRUCT IDENTIFIER LBRACE VarDeclList RBRACE  */
#line 213 "parser.yacc"
{
  (yyval.structDef) = A_StructDef((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].varDeclList));
}
#line 1463 "y.tab.cpp"
    break;

  case 27: /* VarDeclList: VarDecl  */
#line 218 "parser.yacc"
{
  (yyval.varDeclList) = A_VarDeclList((yyvsp[0].varDecl), NULL);
}
#line 1471 "y.tab.cpp"
    break;

  case 28: /* VarDeclList: VarDecl COMMA VarDeclList  */
#line 222 "parser.yacc"
{
  (yyval.varDeclList) = A_VarDeclList((yyvsp[-2].varDecl), (yyvsp[0].varDeclList));
}
#line 1479 "y.tab.cpp"
    break;

  case 29: /* VarDeclStmt: LET VarDecl SEMICOLON  */
#line 227 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDeclStmt((yyvsp[-1].varDecl)->pos, (yyvsp[-1].varDecl));
}
#line 1487 "y.tab.cpp"
    break;

  case 30: /* VarDeclStmt: LET VarDef SEMICOLON  */
#line 231 "parser.yacc"
{
  (yyval.varDeclStmt) = A_VarDefStmt((yyvsp[-1].varDef)->pos, (yyvsp[-1].varDef));
}
#line 1495 "y.tab.cpp"
    break;

  case 31: /* Type: INT  */
#line 236 "parser.yacc"
{
  (yyval.type) = A_NativeType((yyvsp[0].pos), A_intTypeKind);
}
#line 1503 "y.tab.cpp"
    break;

  case 32: /* Type: IDENTIFIER  */
#line 240 "parser.yacc"
{
  (yyval.type) = A_StructType((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1511 "y.tab.cpp"
    break;

  case 33: /* VarDecl: IDENTIFIER COLON Type  */
#line 245 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Scalar((yyvsp[-2].indexExpr)->pos, A_VarDeclScalar((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, (yyvsp[0].type)));
}
#line 1519 "y.tab.cpp"
    break;

  case 34: /* VarDecl: ArrayExpr COLON Type  */
#line 249 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Array((yyvsp[-2].arrayExpr)->pos, A_VarDeclArray((yyvsp[-2].arrayExpr)->pos, (yyvsp[-2].arrayExpr)->arr->u.id, (yyvsp[-2].arrayExpr)->idx->u.num, (yyvsp[0].type)));
}
#line 1527 "y.tab.cpp"
    break;

  case 35: /* VarDecl: IDENTIFIER  */
#line 253 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Scalar((yyvsp[0].indexExpr)->pos, A_VarDeclScalar((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id, NULL));
}
#line 1535 "y.tab.cpp"
    break;

  case 36: /* VarDecl: ArrayExpr  */
#line 257 "parser.yacc"
{
  (yyval.varDecl) = A_VarDecl_Array((yyvsp[0].arrayExpr)->pos, A_VarDeclArray((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr)->arr->u.id, (yyvsp[0].arrayExpr)->idx->u.num, NULL));
}
#line 1543 "y.tab.cpp"
    break;

  case 37: /* BoolBiOpExpr: BoolExpr AND BoolExpr  */
#line 262 "parser.yacc"
{
  (yyval.boolBiOpExpr) = A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos, A_and, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
}
#line 1551 "y.tab.cpp"
    break;

  case 38: /* BoolBiOpExpr: BoolExpr OR BoolExpr  */
#line 266 "parser.yacc"
{
  (yyval.boolBiOpExpr) = A_BoolBiOpExpr((yyvsp[-2].boolExpr)->pos, A_or, (yyvsp[-2].boolExpr), (yyvsp[0].boolExpr));
}
#line 1559 "y.tab.cpp"
    break;

  case 39: /* BoolUOpExpr: NOT BoolUnit  */
#line 271 "parser.yacc"
{
  (yyval.boolUOpExpr) = A_BoolUOpExpr((yyvsp[-1].pos), A_not, (yyvsp[0].boolUnit));
}
#line 1567 "y.tab.cpp"
    break;

  case 40: /* ComExpr: ExprUnit LT ExprUnit  */
#line 276 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_lt, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1575 "y.tab.cpp"
    break;

  case 41: /* ComExpr: ExprUnit LE ExprUnit  */
#line 280 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_le, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1583 "y.tab.cpp"
    break;

  case 42: /* ComExpr: ExprUnit GT ExprUnit  */
#line 284 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_gt, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1591 "y.tab.cpp"
    break;

  case 43: /* ComExpr: ExprUnit GE ExprUnit  */
#line 288 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_ge, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1599 "y.tab.cpp"
    break;

  case 44: /* ComExpr: ExprUnit EQ ExprUnit  */
#line 292 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_eq, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1607 "y.tab.cpp"
    break;

  case 45: /* ComExpr: ExprUnit NEQ ExprUnit  */
#line 296 "parser.yacc"
{
  (yyval.comExpr) = A_ComExpr((yyvsp[-2].exprUnit)->pos, A_ne, (yyvsp[-2].exprUnit), (yyvsp[0].exprUnit));
}
#line 1615 "y.tab.cpp"
    break;

  case 46: /* BoolUnit: ComExpr  */
#line 301 "parser.yacc"
{
  (yyval.boolUnit) = A_ComExprUnit((yyvsp[0].comExpr)->pos, (yyvsp[0].comExpr));
}
#line 1623 "y.tab.cpp"
    break;

  case 47: /* BoolUnit: LPAREN BoolExpr RPAREN  */
#line 305 "parser.yacc"
{
  (yyval.boolUnit) = A_BoolExprUnit((yyvsp[-2].pos), (yyvsp[-1].boolExpr));
}
#line 1631 "y.tab.cpp"
    break;

  case 48: /* BoolUnit: BoolUOpExpr  */
#line 309 "parser.yacc"
{
  (yyval.boolUnit) = A_BoolUOpExprUnit((yyvsp[0].boolUOpExpr)->pos, (yyvsp[0].boolUOpExpr));
}
#line 1639 "y.tab.cpp"
    break;

  case 49: /* BoolExpr: BoolBiOpExpr  */
#line 314 "parser.yacc"
{
  (yyval.boolExpr) = A_BoolBiOp_Expr((yyvsp[0].boolBiOpExpr)->pos, (yyvsp[0].boolBiOpExpr));
}
#line 1647 "y.tab.cpp"
    break;

  case 50: /* BoolExpr: BoolUnit  */
#line 318 "parser.yacc"
{
  (yyval.boolExpr) = A_BoolExpr((yyvsp[0].boolUnit)->pos, (yyvsp[0].boolUnit));
}
#line 1655 "y.tab.cpp"
    break;

  case 51: /* RightVal: ArithExpr  */
#line 323 "parser.yacc"
{
  (yyval.rightVal) = A_ArithExprRVal((yyvsp[0].arithExpr)->pos, (yyvsp[0].arithExpr));
}
#line 1663 "y.tab.cpp"
    break;

  case 52: /* RightVal: BoolExpr  */
#line 327 "parser.yacc"
{
  (yyval.rightVal) = A_BoolExprRVal((yyvsp[0].boolExpr)->pos, (yyvsp[0].boolExpr));
}
#line 1671 "y.tab.cpp"
    break;

  case 53: /* LeftVal: IDENTIFIER  */
#line 332 "parser.yacc"
{
  (yyval.leftVal) = A_IdExprLVal((yyvsp[0].indexExpr)->pos, (yyvsp[0].indexExpr)->u.id);
}
#line 1679 "y.tab.cpp"
    break;

  case 54: /* LeftVal: ArrayExpr  */
#line 336 "parser.yacc"
{
  (yyval.leftVal) = A_ArrExprLVal((yyvsp[0].arrayExpr)->pos, (yyvsp[0].arrayExpr));
}
#line 1687 "y.tab.cpp"
    break;

  case 55: /* LeftVal: MemberExpr  */
#line 340 "parser.yacc"
{
  (yyval.leftVal) = A_MemberExprLVal((yyvsp[0].memberExpr)->pos, (yyvsp[0].memberExpr));
}
#line 1695 "y.tab.cpp"
    break;

  case 56: /* AssignStmt: LeftVal ASSIGN RightVal SEMICOLON  */
#line 345 "parser.yacc"
{
  (yyval.assignStmt) = A_AssignStmt((yyvsp[-3].leftVal)->pos, (yyvsp[-3].leftVal), (yyvsp[-1].rightVal));
}
#line 1703 "y.tab.cpp"
    break;

  case 57: /* RightValList: RightVal  */
#line 350 "parser.yacc"
{
  (yyval.rightValList) = A_RightValList((yyvsp[0].rightVal), NULL);
}
#line 1711 "y.tab.cpp"
    break;

  case 58: /* RightValList: RightVal COMMA RightValList  */
#line 354 "parser.yacc"
{
  (yyval.rightValList) = A_RightValList((yyvsp[-2].rightVal), (yyvsp[0].rightValList));
}
#line 1719 "y.tab.cpp"
    break;

  case 59: /* FnCall: IDENTIFIER LPAREN RightValList RPAREN  */
#line 359 "parser.yacc"
{
  (yyval.fnCall) = A_FnCall((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].rightValList));
}
#line 1727 "y.tab.cpp"
    break;

  case 60: /* FnCall: IDENTIFIER LPAREN RPAREN  */
#line 363 "parser.yacc"
{
  (yyval.fnCall) = A_FnCall((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, NULL);
}
#line 1735 "y.tab.cpp"
    break;

  case 61: /* VarDefScalar: IDENTIFIER COLON Type ASSIGN RightVal  */
#line 368 "parser.yacc"
{
  (yyval.varDefScalar) = A_VarDefScalar((yyvsp[-4].indexExpr)->pos, (yyvsp[-4].indexExpr)->u.id, (yyvsp[-2].type), (yyvsp[0].rightVal));
}
#line 1743 "y.tab.cpp"
    break;

  case 62: /* VarDefScalar: IDENTIFIER ASSIGN RightVal  */
#line 372 "parser.yacc"
{
  (yyval.varDefScalar) = A_VarDefScalar((yyvsp[-2].indexExpr)->pos, (yyvsp[-2].indexExpr)->u.id, NULL, (yyvsp[0].rightVal));
}
#line 1751 "y.tab.cpp"
    break;

  case 63: /* VarDefArray: ArrayExpr COLON Type ASSIGN LBRACE RightValList RBRACE  */
#line 377 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-6].arrayExpr)->pos, (yyvsp[-6].arrayExpr)->arr->u.id, (yyvsp[-6].arrayExpr)->idx->u.num, (yyvsp[-4].type), (yyvsp[-1].rightValList));
}
#line 1759 "y.tab.cpp"
    break;

  case 64: /* VarDefArray: ArrayExpr COLON Type ASSIGN LBRACE RBRACE  */
#line 381 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-5].arrayExpr)->pos, (yyvsp[-5].arrayExpr)->arr->u.id, (yyvsp[-5].arrayExpr)->idx->u.num, (yyvsp[-3].type), NULL);
}
#line 1767 "y.tab.cpp"
    break;

  case 65: /* VarDefArray: ArrayExpr ASSIGN LBRACE RightValList RBRACE  */
#line 385 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-4].arrayExpr)->pos, (yyvsp[-4].arrayExpr)->arr->u.id, (yyvsp[-4].arrayExpr)->idx->u.num, NULL, (yyvsp[-1].rightValList));
}
#line 1775 "y.tab.cpp"
    break;

  case 66: /* VarDefArray: ArrayExpr ASSIGN LBRACE RBRACE  */
#line 389 "parser.yacc"
{
  (yyval.varDefArray) = A_VarDefArray((yyvsp[-3].arrayExpr)->pos, (yyvsp[-3].arrayExpr)->arr->u.id, (yyvsp[-3].arrayExpr)->idx->u.num, NULL, NULL);
}
#line 1783 "y.tab.cpp"
    break;

  case 67: /* VarDef: VarDefArray  */
#line 394 "parser.yacc"
{
  (yyval.varDef) = A_VarDef_Array((yyvsp[0].varDefArray)->pos, (yyvsp[0].varDefArray));
}
#line 1791 "y.tab.cpp"
    break;

  case 68: /* VarDef: VarDefScalar  */
#line 398 "parser.yacc"
{
  (yyval.varDef) = A_VarDef_Scalar((yyvsp[0].varDefScalar)->pos, (yyvsp[0].varDefScalar));
}
#line 1799 "y.tab.cpp"
    break;

  case 69: /* ParamDecl: VarDeclList  */
#line 403 "parser.yacc"
{
  (yyval.paramDecl) = A_ParamDecl((yyvsp[0].varDeclList));
}
#line 1807 "y.tab.cpp"
    break;

  case 70: /* ParamDecl: %empty  */
#line 407 "parser.yacc"
{
  (yyval.paramDecl) = A_ParamDecl(NULL);
}
#line 1815 "y.tab.cpp"
    break;

  case 71: /* FnDecl: FN IDENTIFIER LPAREN ParamDecl RPAREN  */
#line 412 "parser.yacc"
{
  (yyval.fnDecl) = A_FnDecl((yyvsp[-3].indexExpr)->pos, (yyvsp[-3].indexExpr)->u.id, (yyvsp[-1].paramDecl), NULL);
}
#line 1823 "y.tab.cpp"
    break;

  case 72: /* FnDecl: FN IDENTIFIER LPAREN ParamDecl RPAREN ARROW Type  */
#line 416 "parser.yacc"
{
  (yyval.fnDecl) = A_FnDecl((yyvsp[-5].indexExpr)->pos, (yyvsp[-5].indexExpr)->u.id, (yyvsp[-3].paramDecl), (yyvsp[0].type));
}
#line 1831 "y.tab.cpp"
    break;

  case 73: /* FnDeclStmt: FnDecl SEMICOLON  */
#line 421 "parser.yacc"
{
  (yyval.fnDeclStmt) = A_FnDeclStmt((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl));
}
#line 1839 "y.tab.cpp"
    break;

  case 74: /* CallStmt: FnCall SEMICOLON  */
#line 426 "parser.yacc"
{
  (yyval.callStmt) = A_CallStmt((yyvsp[-1].fnCall)->pos, (yyvsp[-1].fnCall));
}
#line 1847 "y.tab.cpp"
    break;

  case 75: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock  */
#line 431 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-4].pos), (yyvsp[-2].boolExpr), (yyvsp[0].codeBlockStmtList), NULL);
}
#line 1855 "y.tab.cpp"
    break;

  case 76: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock ELSE CodeBlock  */
#line 435 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-6].pos), (yyvsp[-4].boolExpr), (yyvsp[-2].codeBlockStmtList), (yyvsp[0].codeBlockStmtList));
}
#line 1863 "y.tab.cpp"
    break;

  case 77: /* IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock ELSE  */
#line 439 "parser.yacc"
{
  (yyval.ifStmt) = A_IfStmt((yyvsp[-5].pos), (yyvsp[-3].boolExpr), (yyvsp[-1].codeBlockStmtList), NULL);
}
#line 1871 "y.tab.cpp"
    break;

  case 78: /* WhileStmt: WHILE LPAREN BoolExpr RPAREN CodeBlock  */
#line 444 "parser.yacc"
{
  (yyval.whileStmt) = A_WhileStmt((yyvsp[-4].pos), (yyvsp[-2].boolExpr), (yyvsp[0].codeBlockStmtList));
}
#line 1879 "y.tab.cpp"
    break;

  case 79: /* ReturnStmt: RETURN RightVal SEMICOLON  */
#line 449 "parser.yacc"
{
  (yyval.returnStmt) = A_ReturnStmt((yyvsp[-2].pos), (yyvsp[-1].rightVal));
}
#line 1887 "y.tab.cpp"
    break;

  case 80: /* CodeBlockStmt: SEMICOLON  */
#line 454 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockNullStmt((yyvsp[0].pos));
}
#line 1895 "y.tab.cpp"
    break;

  case 81: /* CodeBlockStmt: VarDeclStmt  */
#line 458 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockVarDeclStmt((yyvsp[0].varDeclStmt)->pos, (yyvsp[0].varDeclStmt));
}
#line 1903 "y.tab.cpp"
    break;

  case 82: /* CodeBlockStmt: AssignStmt  */
#line 462 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockAssignStmt((yyvsp[0].assignStmt)->pos, (yyvsp[0].assignStmt));
}
#line 1911 "y.tab.cpp"
    break;

  case 83: /* CodeBlockStmt: CallStmt  */
#line 466 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockCallStmt((yyvsp[0].callStmt)->pos, (yyvsp[0].callStmt));
}
#line 1919 "y.tab.cpp"
    break;

  case 84: /* CodeBlockStmt: IfStmt  */
#line 470 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockIfStmt((yyvsp[0].ifStmt)->pos, (yyvsp[0].ifStmt));
}
#line 1927 "y.tab.cpp"
    break;

  case 85: /* CodeBlockStmt: WhileStmt  */
#line 474 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockWhileStmt((yyvsp[0].whileStmt)->pos, (yyvsp[0].whileStmt));
}
#line 1935 "y.tab.cpp"
    break;

  case 86: /* CodeBlockStmt: ReturnStmt  */
#line 478 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockReturnStmt((yyvsp[0].returnStmt)->pos, (yyvsp[0].returnStmt));
}
#line 1943 "y.tab.cpp"
    break;

  case 87: /* CodeBlockStmt: CONTINUE SEMICOLON  */
#line 482 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockContinueStmt((yyvsp[-1].pos));
}
#line 1951 "y.tab.cpp"
    break;

  case 88: /* CodeBlockStmt: BREAK SEMICOLON  */
#line 486 "parser.yacc"
{
  (yyval.codeBlockStmt) = A_BlockBreakStmt((yyvsp[-1].pos));
}
#line 1959 "y.tab.cpp"
    break;

  case 89: /* CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList  */
#line 491 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[-1].codeBlockStmt), (yyvsp[0].codeBlockStmtList));
}
#line 1967 "y.tab.cpp"
    break;

  case 90: /* CodeBlockStmtList: CodeBlockStmt  */
#line 495 "parser.yacc"
{
  (yyval.codeBlockStmtList) = A_CodeBlockStmtList((yyvsp[0].codeBlockStmt), NULL);
}
#line 1975 "y.tab.cpp"
    break;

  case 91: /* CodeBlock: LBRACE RBRACE  */
#line 500 "parser.yacc"
{
  (yyval.codeBlockStmtList) = NULL;
}
#line 1983 "y.tab.cpp"
    break;

  case 92: /* CodeBlock: LBRACE CodeBlockStmtList RBRACE  */
#line 504 "parser.yacc"
{
  (yyval.codeBlockStmtList) = (yyvsp[-1].codeBlockStmtList);
}
#line 1991 "y.tab.cpp"
    break;

  case 93: /* FnDef: FnDecl CodeBlock  */
#line 509 "parser.yacc"
{
  (yyval.fnDef) = A_FnDef((yyvsp[-1].fnDecl)->pos, (yyvsp[-1].fnDecl), (yyvsp[0].codeBlockStmtList));
}
#line 1999 "y.tab.cpp"
    break;


#line 2003 "y.tab.cpp"

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

#line 513 "parser.yacc"



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


