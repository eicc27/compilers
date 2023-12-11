#include "ast2llvm.h"
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include "llvm_ir.h"
#include "temp.h"
#include <cassert>
#include <cstdio>
#include <iostream>
#include <list>
#include <ostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;
using namespace LLVMIR;

static unordered_map<string, FuncType> funcReturnMap;
static unordered_map<string, StructInfo> structInfoMap;
static unordered_map<string, Name_name *> globalVarMap;
static unordered_map<string, Temp_temp *> localVarMap;
static list<L_stm *> emit_irs;

void printIrs(list<L_stm *> &irs) {
  for (auto &ir : irs) {
    printf("IR type: %d", ir->type);
  }
}

LLVMIR::L_prog *ast2llvm(aA_program p) {
  cout << "first stage" << endl;
  auto defs = ast2llvmProg_first(p);
  cout << "second stage" << endl;
  auto funcs = ast2llvmProg_second(p);
  vector<L_func *> funcs_block;
  for (auto f : funcs) {
    funcs_block.push_back(ast2llvmFuncBlock(f));
  }
  cout << funcs_block.size() << endl;
  for (auto &f : funcs_block) {
    ast2llvm_moveAlloca(f);
  }
  return new L_prog(defs, funcs_block);
}

int ast2llvmRightVal_first(aA_rightVal r) {
  if (r == nullptr) {
    return 0;
  }
  switch (r->kind) {
  case A_arithExprValKind: {
    cout << "static arith" << endl;
    return ast2llvmArithExpr_first(r->u.arithExpr);
    break;
  }
  case A_boolExprValKind: {
    cout << "static bool" << endl;
    return ast2llvmBoolExpr_first(r->u.boolExpr);
    break;
  }
  default:
    break;
  }
  return 0;
}

int ast2llvmBoolExpr_first(aA_boolExpr b) {
  switch (b->kind) {
  case A_boolBiOpExprKind: {
    return ast2llvmBoolBiOpExpr_first(b->u.boolBiOpExpr);
    break;
  }
  case A_boolUnitKind: {
    return ast2llvmBoolUnit_first(b->u.boolUnit);
    break;
  }
  default:
    break;
  }
  return 0;
}

int ast2llvmBoolBiOpExpr_first(aA_boolBiOpExpr b) {
  int l = ast2llvmBoolExpr_first(b->left);
  int r = ast2llvmBoolExpr_first(b->right);
  if (b->op == A_and) {
    return l && r;
  } else {
    return l || r;
  }
}

int ast2llvmBoolUOpExpr_first(aA_boolUOpExpr b) {
  if (b->op == A_not) {
    return !ast2llvmBoolUnit_first(b->cond);
  }
  return 0;
}

int ast2llvmBoolUnit_first(aA_boolUnit b) {
  switch (b->kind) {
  case A_comOpExprKind: {
    return ast2llvmComOpExpr_first(b->u.comExpr);
    break;
  }
  case A_boolExprKind: {
    return ast2llvmBoolExpr_first(b->u.boolExpr);
    break;
  }
  case A_boolUOpExprKind: {
    return ast2llvmBoolUOpExpr_first(b->u.boolUOpExpr);
    break;
  }
  default:
    break;
  }
  return 0;
}

int ast2llvmComOpExpr_first(aA_comExpr c) {
  auto l = ast2llvmExprUnit_first(c->left);
  auto r = ast2llvmExprUnit_first(c->right);
  switch (c->op) {
  case A_lt: {
    return l < r;
    break;
  }
  case A_le: {
    return l <= r;
    break;
  }
  case A_gt: {
    return l > r;
    break;
  }
  case A_ge: {
    return l >= r;
    break;
  }
  case A_eq: {
    return l == r;
    break;
  }
  case A_ne: {
    return l != r;
    break;
  }
  default:
    break;
  }
  return 0;
}

int ast2llvmArithBiOpExpr_first(aA_arithBiOpExpr a) {
  auto l = ast2llvmArithExpr_first(a->left);
  auto r = ast2llvmArithExpr_first(a->right);
  switch (a->op) {
  case A_add: {
    return l + r;
    break;
  }
  case A_sub: {
    return l - r;
    break;
  }
  case A_mul: {
    return l * r;
    break;
  }
  case A_div: {
    return l / r;
    break;
  }
  default:
    break;
  }
  return 0;
}

int ast2llvmArithUExpr_first(aA_arithUExpr a) {
  if (a->op == A_neg) {
    return -ast2llvmExprUnit_first(a->expr);
  }
  return 0;
}

int ast2llvmArithExpr_first(aA_arithExpr a) {
  switch (a->kind) {
  case A_arithBiOpExprKind: {
    return ast2llvmArithBiOpExpr_first(a->u.arithBiOpExpr);
    break;
  }
  case A_exprUnitKind: {
    return ast2llvmExprUnit_first(a->u.exprUnit);
    break;
  }
  default:
    assert(0);
    break;
  }
  return 0;
}

int ast2llvmExprUnit_first(aA_exprUnit e) {
  if (e->kind == A_numExprKind) {
    return e->u.num;
  } else if (e->kind == A_arithExprKind) {
    return ast2llvmArithExpr_first(e->u.arithExpr);
  } else if (e->kind == A_arithUExprKind) {
    return ast2llvmArithUExpr_first(e->u.arithUExpr);
  } else {
    assert(0);
  }
  return 0;
}

