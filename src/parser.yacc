%{
#include <stdio.h>
#include "TeaplAst.h"

extern A_pos pos;
extern A_program root;

extern int yylex(void);
extern "C"{
extern void yyerror(char *s); 
extern int  yywrap();
}

%}

%union {
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
}

%token <pos> ADD SUB MUL DIV SEMICOLON INT FN LET STRUCT ARROW RETURN
%token <pos> AND OR NOT EQ NEQ GE LE GT LT
%token <indexExpr> IDENTIFIER INT_LITERAL
%token <pos> ASSIGN COLON LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE  COMMA DOT
%token <pos> CONTINUE BREAK IF ELSE WHILE

%type <leftVal> LeftVal
%type <rightVal> RightVal
%type <program> Program
%type <boolExpr> BoolExpr
%type <boolUnit> BoolUnit
%type <boolBiOpExpr> BoolBiOpExpr
%type <boolUOpExpr> BoolUOpExpr
%type <comExpr> ComExpr
%type <arithExpr> ArithExpr
%type <programElementList> ProgramElementList
%type <programElement> ProgramElement
%type <exprUnit> ExprUnit
%type <structDef> StructDef
%type <varDecl> VarDecl
%type <varDefScalar> VarDefScalar
%type <varDefArray> VarDefArray
%type <varDef> VarDef
%type <varDeclStmt> VarDeclStmt
%type <varDeclList> VarDeclList
%type <fnDeclStmt> FnDeclStmt
%type <fnDecl> FnDecl
%type <paramDecl> ParamDecl
%type <fnDef> FnDef
%type <codeBlockStmt> CodeBlockStmt
%type <codeBlockStmtList> CodeBlockStmtList
%type <codeBlockStmtList> CodeBlock
%type <fnCall> FnCall
%type <callStmt> CallStmt
%type <type> Type
%type <memberExpr> MemberExpr
%type <arrayExpr> ArrayExpr
%type <arithUExpr> ArithUExpr
%type <assignStmt> AssignStmt
%type <rightValList> RightValList
%type <returnStmt> ReturnStmt
%type <ifStmt> IfStmt
%type <whileStmt> WhileStmt

%start Program

%%                   /* beginning of rules section */

Program: ProgramElementList 
{  
  root = A_Program($1);
  $$ = A_Program($1);
}
;

ProgramElementList: ProgramElement ProgramElementList
{
  $$ = A_ProgramElementList($1, $2);
}
|
{
  $$ = NULL;
}
;

ProgramElement: VarDeclStmt
{
  $$ = A_ProgramVarDeclStmt($1->pos, $1);
}
| StructDef
{
  $$ = A_ProgramStructDef($1->pos, $1);
}
| FnDeclStmt
{
  $$ = A_ProgramFnDeclStmt($1->pos, $1);
}
| FnDef
{
  $$ = A_ProgramFnDef($1->pos, $1);
}
| SEMICOLON
{
  $$ = A_ProgramNullStmt($1);
}
;


ArithExpr: ArithExpr ADD ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_add, $1, $3));
}
| ArithExpr SUB ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_sub, $1, $3));
}
| ArithExpr MUL ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_mul, $1, $3));
}
| ArithExpr DIV ArithExpr
{
  $$ = A_ArithBiOp_Expr($1->pos, A_ArithBiOpExpr($1->pos, A_div, $1, $3));
}
| ExprUnit
{
  $$ = A_ExprUnit($1->pos, $1);
};

ArrayExpr: IDENTIFIER LBRACKET INT_LITERAL RBRACKET
{
  $$ = A_ArrayExpr($1->pos, A_IdExprLVal($1->pos, $1->u.id), A_NumIndexExpr($3->pos, $3->u.num));
}| IDENTIFIER LBRACKET IDENTIFIER RBRACKET{
  $$ = A_ArrayExpr($1->pos, A_IdExprLVal($1->pos, $1->u.id), A_IdIndexExpr($3->pos, $3->u.id));
}| LeftVal LBRACKET INT_LITERAL RBRACKET
{
  $$ = A_ArrayExpr($1->pos, $1, A_NumIndexExpr($3->pos, $3->u.num));
}| LeftVal LBRACKET IDENTIFIER RBRACKET
{
  $$ = A_ArrayExpr($1->pos, $1, A_IdIndexExpr($3->pos, $3->u.id));
};

MemberExpr: IDENTIFIER DOT IDENTIFIER
{
  $$ = A_MemberExpr($1->pos, A_IdExprLVal($1->pos, $1->u.id), $3->u.id);
}|
LeftVal DOT IDENTIFIER
{
  $$ = A_MemberExpr($1->pos, $1, $3->u.id);
};

