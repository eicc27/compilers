/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_HPP_INCLUDED
# define YY_YY_Y_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ADD = 258,                     /* ADD  */
    SUB = 259,                     /* SUB  */
    MUL = 260,                     /* MUL  */
    DIV = 261,                     /* DIV  */
    SEMICOLON = 262,               /* SEMICOLON  */
    INT = 263,                     /* INT  */
    FN = 264,                      /* FN  */
    LET = 265,                     /* LET  */
    STRUCT = 266,                  /* STRUCT  */
    ARROW = 267,                   /* ARROW  */
    RETURN = 268,                  /* RETURN  */
    AND = 269,                     /* AND  */
    OR = 270,                      /* OR  */
    NOT = 271,                     /* NOT  */
    EQ = 272,                      /* EQ  */
    NEQ = 273,                     /* NEQ  */
    GE = 274,                      /* GE  */
    LE = 275,                      /* LE  */
    GT = 276,                      /* GT  */
    LT = 277,                      /* LT  */
    IDENTIFIER = 278,              /* IDENTIFIER  */
    INT_LITERAL = 279,             /* INT_LITERAL  */
    ASSIGN = 280,                  /* ASSIGN  */
    COLON = 281,                   /* COLON  */
    LPAREN = 282,                  /* LPAREN  */
    RPAREN = 283,                  /* RPAREN  */
    LBRACKET = 284,                /* LBRACKET  */
    RBRACKET = 285,                /* RBRACKET  */
    LBRACE = 286,                  /* LBRACE  */
    RBRACE = 287,                  /* RBRACE  */
    COMMA = 288,                   /* COMMA  */
    DOT = 289,                     /* DOT  */
    CONTINUE = 290,                /* CONTINUE  */
    BREAK = 291,                   /* BREAK  */
    IF = 292,                      /* IF  */
    ELSE = 293,                    /* ELSE  */
    WHILE = 294                    /* WHILE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define ADD 258
#define SUB 259
#define MUL 260
#define DIV 261
#define SEMICOLON 262
#define INT 263
#define FN 264
#define LET 265
#define STRUCT 266
#define ARROW 267
#define RETURN 268
#define AND 269
#define OR 270
#define NOT 271
#define EQ 272
#define NEQ 273
#define GE 274
#define LE 275
#define GT 276
#define LT 277
#define IDENTIFIER 278
#define INT_LITERAL 279
#define ASSIGN 280
#define COLON 281
#define LPAREN 282
#define RPAREN 283
#define LBRACKET 284
#define RBRACKET 285
#define LBRACE 286
#define RBRACE 287
#define COMMA 288
#define DOT 289
#define CONTINUE 290
#define BREAK 291
#define IF 292
#define ELSE 293
#define WHILE 294

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "parser.yacc"

  A_pos pos;
  A_program program;
  A_programElementList programElementList;
  A_programElement programElement;
  A_arithExpr arithExpr;
  A_exprUnit exprUnit;
  A_structDef structDef;
  A_varDef varDef;
  A_varDeclList varDeclList;
  A_varDeclStmt varDeclStmt;
  A_varDecl varDecl;
  A_fnDecl fnDecl;
  A_fnDeclStmt fnDeclStmt;
  A_paramDecl paramDecl;
  A_fnDef fnDef;
  A_codeBlockStmt codeBlockStmt;
  A_codeBlockStmtList codeBlockStmtList;
  A_indexExpr indexExpr;
  A_fnCall fnCall;
  A_callStmt callStmt;
  A_type type;
  A_rightVal rightVal;
  A_boolExpr boolExpr;
  A_boolBiOpExpr boolBiOpExpr;
  A_boolUOpExpr boolUOpExpr;
  A_boolUnit boolUnit;
  A_comExpr comExpr;
  A_leftVal leftVal;
  A_arrayExpr arrayExpr;
  A_memberExpr memberExpr;
  A_arithUExpr arithUExpr;
  A_assignStmt assignStmt;
  A_rightValList rightValList;
  A_varDefScalar varDefScalar;
  A_varDefArray varDefArray;
  A_returnStmt returnStmt;
  A_ifStmt ifStmt;
  A_whileStmt whileStmt;

#line 186 "y.tab.hpp"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_HPP_INCLUDED  */