std::vector<LLVMIR::L_def *> ast2llvmProg_first(aA_program p) {
  vector<L_def *> defs;
  defs.push_back(
      L_Funcdecl("getch", vector<TempDef>(), FuncType(ReturnType::INT_TYPE)));
  funcReturnMap.emplace("getch", FuncType(ReturnType::INT_TYPE));
  defs.push_back(
      L_Funcdecl("getint", vector<TempDef>(), FuncType(ReturnType::INT_TYPE)));
  funcReturnMap.emplace("getint", FuncType(ReturnType::INT_TYPE));
  defs.push_back(L_Funcdecl("putch",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  funcReturnMap.emplace("putch", FuncType(ReturnType::VOID_TYPE));
  defs.push_back(L_Funcdecl("putint",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  funcReturnMap.emplace("putint", FuncType(ReturnType::VOID_TYPE));
  defs.push_back(L_Funcdecl("putarray",
                            vector<TempDef>{TempDef(TempType::INT_TEMP),
                                            TempDef(TempType::INT_PTR, -1)},
                            FuncType(ReturnType::VOID_TYPE)));
  funcReturnMap.emplace("putarray", FuncType(ReturnType::VOID_TYPE));
  defs.push_back(L_Funcdecl("_sysy_starttime",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  funcReturnMap.emplace("_sysy_starttime", FuncType(ReturnType::VOID_TYPE));
  defs.push_back(L_Funcdecl("_sysy_stoptime",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  funcReturnMap.emplace("_sysy_stoptime", FuncType(ReturnType::VOID_TYPE));
  cout << "programElements size: " << p->programElements.size() << endl;
  for (const auto &v : p->programElements) {
    switch (v->kind) {
    case A_programNullStmtKind: {
      cout << "A_programNullStmtKind" << endl;
      break;
    }
    case A_programVarDeclStmtKind: {
      cout << "A_programVarDeclStmtKind" << endl;
      if (v->u.varDeclStmt->kind == A_varDeclKind) {
        if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclScalarKind) {
          if (v->u.varDeclStmt->u.varDecl->u.declScalar->type->type ==
              A_structTypeKind) {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                Name_newname_struct(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDecl->u.declScalar->id),
                    *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u
                         .structType));
            TempDef def(
                TempType::STRUCT_TEMP, 0,
                *v->u.varDeclStmt->u.varDecl->u.declScalar->type->u.structType);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, def,
                            vector<int>()));
          } else {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDecl->u.declScalar->id,
                Name_newname_int(Temp_newlabel_named(
                    *v->u.varDeclStmt->u.varDecl->u.declScalar->id)));
            TempDef def(TempType::INT_TEMP, 0);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declScalar->id, def,
                            vector<int>()));
          }
        } else if (v->u.varDeclStmt->u.varDecl->kind == A_varDeclArrayKind) {
          if (v->u.varDeclStmt->u.varDecl->u.declArray->type->type ==
              A_structTypeKind) {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDecl->u.declArray->id,
                Name_newname_struct_ptr(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDecl->u.declArray->id),
                    v->u.varDeclStmt->u.varDecl->u.declArray->len,
                    *v->u.varDeclStmt->u.varDecl->u.declArray->type->u
                         .structType));
            TempDef def(
                TempType::STRUCT_PTR,
                v->u.varDeclStmt->u.varDecl->u.declArray->len,
                *v->u.varDeclStmt->u.varDecl->u.declArray->type->u.structType);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id, def,
                            vector<int>()));
          } else {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDecl->u.declArray->id,
                Name_newname_int_ptr(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDecl->u.declArray->id),
                    v->u.varDeclStmt->u.varDecl->u.declArray->len));
            TempDef def(TempType::INT_PTR,
                        v->u.varDeclStmt->u.varDecl->u.declArray->len);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDecl->u.declArray->id, def,
                            vector<int>()));
          }
        } else {
          assert(0);
        }
      } else if (v->u.varDeclStmt->kind == A_varDefKind) {
        if (v->u.varDeclStmt->u.varDef->kind == A_varDefScalarKind) {
          if (v->u.varDeclStmt->u.varDef->u.defScalar->type->type ==
              A_structTypeKind) {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDef->u.defScalar->id,
                Name_newname_struct(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDef->u.defScalar->id),
                    *v->u.varDeclStmt->u.varDef->u.defScalar->type->u
                         .structType));
            TempDef def(
                TempType::STRUCT_TEMP, 0,
                *v->u.varDeclStmt->u.varDef->u.defScalar->type->u.structType);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defScalar->id, def,
                            vector<int>()));
          } else {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDef->u.defScalar->id,
                Name_newname_int(Temp_newlabel_named(
                    *v->u.varDeclStmt->u.varDef->u.defScalar->id)));
            TempDef def(TempType::INT_TEMP, 0);
            vector<int> init;
            init.push_back(ast2llvmRightVal_first(
                v->u.varDeclStmt->u.varDef->u.defScalar->val));
            defs.push_back(L_Globaldef(
                *v->u.varDeclStmt->u.varDef->u.defScalar->id, def, init));
          }
        } else if (v->u.varDeclStmt->u.varDef->kind == A_varDefArrayKind) {
          if (v->u.varDeclStmt->u.varDef->u.defArray->type->type ==
              A_structTypeKind) {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDef->u.defArray->id,
                Name_newname_struct_ptr(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDef->u.defArray->id),
                    v->u.varDeclStmt->u.varDef->u.defArray->len,
                    *v->u.varDeclStmt->u.varDef->u.defArray->type->u
                         .structType));
            TempDef def(
                TempType::STRUCT_PTR,
                v->u.varDeclStmt->u.varDef->u.defArray->len,
                *v->u.varDeclStmt->u.varDef->u.defArray->type->u.structType);
            defs.push_back(
                L_Globaldef(*v->u.varDeclStmt->u.varDef->u.defArray->id, def,
                            vector<int>()));
          } else {
            globalVarMap.emplace(
                *v->u.varDeclStmt->u.varDef->u.defArray->id,
                Name_newname_int_ptr(
                    Temp_newlabel_named(
                        *v->u.varDeclStmt->u.varDef->u.defArray->id),
                    v->u.varDeclStmt->u.varDef->u.defArray->len));
            TempDef def(TempType::INT_PTR,
                        v->u.varDeclStmt->u.varDef->u.defArray->len);
            vector<int> init;
            for (auto &el : v->u.varDeclStmt->u.varDef->u.defArray->vals) {
              init.push_back(ast2llvmRightVal_first(el));
            }
            defs.push_back(L_Globaldef(
                *v->u.varDeclStmt->u.varDef->u.defArray->id, def, init));
          }
        } else {
          assert(0);
        }
      } else {
        assert(0);
      }
      break;
    }
    case A_programStructDefKind: {
      cout << "A_programStructDefKind" << endl;
      StructInfo si;
      int off = 0;
      vector<TempDef> members;
      for (const auto &decl : v->u.structDef->varDecls) {
        if (decl->kind == A_varDeclScalarKind) {
          if (decl->u.declScalar->type->type == A_structTypeKind) {
            TempDef def(TempType::STRUCT_TEMP, 0,
                        *decl->u.declScalar->type->u.structType);
            MemberInfo info(off++, def);
            si.memberinfos.emplace(*decl->u.declScalar->id, info);
            members.push_back(def);
          } else {
            TempDef def(TempType::INT_TEMP, 0);
            MemberInfo info(off++, def);
            si.memberinfos.emplace(*decl->u.declScalar->id, info);
            members.push_back(def);
          }
        } else if (decl->kind == A_varDeclArrayKind) {
          if (decl->u.declArray->type->type == A_structTypeKind) {
            TempDef def(TempType::STRUCT_PTR, decl->u.declArray->len,
                        *decl->u.declArray->type->u.structType);
            MemberInfo info(off++, def);
            si.memberinfos.emplace(*decl->u.declArray->id, info);
            members.push_back(def);
          } else {
            TempDef def(TempType::INT_PTR, decl->u.declArray->len);
            MemberInfo info(off++, def);
            si.memberinfos.emplace(*decl->u.declArray->id, info);
            members.push_back(def);
          }
        } else {
          assert(0);
        }
      }
      structInfoMap.emplace(*v->u.structDef->id, std::move(si));
      defs.push_back(L_Structdef(*v->u.structDef->id, members));
      break;
    }
    case A_programFnDeclStmtKind: {
      cout << "A_programFnDeclStmtKind" << endl;
      FuncType type;
      if (v->u.fnDeclStmt->fnDecl->type == nullptr) {
        type.type = ReturnType::VOID_TYPE;
      } else if (v->u.fnDeclStmt->fnDecl->type->type == A_nativeTypeKind) {
        type.type = ReturnType::INT_TYPE;
      } else if (v->u.fnDeclStmt->fnDecl->type->type == A_structTypeKind) {
        type.type = ReturnType::STRUCT_TYPE;
        type.structname = *v->u.fnDeclStmt->fnDecl->type->u.structType;
      } else {
        assert(0);
      }
      if (funcReturnMap.find(*v->u.fnDeclStmt->fnDecl->id) ==
          funcReturnMap.end())
        funcReturnMap.emplace(*v->u.fnDeclStmt->fnDecl->id, type);
      vector<TempDef> args;
      for (const auto &decl : v->u.fnDeclStmt->fnDecl->paramDecl->varDecls) {
        if (decl->kind == A_varDeclScalarKind) {
          if (decl->u.declScalar->type->type == A_structTypeKind) {
            TempDef def(TempType::STRUCT_PTR, 0,
                        *decl->u.declScalar->type->u.structType);
            args.push_back(def);
          } else {
            TempDef def(TempType::INT_TEMP, 0);
            args.push_back(def);
          }
        } else if (decl->kind == A_varDeclArrayKind) {
          if (decl->u.declArray->type->type == A_structTypeKind) {
            TempDef def(TempType::STRUCT_PTR, -1,
                        *decl->u.declArray->type->u.structType);
            args.push_back(def);
          } else {
            TempDef def(TempType::INT_PTR, -1);
            args.push_back(def);
          }
        } else {
          assert(0);
        }
      }
      defs.push_back(L_Funcdecl(*v->u.fnDeclStmt->fnDecl->id, args, type));
      break;
    }
    case A_programFnDefKind: {
      cout << "A_programFnDefKind" << endl;
      if (funcReturnMap.find(*v->u.fnDef->fnDecl->id) == funcReturnMap.end()) {
        FuncType type;
        if (v->u.fnDef->fnDecl->type == nullptr) {
          type.type = ReturnType::VOID_TYPE;
        } else if (v->u.fnDef->fnDecl->type->type == A_nativeTypeKind) {
          type.type = ReturnType::INT_TYPE;
        } else if (v->u.fnDef->fnDecl->type->type == A_structTypeKind) {
          type.type = ReturnType::STRUCT_TYPE;
          type.structname = *v->u.fnDef->fnDecl->type->u.structType;
        } else {
          assert(0);
        }
        funcReturnMap.emplace(*v->u.fnDef->fnDecl->id, std::move(type));
      }
      break;
    }
    default:
      assert(0);
      break;
    }
  }
  return defs;
}