ArithUExpr: SUB ExprUnit
{
  $$ = A_ArithUExpr($1, A_neg, $2);
};

ExprUnit: INT_LITERAL
{
  $$ = A_NumExprUnit($1->pos, $1->u.num);
}
| IDENTIFIER
{
  $$ = A_IdExprUnit($1->pos, $1->u.id);
}
| LPAREN ArithExpr RPAREN
{
  $$ = A_ArithExprUnit($1, $2);
}
| FnCall
{
  $$ = A_CallExprUnit($1->pos, $1);
}
| MemberExpr
{
  $$ = A_MemberExprUnit($1->pos, $1);
}
| ArrayExpr
{
  $$ = A_ArrayExprUnit($1->pos, $1);
}
| ArithUExpr
{
  $$ = A_ArithUExprUnit($1->pos, $1);
};

StructDef: STRUCT IDENTIFIER LBRACE VarDeclList RBRACE
{
  $$ = A_StructDef($2->pos, $2->u.id, $4);
}

VarDeclList: VarDecl
{
  $$ = A_VarDeclList($1, NULL);
}
| VarDecl COMMA VarDeclList
{
  $$ = A_VarDeclList($1, $3);
};

VarDeclStmt: LET VarDecl SEMICOLON
{
  $$ = A_VarDeclStmt($2->pos, $2);
}
| LET VarDef SEMICOLON
{
  $$ = A_VarDefStmt($2->pos, $2);
};

Type: INT
{
  $$ = A_NativeType($1, A_intTypeKind);
}
| IDENTIFIER
{
  $$ = A_StructType($1->pos, $1->u.id);
};

VarDecl: IDENTIFIER COLON Type
{
  $$ = A_VarDecl_Scalar($1->pos, A_VarDeclScalar($1->pos, $1->u.id, $3));
}
| ArrayExpr COLON Type
{
  $$ = A_VarDecl_Array($1->pos, A_VarDeclArray($1->pos, $1->arr->u.id, $1->idx->u.num, $3));
}
| IDENTIFIER
{
  $$ = A_VarDecl_Scalar($1->pos, A_VarDeclScalar($1->pos, $1->u.id, NULL));
}
| ArrayExpr
{
  $$ = A_VarDecl_Array($1->pos, A_VarDeclArray($1->pos, $1->arr->u.id, $1->idx->u.num, NULL));
};

BoolBiOpExpr: BoolExpr AND BoolExpr
{
  $$ = A_BoolBiOpExpr($1->pos, A_and, $1, $3);
}
| BoolExpr OR BoolExpr
{
  $$ = A_BoolBiOpExpr($1->pos, A_or, $1, $3);
};

BoolUOpExpr: NOT BoolUnit
{
  $$ = A_BoolUOpExpr($1, A_not, $2);
};

ComExpr: ExprUnit LT ExprUnit
{
  $$ = A_ComExpr($1->pos, A_lt, $1, $3);
}
| ExprUnit LE ExprUnit
{
  $$ = A_ComExpr($1->pos, A_le, $1, $3);
}
| ExprUnit GT ExprUnit
{
  $$ = A_ComExpr($1->pos, A_gt, $1, $3);
}
| ExprUnit GE ExprUnit
{
  $$ = A_ComExpr($1->pos, A_ge, $1, $3);
}
| ExprUnit EQ ExprUnit
{
  $$ = A_ComExpr($1->pos, A_eq, $1, $3);
}
| ExprUnit NEQ ExprUnit
{
  $$ = A_ComExpr($1->pos, A_ne, $1, $3);
};

BoolUnit: ComExpr
{
  $$ = A_ComExprUnit($1->pos, $1);
}
| LPAREN BoolExpr RPAREN
{
  $$ = A_BoolExprUnit($1, $2);
}
| BoolUOpExpr
{
  $$ = A_BoolUOpExprUnit($1->pos, $1);
};

BoolExpr: BoolBiOpExpr
{
  $$ = A_BoolBiOp_Expr($1->pos, $1);
}
| BoolUnit
{
  $$ = A_BoolExpr($1->pos, $1);
};

RightVal: ArithExpr
{
  $$ = A_ArithExprRVal($1->pos, $1);
}
| BoolExpr
{
  $$ = A_BoolExprRVal($1->pos, $1);
};

LeftVal: IDENTIFIER
{
  $$ = A_IdExprLVal($1->pos, $1->u.id);
}
| ArrayExpr
{
  $$ = A_ArrExprLVal($1->pos, $1);
}
| MemberExpr
{
  $$ = A_MemberExprLVal($1->pos, $1);
};


AssignStmt: LeftVal ASSIGN RightVal SEMICOLON
{
  $$ = A_AssignStmt($1->pos, $1, $3);
};

