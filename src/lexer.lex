%{
#include <stdio.h>
#include <string.h>
#include "TeaplAst.h"
#include "y.tab.hpp"
extern int line, col;
%}

digit       [0-9]
nondigit    [a-zA-Z_]
identifier  {nondigit}({nondigit}|{digit})*
number      [1-9]{digit}*|0

%s COMMENT_INLINE COMMENT_BLOCK

%%
"fn"       { yylval.pos = A_Pos(line, col); col+=2; return FN; }
"let"      { yylval.pos = A_Pos(line, col); col+=3; return LET; }
"ret"      { yylval.pos = A_Pos(line, col); col+=3; return RETURN; }
"struct"   { yylval.pos = A_Pos(line, col); col+=6; return STRUCT; }
"if"       { yylval.pos = A_Pos(line, col); col+=2; return IF; }
"else"     { yylval.pos = A_Pos(line, col); col+=4; return ELSE; }
"while"    { yylval.pos = A_Pos(line, col); col+=5; return WHILE; }
"int"      { yylval.pos = A_Pos(line, col); col+=3; return INT; }
"continue" { yylval.pos = A_Pos(line, col); col+=8; return CONTINUE; }
"break"    { yylval.pos = A_Pos(line, col); col+=5; return BREAK; }
"+"       { yylval.pos = A_Pos(line, col); col+=1; return ADD; }
"-"       { yylval.pos = A_Pos(line, col); col+=1; return SUB; }
"*"       { yylval.pos = A_Pos(line, col); col+=1; return MUL; }
"/"       { yylval.pos = A_Pos(line, col); col+=1; return DIV; }
"="       { yylval.pos = A_Pos(line, col); col+=1; return ASSIGN; }
"&&"      { yylval.pos = A_Pos(line, col); col+=2; return AND; }
"||"      { yylval.pos = A_Pos(line, col); col+=2; return OR; }
"!"       { yylval.pos = A_Pos(line, col); col+=1; return NOT; }
"=="      { yylval.pos = A_Pos(line, col); col+=2; return EQ; }
"!="      { yylval.pos = A_Pos(line, col); col+=2; return NEQ; }
"<"       { yylval.pos = A_Pos(line, col); col+=1; return LT; }
"<="      { yylval.pos = A_Pos(line, col); col+=2; return LE; }
">"       { yylval.pos = A_Pos(line, col); col+=1; return GT; }
">="      { yylval.pos = A_Pos(line, col); col+=2; return GE; }
":"       { yylval.pos = A_Pos(line, col); col+=1; return COLON; }
";"       { yylval.pos = A_Pos(line, col); col+=1; return SEMICOLON; }
","       { yylval.pos = A_Pos(line, col); col+=1; return COMMA; }
"("       { yylval.pos = A_Pos(line, col); col+=1; return LPAREN; }
")"       { yylval.pos = A_Pos(line, col); col+=1; return RPAREN; }
"{"       { yylval.pos = A_Pos(line, col); col+=1; return LBRACE; }
"}"       { yylval.pos = A_Pos(line, col); col+=1; return RBRACE; }
"["       { yylval.pos = A_Pos(line, col); col+=1; return LBRACKET; }
"]"       { yylval.pos = A_Pos(line, col); col+=1; return RBRACKET; }
"."       { yylval.pos = A_Pos(line, col); col+=1; return DOT; }
"->"      { yylval.pos = A_Pos(line, col); col+=2; return ARROW; }

{identifier}    { yylval.indexExpr->pos = A_Pos(line, col); yylval.indexExpr->kind = A_idIndexKind; yylval.indexExpr->u.id = strdup(yytext); return IDENTIFIER; }
{number}        { yylval.indexExpr->pos = A_Pos(line, col); yylval.indexExpr->kind = A_numIndexKind; yylval.indexExpr->u.num = atoi(yytext); return INT_LITERAL; }
<INITIAL>"//" { BEGIN(COMMENT_INLINE); }
<COMMENT_INLINE>[^\n]* { }
<COMMENT_INLINE>\n { BEGIN(INITIAL); }
<INITIAL>"/*" { BEGIN(COMMENT_BLOCK); }
<COMMENT_BLOCK>[^*]* { }
<COMMENT_BLOCK>"*"+[^*/]* { }
<COMMENT_BLOCK>"*"+"/" { BEGIN(INITIAL); }
[\t]    { col+=4; }
[\n] {  line++; col=1;}
" " {col++;}
%%