std::vector<Func_local *> ast2llvmProg_second(aA_program p) {
  // TODO, generate llvm ir for function implementation
  auto vec = vector<Func_local *>();
  for (const auto &v : p->programElements) {
    switch (v->kind) {
    case A_programFnDefKind: {
      cout << *v->u.fnDef->fnDecl->id << endl;
      localVarMap.clear();
      vec.push_back(ast2llvmFunc(v->u.fnDef));
      break;
    }
    default: {
      break;
    }
    }
  }
  cout << "size: " << vec.size() << endl;
  return vec;
}

vector<L_stm *> Gen_varDeclStmtKind(aA_varDeclStmt stmt) {
  vector<L_stm *> res;
  cout << "Gen_varDeclStmtKind" << endl;
  if (stmt->kind == A_varDeclStmtType::A_varDeclKind) {
    cout << "\tA_varDeclKind" << endl;
    aA_varDecl varDecl = stmt->u.varDecl;
    if (varDecl->kind == A_varDeclType::A_varDeclScalarKind) {
      aA_varDeclScalar declScalar = varDecl->u.declScalar;
      if (declScalar->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(0);
        cout << "VarDecl->Scalar->Int id: " << *declScalar->id << endl;
        localVarMap.emplace(*declScalar->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      } else if (declScalar->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(0, *declScalar->type->u.structType);
        cout << "VarDecl->Scalar->Struct id: " << *declScalar->id << endl;
        localVarMap.emplace(*declScalar->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      }
    } else if (varDecl->kind == A_varDeclType::A_varDeclArrayKind) {
      aA_varDeclArray declArray = varDecl->u.declArray;
      if (declArray->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(declArray->len);
        cout << "VarDecl->Array->Int id: " << *declArray->id << endl;
        localVarMap.emplace(*declArray->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      } else if (declArray->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(declArray->len,
                                           *declArray->type->u.structType);
        cout << "VarDecl->Array->Struct id: " << *declArray->id << endl;
        localVarMap.emplace(*declArray->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      }
    }
  } else if (stmt->kind == A_varDeclStmtType::A_varDefKind) {
    cout << "\tA_varDefKind" << endl;
    aA_varDef varDef = stmt->u.varDef;
    if (varDef->kind == A_varDefType::A_varDefScalarKind) {
      cout << "\t\tA_varDefScalarKind" << endl;
      aA_varDefScalar defScalar = varDef->u.defScalar;
      if (defScalar->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(0);
        auto opt = AS_Operand_Temp(tmp);
        cout << "defScalar->nativeType->id: " << *defScalar->id << endl;
        localVarMap.emplace(*defScalar->id, tmp);
        res.push_back(L_Alloca(opt));
        cout << "defScalar->val->kind: " << defScalar->val->kind << endl;
        auto op = ast2llvmRightVal(defScalar->val);
        res.push_back(L_Store(op, opt));
      } else if (defScalar->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(0, *defScalar->type->u.structType);
        auto opt = AS_Operand_Temp(tmp);
        cout << "defScalar->structType->id: " << *defScalar->id << endl;
        localVarMap.emplace(*defScalar->id, tmp);
        res.push_back(L_Alloca(opt));
        auto op = ast2llvmRightVal(defScalar->val);
        res.push_back(L_Store(op, opt));
      }
    } else if (varDef->kind == A_varDefType::A_varDefArrayKind) {
      cout << "\t\tA_varDefArrayKind" << endl;
      aA_varDefArray defArray = varDef->u.defArray;
      if (defArray->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(defArray->len);
        auto opt = AS_Operand_Temp(tmp);
        cout << "defArray->nativeType->id: " << *defArray->id << endl;
        localVarMap.emplace(*defArray->id, tmp);
        res.push_back(L_Alloca(opt));
        auto i = 0;
        for (auto val : defArray->vals) {
          auto op = ast2llvmRightVal(val);
          // get the bias of the array
          auto idx_ptr = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
          res.push_back(L_Gep(idx_ptr, opt, AS_Operand_Const(i++)));
          res.push_back(L_Store(op, idx_ptr));
        }
      } else if (defArray->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(defArray->len,
                                           *defArray->type->u.structType);
        auto opt = AS_Operand_Temp(tmp);
        cout << "defArray->structType->id: " << *defArray->id << endl;
        localVarMap.emplace(*defArray->id, tmp);
        res.push_back(L_Alloca(opt));
        auto i = 0;
        for (auto val : defArray->vals) {
          auto op = ast2llvmRightVal(val);
          // get the bias of the array
          auto idx_ptr = AS_Operand_Temp(
              Temp_newtemp_struct_ptr(0, *defArray->type->u.structType));
          res.push_back(L_Gep(idx_ptr, opt, AS_Operand_Const(i++)));
          res.push_back(L_Store(op, idx_ptr));
        }
      }
    } else {
      assert(0);
    }
  } else {
    assert(0);
  }
  return res;
}

vector<L_stm *> Gen_assignStmtKind(aA_assignStmt stmt) {
  auto left = ast2llvmLeftVal(stmt->leftVal); // Geps in llvm
  auto right = ast2llvmRightVal(stmt->rightVal);
  vector<L_stm *> res;
  res.insert(res.end(), emit_irs.begin(), emit_irs.end());
  emit_irs.clear();
  res.push_back(L_Store(right, left));
  return res;
}

// 生成函数调用的L_stm
list<LLVMIR::L_stm *> Gen_callStmtKind(aA_callStmt callStmt) {
  aA_fnCall fnCall = callStmt->fnCall;
  string fnName = *(fnCall->fn);
  vector<AS_operand *> args;
  list<LLVMIR::L_stm *> instrs;
  // 对参数列表中的每一个参数(右值)进行转换，TODO
  for (aA_rightVal rightVal : fnCall->vals) {
    cout << "call args" << endl;
    args.emplace_back(ast2llvmRightVal(rightVal));
    instrs.insert(instrs.end(), emit_irs.begin(), emit_irs.end());
    emit_irs.clear();
  }
  // 保证函数一定声明或者定义过
  if (funcReturnMap.count(fnName) == 0) {
    assert(0);
  }
  FuncType funcType = funcReturnMap[fnName];
  if (funcType.type == ReturnType::INT_TYPE) {
    Temp_temp *intTemp = Temp_newtemp_int();
    instrs.emplace_back(L_Call(fnName, AS_Operand_Temp(intTemp), args));
  } else if (funcType.type == ReturnType::STRUCT_TYPE) {
    Temp_temp *structTemp = Temp_newtemp_struct_ptr(0, funcType.structname);
    instrs.emplace_back(L_Call(fnName, AS_Operand_Temp(structTemp), args));
  } else if (funcType.type == ReturnType::VOID_TYPE) {
    instrs.emplace_back(L_Voidcall(fnName, args));
  } else {
    assert(0);
  }
  return instrs;
}

list<LLVMIR::L_stm *> Gen_ifStmtKind(aA_ifStmt ifStmt,
                                     Temp_label *continueLabel,
                                     Temp_label *breakLabel) {
  cout << "Gen_ifStmtKind" << endl;
  list<LLVMIR::L_stm *> instrs;
  aA_boolExpr boolExpr = ifStmt->boolExpr;
  // 1.先生成ifLabel,elseLabel,以及完成if-else块后的代码对应的originBlockContinueLabel(oLabel)
  Temp_label *ifLabel = Temp_newlabel();
  Temp_label *elseLabel = Temp_newlabel();
  Temp_label *originBlockContinueLabel = Temp_newlabel();
  // 2.添加判断跳转的指令，是跳转到ifLabel，还是elseLabel
  emit_irs.clear();
  AS_operand *op = ast2llvmBoolExpr(boolExpr, ifLabel, elseLabel); // unsure
  instrs.insert(instrs.end(), emit_irs.begin(),
                emit_irs.end()); // ast2llvmBoolExpr内部处理的命令
  emit_irs.clear();              // ast2llvmBoolExpr内部处理的命令
  // 3.转换if块的指令，并且在if块的最后添加跳转到originBlockContinueLabel
  list<LLVMIR::L_stm *> if_instrs =
      Gen_Block(ifLabel, continueLabel, breakLabel, &ifStmt->ifStmts);
  if_instrs.emplace_back(L_Jump(originBlockContinueLabel));
  // 将转化好的if块指令放入真正的指令集中
  instrs.insert(instrs.end(), if_instrs.begin(), if_instrs.end());
  // 4.转换else块的指令，无论else块是否存在，都要在最后添加跳转到originBlockContinueLabel
  list<LLVMIR::L_stm *> else_instrs =
      Gen_Block(elseLabel, continueLabel, breakLabel, &ifStmt->elseStmts);
  else_instrs.emplace_back(L_Jump(originBlockContinueLabel));
  // 将转化好的else块指令放入真正的指令集中
  instrs.insert(instrs.end(), else_instrs.begin(), else_instrs.end());
  // 5.跳出if-else块后，需要到originBlockContinueLabel下继续执行，因此需要originBlockContinueLabel进行标识
  instrs.emplace_back(L_Label(originBlockContinueLabel));
  return instrs;
}

list<LLVMIR::L_stm *> Gen_whileStmtKind(aA_whileStmt whileStmt) {
  list<LLVMIR::L_stm *> instrs;
  Temp_label *whileLabel = Temp_newlabel();
  Temp_label *breakLabel = Temp_newlabel();
  Temp_label *compareLabel = Temp_newlabel();
  instrs.emplace_back(L_Jump(compareLabel));
  instrs.emplace_back(L_Label(compareLabel));
  AS_operand *op =
      ast2llvmBoolExpr(whileStmt->boolExpr, whileLabel, breakLabel);
  instrs.insert(instrs.end(), emit_irs.begin(),
                emit_irs.end()); // ast2llvmBoolExpr内部处理的命令
  emit_irs.clear();
  list<LLVMIR::L_stm *> while_instrs =
      Gen_Block(whileLabel, compareLabel, breakLabel, &whileStmt->whileStmts);
  instrs.insert(instrs.end(), while_instrs.begin(), while_instrs.end());
  instrs.emplace_back(L_Jump(compareLabel));
  instrs.emplace_back(L_Label(breakLabel));
  return instrs;
}

// 将代码块的处理独立出来
list<LLVMIR::L_stm *> Gen_Block(Temp_label *blockLabel,
                                Temp_label *continueLabel,
                                Temp_label *breakLabel,
                                vector<aA_codeBlockStmt> *stmts) {
  list<LLVMIR::L_stm *> instrs;
  if (stmts == nullptr) {
    return instrs;
  }
  instrs.push_back(L_Label(blockLabel));
  auto i = 0;
  for (auto stmt : *stmts) {
    auto isLast =
        ++i == stmts->size(); // 如果最后一个block是代码块（含有if/else,
                              // while），必须向最后的label中填写return语句
    switch (stmt->kind) {
    case A_nullStmtKind:
      break;
    case A_varDeclStmtKind: {
      auto v = Gen_varDeclStmtKind(stmt->u.varDeclStmt);
      instrs.insert(instrs.end(), emit_irs.begin(), emit_irs.end());
      instrs.insert(instrs.end(), v.begin(), v.end());
      emit_irs.clear();
      break;
    }
    case A_assignStmtKind: {
      auto v = Gen_assignStmtKind(stmt->u.assignStmt);
      instrs.insert(instrs.end(), v.begin(), v.end());
      break;
    }
    case A_callStmtKind: {
      auto v = Gen_callStmtKind(stmt->u.callStmt);
      instrs.insert(instrs.end(), v.begin(), v.end());
      break;
    }
    case A_ifStmtKind: {
      auto v = Gen_ifStmtKind(stmt->u.ifStmt, continueLabel, breakLabel);
      instrs.insert(instrs.end(), v.begin(), v.end());
      if (isLast)
        instrs.push_back(L_Ret(AS_Operand_Const(0)));
      break;
    }
    case A_whileStmtKind: {
      auto v = Gen_whileStmtKind(stmt->u.whileStmt);
      instrs.insert(instrs.end(), v.begin(), v.end());
      if (isLast)
        instrs.push_back(L_Ret(AS_Operand_Const(0)));
      break;
    }
    case A_returnStmtKind: {
      cout << "ReturnStmtKind" << endl;
      auto u = stmt->u.returnStmt;
      auto ret = u->retVal;
      auto op = ast2llvmRightVal(ret);
      instrs.insert(instrs.end(), emit_irs.begin(), emit_irs.end());
      cout << "emit irs: " << emit_irs.size() << endl;
      emit_irs.clear();
      instrs.push_back(L_Ret(op));
      break;
    }
    case A_continueStmtKind: {
      if (continueLabel == nullptr) {
        break;
      }
      instrs.push_back(L_Jump(continueLabel));
      break;
    }
    case A_breakStmtKind: {
      if (breakLabel == nullptr) {
        break;
      }
      instrs.push_back(L_Jump(breakLabel));
      break;
    }
    default:
      break;
    }
    if (isLast && stmt->kind != A_returnStmtKind) { // 如果函数最后没有ret语句
      instrs.push_back(L_Ret(nullptr)); // 加上ret void
    }
  }
  return instrs;
}

Func_local *ast2llvmFunc(aA_fnDef f) {
  // 首先获取函数的参数，转成temp_temp
  auto vars = f->fnDecl->paramDecl->varDecls;
  vector<Temp_temp *> args;
  auto type = f->fnDecl->type;
  FuncType ret;
  if (type == nullptr) {
    ret.type = ReturnType::VOID_TYPE;
  } else if (type->type == A_nativeTypeKind) {
    ret.type = ReturnType::INT_TYPE;
  } else if (type->type == A_structTypeKind) {
    ret.type = ReturnType::STRUCT_TYPE;
    ret.structname = *type->u.structType;
  } else {
    assert(0);
  }
  int num = 0;
  cout << "vars size:" << vars.size() << endl;
  for (auto var : vars) {
    cout << "\tvar kind: " << var->kind << endl;
    TempType kind;
    int len;
    string structname;
    Temp_temp *tmp;
    switch (var->kind) {
    case A_varDeclScalarKind: {
      // cout << var->u.declScalar->type->type << endl;
      if (var->u.declScalar->type->type == A_structTypeKind) {
        kind = TempType::STRUCT_TEMP;
        len = 0;
        structname = *var->u.declScalar->type->u.structType;
        tmp = Temp_newtemp_struct(structname);
        // register into local var map
        localVarMap.emplace(*var->u.declScalar->id, tmp);
        printf("%s: %s\n", var->u.declScalar->id->c_str(), structname.c_str());
      } else {
        kind = TempType::INT_TEMP;
        tmp = Temp_newtemp_int();
        // register into local var map
        localVarMap.emplace(*var->u.declScalar->id, tmp);
        printf("%s: int\n", var->u.declScalar->id->c_str());
      }
      break;
    }
    case A_varDeclArrayKind: {
      if (var->u.declArray->type->type == A_structTypeKind) {
        kind = TempType::STRUCT_PTR;
        len = var->u.declArray->len;
        structname = *var->u.declArray->type->u.structType;
        // register into local var map
        tmp = Temp_newtemp_struct_ptr(len, structname);
        localVarMap.emplace(*var->u.declArray->id, tmp);
      } else {
        kind = TempType::INT_PTR;
        len = var->u.declArray->len;
        structname = "";
        // register into local var map
        tmp = Temp_newtemp_int_ptr(var->u.declArray->len);
        localVarMap.emplace(*var->u.declArray->id, tmp);
      }
      break;
    }
    default:
      assert(0);
    }
    args.push_back(tmp);
  }
  auto funLabel = Temp_newlabel();
  auto instrs = Gen_Block(funLabel, nullptr, nullptr, &f->stmts);
  auto func = new Func_local(*f->fnDecl->id, ret, args, instrs);
  return func;
}

void ast2llvmBlock(aA_codeBlockStmt b, Temp_label *con_label,
                   Temp_label *bre_label) {}

AS_operand *ast2llvmRightVal(aA_rightVal r) {
  if (r == nullptr) {
    return nullptr;
  }
  cout << "kind: " << endl;
  switch (r->kind) {
  case A_arithExprValKind: {
    cout << "arithmetic" << endl;
    return ast2llvmArithExpr(r->u.arithExpr);
    break;
  }
  case A_boolExprValKind: {
    cout << "bool" << endl;
    return ast2llvmBoolExpr(r->u.boolExpr);
    break;
  }
  default:
    break;
  }
  return nullptr;
}

AS_operand *ast2llvmLeftVal(aA_leftVal l) {
  switch (l->kind) {
  case A_leftValType::A_arrValKind: {
    auto u = l->u.arrExpr;
    auto arr = ast2llvmLeftVal(u->arr);
    auto idx = ast2llvmIndexExpr(u->idx);

    cout << "error" << endl;
    AS_operand *res;
    if (arr->kind == OperandKind::TEMP) {
      auto u = arr->u.TEMP;
      if (u->type == TempType::INT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (u->type == TempType::STRUCT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_struct_ptr(u->len, u->structname));
      } else {
        assert(0);
      }
    } else if (arr->kind == OperandKind::NAME) {

      auto u = arr->u.NAME;
      if (u->type == TempType::INT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (u->type == TempType::STRUCT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_struct_ptr(u->len, u->structname));
      } else {
        assert(0);
      }
    } else {
      assert(0);
    }
    auto stm = L_Gep(res, arr, idx);
    emit_irs.push_back(stm);
    return res;
  }
  case A_leftValType::A_memberValKind: {
    cout << "MemberValKind" << endl;
    auto u = l->u.memberExpr;
    auto structid = ast2llvmLeftVal(u->structId);
    cout << "found structid" << endl;
    auto structname = structid->kind == OperandKind::NAME
                          ? structid->u.NAME->structname
                          : structid->u.TEMP->structname;
    cout << "found structname: " << structname << endl;
    auto m = structInfoMap.find(structname)->second;
    auto member = m.memberinfos.find(*u->memberId)->second;
    AS_operand *res;
    if (member.def.kind == TempType::STRUCT_PTR) {
      res = AS_Operand_Temp(
          Temp_newtemp_struct_ptr(member.def.len, member.def.structname));
    } else if (member.def.kind == TempType::STRUCT_TEMP) {
      res = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, member.def.structname));
    } else if (member.def.kind == TempType::INT_PTR) {
      res = AS_Operand_Temp(Temp_newtemp_int_ptr(member.def.len));
    } else if (member.def.kind == TempType::INT_TEMP) {
      res = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    } else {
      assert(0);
    }
    auto stm = L_Gep(res, structid, AS_Operand_Const(member.offset));
    emit_irs.push_back(stm);
    return res;
  }
  case A_leftValType::A_varValKind: {
    cout << "VarValKind" << endl;
    auto u = l->u.id;
    cout << "found id: " << *u << endl;
    // find var in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      AS_operand *ptrOp = AS_Operand_Temp(tmp);
      return ptrOp;
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      AS_operand *ptrOp = AS_Operand_Name(name);

      return ptrOp;
    }
    assert(0);
  }
  }
}

AS_operand *ast2llvmIndexExpr(aA_indexExpr index) {
  switch (index->kind) {
  case A_indexExprKind::A_idIndexKind: {
    auto u = index->u.id;
    // find the id in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      AS_operand *ptrOp = AS_Operand_Temp(tmp);
      AS_operand *dstOp;
      if (tmp->type == TempType::INT_PTR) {
        dstOp = AS_Operand_Temp(Temp_newtemp_int());
        emit_irs.emplace_back(L_Load(dstOp, ptrOp));
        return dstOp;
      } else if (tmp->type == TempType::STRUCT_PTR) {
        return ptrOp;
      }
      return dstOp;
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      AS_operand *ptrOp = AS_Operand_Name(name);
      AS_operand *dstOp;
      if (name->type == TempType::INT_TEMP) {
        dstOp = AS_Operand_Temp(Temp_newtemp_int());
      } else if (name->type == TempType::STRUCT_TEMP) {
        dstOp = AS_Operand_Temp(Temp_newtemp_struct(name->structname));
      }
      emit_irs.emplace_back(L_Load(dstOp, ptrOp));
      return dstOp;
    }
  }
  case A_indexExprKind::A_numIndexKind: {
    return AS_Operand_Const(index->u.num);
  }
  }
}