RightValList: RightVal
{
  $$ = A_RightValList($1, NULL);
}
| RightVal COMMA RightValList
{
  $$ = A_RightValList($1, $3);
};

FnCall: IDENTIFIER LPAREN RightValList RPAREN
{
  $$ = A_FnCall($1->pos, $1->u.id, $3);
}
| IDENTIFIER LPAREN RPAREN
{
  $$ = A_FnCall($1->pos, $1->u.id, NULL);
};

VarDefScalar: IDENTIFIER COLON Type ASSIGN RightVal
{
  $$ = A_VarDefScalar($1->pos, $1->u.id, $3, $5);
}
| IDENTIFIER ASSIGN RightVal
{
  $$ = A_VarDefScalar($1->pos, $1->u.id, NULL, $3);
};

VarDefArray: ArrayExpr COLON Type ASSIGN LBRACE RightValList RBRACE
{
  $$ = A_VarDefArray($1->pos, $1->arr->u.id, $1->idx->u.num, $3, $6);
}
| ArrayExpr COLON Type ASSIGN LBRACE RBRACE
{
  $$ = A_VarDefArray($1->pos, $1->arr->u.id, $1->idx->u.num, $3, NULL);
}
| ArrayExpr ASSIGN LBRACE RightValList RBRACE
{
  $$ = A_VarDefArray($1->pos, $1->arr->u.id, $1->idx->u.num, NULL, $4);
}
| ArrayExpr ASSIGN LBRACE RBRACE
{
  $$ = A_VarDefArray($1->pos, $1->arr->u.id, $1->idx->u.num, NULL, NULL);
};

VarDef: VarDefArray
{
  $$ = A_VarDef_Array($1->pos, $1);
}
| VarDefScalar
{
  $$ = A_VarDef_Scalar($1->pos, $1);
};

ParamDecl: VarDeclList
{
  $$ = A_ParamDecl($1);
}
|
{
  $$ = A_ParamDecl(NULL);
};

FnDecl: FN IDENTIFIER LPAREN ParamDecl RPAREN
{
  $$ = A_FnDecl($2->pos, $2->u.id, $4, NULL);
}
| FN IDENTIFIER LPAREN ParamDecl RPAREN ARROW Type
{
  $$ = A_FnDecl($2->pos, $2->u.id, $4, $7);
};

FnDeclStmt: FnDecl SEMICOLON
{
  $$ = A_FnDeclStmt($1->pos, $1);
};

CallStmt: FnCall SEMICOLON
{
  $$ = A_CallStmt($1->pos, $1);
}

IfStmt: IF LPAREN BoolExpr RPAREN CodeBlock
{
  $$ = A_IfStmt($1, $3, $5, NULL);
}
| IF LPAREN BoolExpr RPAREN CodeBlock ELSE CodeBlock
{
  $$ = A_IfStmt($1, $3, $5, $7);
}
| IF LPAREN BoolExpr RPAREN CodeBlock ELSE
{
  $$ = A_IfStmt($1, $3, $5, NULL);
};

WhileStmt: WHILE LPAREN BoolExpr RPAREN CodeBlock
{
  $$ = A_WhileStmt($1, $3, $5);
};

ReturnStmt: RETURN RightVal SEMICOLON
{
  $$ = A_ReturnStmt($1, $2);
};

CodeBlockStmt: SEMICOLON
{
  $$ = A_BlockNullStmt($1);
}
| VarDeclStmt
{
  $$ = A_BlockVarDeclStmt($1->pos, $1);
}
| AssignStmt
{
  $$ = A_BlockAssignStmt($1->pos, $1);
}
| CallStmt
{
  $$ = A_BlockCallStmt($1->pos, $1);
}
| IfStmt
{
  $$ = A_BlockIfStmt($1->pos, $1);
}
| WhileStmt
{
  $$ = A_BlockWhileStmt($1->pos, $1);
}
| ReturnStmt
{
  $$ = A_BlockReturnStmt($1->pos, $1);
}
| CONTINUE SEMICOLON
{
  $$ = A_BlockContinueStmt($1);
}
| BREAK SEMICOLON
{
  $$ = A_BlockBreakStmt($1);
};

CodeBlockStmtList: CodeBlockStmt CodeBlockStmtList
{
  $$ = A_CodeBlockStmtList($1, $2);
}
| CodeBlockStmt
{
  $$ = A_CodeBlockStmtList($1, NULL);
};

CodeBlock: LBRACE RBRACE
{
  $$ = NULL;
}
| LBRACE CodeBlockStmtList RBRACE
{
  $$ = $2;
};

FnDef: FnDecl CodeBlock
{
  $$ = A_FnDef($1->pos, $1, $2);
};

%%


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


