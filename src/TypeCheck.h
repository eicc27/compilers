#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include <unordered_map>
#include <stack>
//用来保存数字变量的值
typedef std::unordered_map<string, int> intMap;
// you can use this type to store the type a token.
typedef std::unordered_map<string, aA_type> typeMap; 
//用于存储位置信息
typedef std::unordered_map<string, A_pos> posMap; 
//用于存储函数已经被声明还是已经被定义
typedef std::unordered_map<string, A_programElementType> fnStateMap; 
//用于存储数组信息
typedef std::unordered_map<string, aA_varDeclArray_*> arrayDeclMap;
typedef std::unordered_map<string, aA_varDefArray_ *> arrayDefMap;
// you can use this map to store the members of a struct or params of a function.
typedef std::unordered_map<string, vector<aA_varDecl>*> paramMemberMap;

void check_Prog(std::ostream* out, aA_program p);
void check_VarDecl(std::ostream* out, aA_varDeclStmt vd, bool global);
void check_StructDef(std::ostream* out, aA_structDef sd);
void check_FnDecl(std::ostream* out, aA_fnDecl fd);
void check_FnDeclStmt(std::ostream* out, aA_fnDeclStmt fd);
void check_FnDef(std::ostream* out, aA_fnDef fd);
void check_CodeblockStmt(std::ostream* out, aA_codeBlockStmt cs);
void check_AssignStmt(std::ostream* out, aA_assignStmt as);
aA_type check_ArrayExpr(std::ostream* out, aA_arrayExpr ae);
aA_type check_MemberExpr(std::ostream* out, aA_memberExpr me);
void check_IfStmt(std::ostream* out, aA_ifStmt is);
void check_BoolExpr(std::ostream* out, aA_boolExpr be);
void check_BoolUnit(std::ostream* out, aA_boolUnit bu);
aA_type check_ExprUnit(std::ostream* out, aA_exprUnit eu);
aA_type check_FuncCall(std::ostream* out, aA_fnCall fc);
void check_WhileStmt(std::ostream* out, aA_whileStmt ws);
void check_CallStmt(std::ostream* out, aA_callStmt cs);
void check_ReturnStmt(std::ostream* out, aA_returnStmt rs);
bool com_aA_type(aA_type type1,aA_type type2);
bool com_paramList(vector<aA_varDecl> vec1,vector<aA_varDecl> vec2);
string aA_varDecl2Name(aA_varDecl varDecl);
aA_type aA_varDecl2Type(aA_varDecl varDecl);
bool typeCheck(aA_type type);
string type2Name(aA_type type);
aA_type id2Type(std::ostream *out, A_pos pos ,string id);
bool localExist(string name);
aA_type local2Type(string name);
void addLocal2Type(string name,aA_type type);
void beforeBlock();
void afterBlock();
bool localArrDeclExist(string name);
bool localArrDefExist(string name);
void addLocalArrDecl(string name,aA_varDeclArray varDeclArray);
void addLocalArrDef(string name,aA_varDefArray varDefArray);
aA_type localArr2Type(string name);
aA_type rightVal2Type(std::ostream* out,aA_rightVal rightVal);
aA_type arithExpr2Type(std::ostream* out,aA_arithExpr arithExpr);