AS_operand *ast2llvmBoolExpr(aA_boolExpr b, Temp_label *true_label,
                             Temp_label *false_label) {
  switch (b->kind) {
  case A_boolBiOpExprKind: {
    return ast2llvmBoolBiOpExpr(b->u.boolBiOpExpr, true_label, false_label);
  }
  case A_boolUnitKind: {
    return ast2llvmBoolUnit(b->u.boolUnit, true_label, false_label);
  }
  }
}

AS_operand *ast2llvmBoolBiOpExpr(aA_boolBiOpExpr b, Temp_label *true_label,
                                 Temp_label *false_label) {
  // 1.先给定标签,leftLabel是指布尔表达式中某一个||或者&&的左侧部分
  Temp_label *leftLabel = Temp_newlabel();
  Temp_label *rightLabel = Temp_newlabel();
  emit_irs.emplace_back(L_Jump(leftLabel));
  if (b->op == A_boolBiOp::A_and) {
    emit_irs.emplace_back(L_Label(leftLabel));
    AS_operand *left = ast2llvmBoolExpr(b->left, rightLabel, false_label);
    emit_irs.emplace_back(L_Label(rightLabel));
    AS_operand *right = ast2llvmBoolExpr(b->right, true_label, false_label);
  } else if (b->op == A_boolBiOp::A_or) {
    emit_irs.emplace_back(L_Label(leftLabel));
    AS_operand *left = ast2llvmBoolExpr(b->left, true_label, rightLabel);
    emit_irs.emplace_back(L_Label(rightLabel));
    AS_operand *right = ast2llvmBoolExpr(b->right, true_label, false_label);
  }
  return AS_Operand_Temp(Temp_newtemp_int_ptr(0));
  // auto left = ast2llvmBoolExpr(b->left, true_label, false_label);
  // auto right = ast2llvmBoolExpr(b->right, true_label, false_label);
  // auto l1 = Temp_newlabel();
  // auto l2 = Temp_newlabel();
  // auto l3 = Temp_newlabel();
  // L_stm *entry;
  // auto jump = L_Jump(l3);
  // L_stm *end;
  // auto dst = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
  // if (b->op == A_and) {
  //   entry = L_Cjump(left, l2, l3);

  //   end = L_Phi(dst,
  //               vector<pair<AS_operand *, Temp_label *>>{
  //                   make_pair(AS_Operand_Const(0), l1), make_pair(right,
  //                   l2)});
  // } else {
  //   entry = L_Cjump(left, l3, l2);
  //   end = L_Phi(dst,
  //               vector<pair<AS_operand *, Temp_label *>>{
  //                   make_pair(AS_Operand_Const(1), l1), make_pair(right,
  //                   l2)});
  // }
  // auto stm = L_Cjump(dst, true_label, false_label);
  // emit_irs.push_back(L_Label(l1));
  // emit_irs.push_back(entry);
  // emit_irs.push_back(L_Label(l2));
  // emit_irs.push_back(jump);
  // emit_irs.push_back(L_Label(l3));
  // emit_irs.push_back(end);
  // if (true_label != nullptr && false_label != nullptr)
  //   emit_irs.push_back(stm);
  // return dst;
}

AS_operand *ast2llvmBoolUnit(aA_boolUnit b, Temp_label *true_label,
                             Temp_label *false_label) {
  switch (b->kind) {
  case A_comOpExprKind: {
    return ast2llvmComOpExpr(b->u.comExpr, true_label, false_label);
  }
  case A_boolExprKind: {
    return ast2llvmBoolExpr(b->u.boolExpr, true_label, false_label);
  }
  case A_boolUOpExprKind: {
    return ast2llvmBoolUOpExpr(b->u.boolUOpExpr, true_label, false_label);
  }
  }
}

AS_operand *ast2llvmComOpExpr(aA_comExpr c, Temp_label *true_label,
                              Temp_label *false_label) {
  auto left = ast2llvmExprUnit(c->left);
  auto right = ast2llvmExprUnit(c->right);
  L_relopKind kind;
  switch (c->op) {
  case A_comOp::A_lt: {
    kind = L_relopKind::T_lt;
    break;
  }
  case A_comOp::A_le: {
    kind = L_relopKind::T_le;
    break;
  }
  case A_comOp::A_gt: {
    kind = L_relopKind::T_gt;
    break;
  }
  case A_comOp::A_ge: {
    kind = L_relopKind::T_ge;
    break;
  }
  case A_comOp::A_eq: {
    kind = L_relopKind::T_eq;
    break;
  }
  case A_comOp::A_ne: {
    kind = L_relopKind::T_ne;
    break;
  }
  }
  auto dst = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
  auto stm = L_Cmp(kind, left, right, dst); // dst is int1
  emit_irs.push_back(stm);
  if (true_label == nullptr || false_label == nullptr) {
    return dst;
  }
  auto jmp = L_Cjump(dst, true_label, false_label);
  emit_irs.push_back(jmp);
  return dst;
}

AS_operand *ast2llvmBoolUOpExpr(aA_boolUOpExpr b, Temp_label *true_label,
                                Temp_label *false_label) {
  if (b->op != A_not)
    assert(0);
  return ast2llvmBoolUnit(b->cond, false_label, true_label);
}

AS_operand *ast2llvmArithBiOpExpr(aA_arithBiOpExpr a) {
  auto left = ast2llvmArithExpr(a->left);
  auto right = ast2llvmArithExpr(a->right);
  L_binopKind kind;
  switch (a->op) {
  case A_add: {
    kind = L_binopKind::T_plus;
    break;
  }
  case A_sub: {
    kind = L_binopKind::T_minus;
    break;
  }
  case A_mul: {
    kind = L_binopKind::T_mul;
    break;
  }
  case A_div: {
    kind = L_binopKind::T_div;
    break;
  }
  }
  auto op = AS_Operand_Temp(Temp_newtemp_int()); // only int can be arith
  auto stm = L_Binop(kind, left, right, op);
  emit_irs.push_back(stm);
  return op;
}

AS_operand *ast2llvmArithUExpr(aA_arithUExpr a) {
  if (a->op != A_arithUOp::A_neg) // the only possible unary operator
    assert(0);
  auto expr = ast2llvmExprUnit(a->expr);
  auto left = AS_Operand_Const(0);
  emit_irs.push_back(L_Alloca(left));
  auto op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
  auto stm = L_Binop(L_binopKind::T_minus, left, expr, op);
  emit_irs.push_back(stm);
  return op;
}

AS_operand *ast2llvmArithExpr(aA_arithExpr a) {
  switch (a->kind) {
  case A_arithBiOpExprKind: {
    return ast2llvmArithBiOpExpr(a->u.arithBiOpExpr);
    break;
  }
  case A_exprUnitKind: {
    return ast2llvmExprUnit(a->u.exprUnit);
    break;
  }
  default:
    break;
  }
  return nullptr;
}

AS_operand *ast2llvmExprUnit(aA_exprUnit e) {
  switch (e->kind) {
  case A_numExprKind: {
    auto u = e->u.num;
    return AS_Operand_Const(u);
  }
  case A_idExprKind: {
    auto u = e->u.id;
    cout << "idExprkind, id: " << *u << endl;
    // find the id in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      cout << "found " << *u << " in local" << endl;
      auto tmp = local->second;
      AS_operand *ptrOp = AS_Operand_Temp(tmp);
      AS_operand *dstOp;
      if (tmp->type == TempType::INT_PTR) {
        dstOp = AS_Operand_Temp(Temp_newtemp_int());
        emit_irs.emplace_back(L_Load(dstOp, ptrOp));
        return dstOp;
      } else if (tmp->type == TempType::STRUCT_PTR) {
        return ptrOp;
      } else if (tmp->type == TempType::INT_TEMP ||
                 tmp->type == TempType::STRUCT_TEMP) {
        return ptrOp;
      }
      return dstOp;
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      AS_operand *ptrOp = AS_Operand_Name(name);
      AS_operand *dstOp;
      if (name->type == TempType::INT_TEMP) {
        dstOp = AS_Operand_Temp(Temp_newtemp_int());
      } else if (name->type == TempType::STRUCT_TEMP) {
        return ptrOp;
      } else if (name->type == TempType::INT_PTR) {
        return ptrOp;
      } else if (name->type == TempType::STRUCT_PTR) {
        return ptrOp;
      } else {
        assert(0);
      }
      emit_irs.emplace_back(L_Load(dstOp, ptrOp));
      return dstOp;
    }
    assert(0); // not found, raise error
  }
  case A_arithExprKind: {
    return ast2llvmArithExpr(e->u.arithExpr);
  }
  case A_fnCallKind: {
    auto u = e->u.callExpr;
    auto fn = funcReturnMap.find(*u->fn)->second;
    AS_operand *op;
    if (fn.type == ReturnType::INT_TYPE) {
      op = AS_Operand_Temp(Temp_newtemp_int());
    } else if (fn.type == ReturnType::STRUCT_TYPE) {
      op = AS_Operand_Temp(Temp_newtemp_struct(fn.structname));
    } else {
      op = nullptr;
    }
    vector<AS_operand *> args;
    for (auto val : u->vals) {
      args.push_back(ast2llvmRightVal(val));
    }
    auto stm = L_Call(*u->fn, op, args);
    emit_irs.push_back(stm);
    return op;
  }
  case A_arrayExprKind: {
    auto u = e->u.arrayExpr;
    AS_operand *op;
    AS_operand *newop;
    auto lval = ast2llvmLeftVal(u->arr);
    auto idx = ast2llvmIndexExpr(u->idx);
    if (lval->kind == OperandKind::TEMP) {
      auto tmp = lval->u.TEMP;
      if (tmp->type == TempType::INT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
        newop = AS_Operand_Temp(Temp_newtemp_int());
        auto stm = L_Gep(op, lval, idx);
        emit_irs.push_back(stm);
        emit_irs.push_back(L_Load(newop, op));
      } else if (tmp->type == TempType::STRUCT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, tmp->structname));
        newop = op;
        auto stm = L_Gep(op, lval, idx);
        emit_irs.push_back(stm);
      } else {
        assert(0);
      }
    } else if (lval->kind == OperandKind::NAME) {
      auto name = lval->u.NAME;
      if (name->type == TempType::INT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
        newop = AS_Operand_Temp(Temp_newtemp_int());
        auto stm = L_Gep(op, lval, idx);
        emit_irs.push_back(stm);
        emit_irs.push_back(L_Load(newop, op));
      } else if (name->type == TempType::STRUCT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, name->structname));
        newop = op;
        auto stm = L_Gep(op, lval, idx);
        emit_irs.push_back(stm);
      } else {
        assert(0);
      }
    } else
      assert(0);
    return newop;
  }
  case A_memberExprKind: {
    cout << "MemberExprKind: " << endl;
    auto u = e->u.memberExpr;
    auto lval = ast2llvmLeftVal(u->structId);
    cout << "found lval" << endl;
    auto name = lval->kind == OperandKind::NAME ? lval->u.NAME->structname
                                                : lval->u.TEMP->structname;
    auto structinfo = structInfoMap.find(name)->second;
    cout << "found structinfo: " << name << endl;
    auto memberinfo = structinfo.memberinfos.find(*u->memberId)->second;
    cout << "found memberinfo" << endl;
    AS_operand *op;
    AS_operand *newop;
    if (memberinfo.def.kind == TempType::INT_TEMP) {
      op = AS_Operand_Temp(Temp_newtemp_int());
      newop = AS_Operand_Temp(Temp_newtemp_int());
    } else if (memberinfo.def.kind == TempType::STRUCT_TEMP) {
      op = AS_Operand_Temp(Temp_newtemp_struct(memberinfo.def.structname));
      newop = AS_Operand_Temp(Temp_newtemp_struct(memberinfo.def.structname));
    } else if (memberinfo.def.kind == TempType::INT_PTR) {
      op = AS_Operand_Temp(Temp_newtemp_int_ptr(memberinfo.def.len));
      newop = AS_Operand_Temp(Temp_newtemp_int_ptr(memberinfo.def.len));
    } else if (memberinfo.def.kind == TempType::STRUCT_PTR) {
      op = AS_Operand_Temp(Temp_newtemp_struct_ptr(memberinfo.def.len,
                                                   memberinfo.def.structname));
      newop = AS_Operand_Temp(Temp_newtemp_struct_ptr(
          memberinfo.def.len, memberinfo.def.structname));
    }
    auto stm = L_Gep(op, lval, AS_Operand_Const(memberinfo.offset));
    emit_irs.push_back(stm);
    auto load = L_Load(newop, op);
    emit_irs.push_back(load);
    return newop;
  }
  case A_arithUExprKind: {
    return ast2llvmArithUExpr(e->u.arithUExpr);
  }
  }
}

LLVMIR::L_func *ast2llvmFuncBlock(Func_local *f) {
  auto args = f->args;
  auto instrs = f->irs;
  auto name = f->name;
  auto ret = f->ret;
  auto blocks = list<L_block *>();
  blocks.push_back(L_Block(instrs));
  auto func = new L_func(name, ret, args, blocks);
  return func;
}

void ast2llvm_moveAlloca(LLVMIR::L_func *f) {}