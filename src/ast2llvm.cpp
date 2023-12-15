#include "ast2llvm.h"
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include "llvm_ir.h"
#include "temp.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <ostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;
using namespace LLVMIR;

static unordered_map<string, FuncType> funcReturnMap;
static unordered_map<string, StructInfo> structInfoMap;
static unordered_map<string, Name_name *> globalVarMap;
static unordered_map<string, Temp_temp *> localVarMap;
static list<L_stm *> emit_irs;

LLVMIR::L_prog *ast2llvm(aA_program p) {
  auto defs = ast2llvmProg_first(p);
  auto funcs = ast2llvmProg_second(p);
  vector<L_func *> funcs_block;
  cout << "to function block" << endl;
  for (auto f : funcs) {
    funcs_block.push_back(ast2llvmFuncBlock(f));
  }
  cout << "move alloca" << endl;
  for (auto &f : funcs_block) {
    ast2llvm_moveAlloca(f);
  }
  for (auto &f : funcs_block) {
    ast2llvm_renameEmptyLabel(f);
    ast2llvm_removeAfterReturn(f);
    //不动点算法，当counter的大小不再发生变化时，停止循环
    auto prevCounter = ast2llvm_removeUnusedBlock(f);
    while (true) {
      auto counter = ast2llvm_removeUnusedBlock(f);
      if (prevCounter.size() == counter.size()) {
        break;
      }
      prevCounter = counter;
    }
  }
  return new L_prog(defs, funcs_block);
}

int ast2llvmRightVal_first(aA_rightVal r) {
  if (r == nullptr) {
    return 0;
  }
  switch (r->kind) {
  case A_arithExprValKind: {
    return ast2llvmArithExpr_first(r->u.arithExpr);
    break;
  }
  case A_boolExprValKind: {
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
  for (const auto &v : p->programElements) {
    switch (v->kind) {
    case A_programNullStmtKind: {
      break;
    }
    case A_programVarDeclStmtKind: {
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
      localVarMap.clear();
      vec.push_back(ast2llvmFunc(v->u.fnDef));
      break;
    }
    default: {
      break;
    }
    }
  }
  return vec;
}

vector<L_stm *> Gen_varDeclStmtKind(aA_varDeclStmt stmt) {
  vector<L_stm *> res;
  if (stmt->kind == A_varDeclStmtType::A_varDeclKind) {
    aA_varDecl varDecl = stmt->u.varDecl;
    if (varDecl->kind == A_varDeclType::A_varDeclScalarKind) {
      aA_varDeclScalar declScalar = varDecl->u.declScalar;
      if (declScalar->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(0);
        localVarMap.emplace(*declScalar->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      } else if (declScalar->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(0, *declScalar->type->u.structType);
        localVarMap.emplace(*declScalar->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      }
    } else if (varDecl->kind == A_varDeclType::A_varDeclArrayKind) {
      aA_varDeclArray declArray = varDecl->u.declArray;
      if (declArray->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(declArray->len);
        localVarMap.emplace(*declArray->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      } else if (declArray->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(declArray->len,
                                           *declArray->type->u.structType);
        localVarMap.emplace(*declArray->id, tmp);
        res.push_back(L_Alloca(AS_Operand_Temp(tmp)));
      }
    }
  } else if (stmt->kind == A_varDeclStmtType::A_varDefKind) {
    aA_varDef varDef = stmt->u.varDef;
    if (varDef->kind == A_varDefType::A_varDefScalarKind) {
      aA_varDefScalar defScalar = varDef->u.defScalar;
      if (defScalar->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(0);
        auto opt = AS_Operand_Temp(tmp);
        localVarMap.emplace(*defScalar->id, tmp);
        res.push_back(L_Alloca(opt));
        auto op = ast2llvmRightVal(defScalar->val);
        res.push_back(L_Store(op, opt));
      } else if (defScalar->type->type == A_dataType::A_structTypeKind) {
        auto tmp = Temp_newtemp_struct_ptr(0, *defScalar->type->u.structType);
        auto opt = AS_Operand_Temp(tmp);
        localVarMap.emplace(*defScalar->id, tmp);
        res.push_back(L_Alloca(opt));
        auto op = ast2llvmRightVal(defScalar->val);
        res.push_back(L_Store(op, opt));
      }
    } else if (varDef->kind == A_varDefType::A_varDefArrayKind) {
      aA_varDefArray defArray = varDef->u.defArray;
      if (defArray->type->type == A_dataType::A_nativeTypeKind) {
        auto tmp = Temp_newtemp_int_ptr(defArray->len);
        auto opt = AS_Operand_Temp(tmp);
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
  if (left->kind == OperandKind::TEMP &&
      left->u.TEMP->type == TempType::INT_TEMP) {
    AS_operand *temp = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    res.push_back(L_Store(right, temp));
    res.push_back(L_Load(left, temp));
  } else {
    res.push_back(L_Store(right, left));
  }

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
  Temp_label *compareLabel_1 = Temp_newlabel();
  instrs.emplace_back(L_Jump(compareLabel_1));
  instrs.emplace_back(L_Label(compareLabel_1));
  ast2llvmBoolExpr(whileStmt->boolExpr, whileLabel, breakLabel);
  instrs.insert(instrs.end(), emit_irs.begin(),
                emit_irs.end()); // ast2llvmBoolExpr内部处理的命令
  emit_irs.clear();

  Temp_label *compareLabel_2 = Temp_newlabel();

  list<LLVMIR::L_stm *> while_instrs =
      Gen_Block(whileLabel, compareLabel_2, breakLabel, &whileStmt->whileStmts);
  instrs.insert(instrs.end(), while_instrs.begin(), while_instrs.end());
  instrs.emplace_back(L_Jump(compareLabel_2));

  instrs.emplace_back(L_Label(compareLabel_2));
  ast2llvmBoolExpr(whileStmt->boolExpr, whileLabel, breakLabel);
  instrs.insert(instrs.end(), emit_irs.begin(),
                emit_irs.end()); // ast2llvmBoolExpr内部处理的命令
  emit_irs.clear();
  instrs.emplace_back(L_Label(breakLabel));
  return instrs;
}

// 将代码块的处理独立出来
list<LLVMIR::L_stm *> Gen_Block(Temp_label *blockLabel,
                                Temp_label *continueLabel,
                                Temp_label *breakLabel,
                                vector<aA_codeBlockStmt> *stmts,
                                bool recursive) {
  list<LLVMIR::L_stm *> instrs;
  if (stmts == nullptr) {
    return instrs;
  }
  instrs.push_back(L_Label(blockLabel));
  for (auto stmt : *stmts) {
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
      break;
    }
    case A_whileStmtKind: {
      auto v = Gen_whileStmtKind(stmt->u.whileStmt);
      instrs.insert(instrs.end(), v.begin(), v.end());
      break;
    }
    case A_returnStmtKind: {
      auto u = stmt->u.returnStmt;
      auto ret = u->retVal;
      auto op = ast2llvmRightVal(ret);
      instrs.insert(instrs.end(), emit_irs.begin(), emit_irs.end());
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
  }
  return instrs;
}

Func_local *ast2llvmFunc(aA_fnDef f) {
  // 首先获取函数的参数，转成temp_temp
  auto vars = f->fnDecl->paramDecl->varDecls;
  vector<Temp_temp *> args;
  auto funLabel = Temp_newlabel();
  list<LLVMIR::L_stm *> instrs;
  bool hasNativeArg = false;
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
  for (auto var : vars) {
    TempType kind;
    int len;
    string structname;
    Temp_temp *tmp;
    switch (var->kind) {
    case A_varDeclScalarKind: {
      if (var->u.declScalar->type->type == A_structTypeKind) {
        kind = TempType::STRUCT_TEMP;
        len = 0;
        structname = *var->u.declScalar->type->u.structType;
        tmp = Temp_newtemp_struct_ptr(0, structname);
        // register into local var map
        localVarMap.emplace(*var->u.declScalar->id, tmp);
      } else {
        kind = TempType::INT_TEMP;
        tmp = Temp_newtemp_int();
        if (hasNativeArg == false) {
          instrs.emplace_back(L_Label(Temp_newlabel()));
          hasNativeArg = true;
        }
        Temp_temp *temp_ptr = Temp_newtemp_int_ptr(0);
        instrs.emplace_back(L_Alloca(AS_Operand_Temp(temp_ptr)));
        instrs.emplace_back(
            L_Store(AS_Operand_Temp(tmp), AS_Operand_Temp(temp_ptr)));
        // register into local var map
        localVarMap.emplace(*var->u.declScalar->id, temp_ptr);
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
  if (hasNativeArg) {
    instrs.emplace_back(L_Jump(funLabel));
  }
  // 生成代码块。
  auto block_instrs = Gen_Block(funLabel, nullptr, nullptr, &f->stmts, false);
  instrs.insert(instrs.end(), block_instrs.begin(), block_instrs.end());
  // 如果函数的最后一个block不是return,需要加上一句示例return,以避免出现空label的情况
  auto isReturn = f->stmts.back()->kind == A_returnStmtKind;
  if (!isReturn) {
    // 根据函数返回值类型加return
    if (ret.type == ReturnType::INT_TYPE) {
      instrs.push_back(L_Ret(AS_Operand_Const(0)));
    } else if (ret.type == ReturnType::STRUCT_TYPE) {
      instrs.push_back(L_Ret(AS_Operand_Const(0)));
    } else if (ret.type == ReturnType::VOID_TYPE) {
      instrs.push_back(L_Ret(nullptr));
    } else {
      assert(0);
    }
  }
  auto func = new Func_local(*f->fnDecl->id, ret, args, instrs);
  return func;
}

void ast2llvmBlock(aA_codeBlockStmt b, Temp_label *con_label,
                   Temp_label *bre_label) {}

AS_operand *ast2llvmRightVal(aA_rightVal r) {
  if (r == nullptr) {
    return nullptr;
  }
  switch (r->kind) {
  case A_arithExprValKind: {
    return ast2llvmArithExpr(r->u.arithExpr);
    break;
  }
  case A_boolExprValKind: {
    return ast2llvmBoolExpr(r->u.boolExpr, nullptr, nullptr);
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
    auto u = l->u.memberExpr;
    auto structid = ast2llvmLeftVal(u->structId);
    auto structname = structid->kind == OperandKind::NAME
                          ? structid->u.NAME->structname
                          : structid->u.TEMP->structname;
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
    auto u = l->u.id;
    // find var in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      AS_operand *ptrOp = AS_Operand_Temp(tmp);
      if (tmp->type == TempType::INT_TEMP) {
        Temp_temp *left_ptr_temp = Temp_newtemp_int_ptr(0);
        AS_operand *left_ptr = AS_Operand_Temp(left_ptr_temp);
        emit_irs.emplace_back(L_Alloca(left_ptr));
        emit_irs.emplace_back(L_Store(ptrOp, left_ptr));
        localVarMap[*u] = left_ptr_temp;
        return left_ptr;
      }
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
  if (true_label != nullptr && false_label != nullptr) {
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
  } else {
    true_label = Temp_newlabel();
    false_label = Temp_newlabel();
    Temp_label *continueLabel = Temp_newlabel();
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
    emit_irs.emplace_back(L_Label(true_label));
    emit_irs.emplace_back(L_Jump(continueLabel));
    emit_irs.emplace_back(L_Label(false_label));
    emit_irs.emplace_back(L_Jump(continueLabel));
    emit_irs.emplace_back(L_Label(continueLabel));
    std::vector<std::pair<AS_operand *, Temp_label *>> vec;
    std::pair<AS_operand *, Temp_label *> p1{AS_Operand_Const(1), true_label};
    std::pair<AS_operand *, Temp_label *> p2{AS_Operand_Const(0), false_label};
    vec.push_back(p1);
    vec.push_back(p2);
    AS_operand *val = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    emit_irs.emplace_back(L_Phi(val, vec));
    return val;
  }
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
    true_label = Temp_newlabel();
    false_label = Temp_newlabel();
    Temp_label *continueLabel = Temp_newlabel();
    auto jmp = L_Cjump(dst, true_label, false_label);
    emit_irs.push_back(jmp);
    emit_irs.emplace_back(L_Label(true_label));
    emit_irs.emplace_back(L_Jump(continueLabel));
    emit_irs.emplace_back(L_Label(false_label));
    emit_irs.emplace_back(L_Jump(continueLabel));
    emit_irs.emplace_back(L_Label(continueLabel));
    std::vector<std::pair<AS_operand *, Temp_label *>> vec;
    std::pair<AS_operand *, Temp_label *> p1{AS_Operand_Const(1), true_label};
    std::pair<AS_operand *, Temp_label *> p2{AS_Operand_Const(0), false_label};
    vec.push_back(p1);
    vec.push_back(p2);
    AS_operand *val = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    emit_irs.emplace_back(L_Phi(val, vec));
    return val;
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
  auto op = AS_Operand_Temp(Temp_newtemp_int());
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
    // find the id in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      AS_operand *ptrOp = AS_Operand_Temp(tmp);
      AS_operand *dstOp;
      if (tmp->type == TempType::INT_PTR) {
        if (tmp->len != 0) {
          return ptrOp;
        }
        dstOp = AS_Operand_Temp(Temp_newtemp_int());
        emit_irs.emplace_back(L_Load(dstOp, ptrOp));
        return dstOp;
      } else if (tmp->type == TempType::STRUCT_PTR) {
        return ptrOp;
      } else if (tmp->type == TempType::INT_TEMP) {
        Temp_temp *temp_ptr = Temp_newtemp_int_ptr(0);
        AS_operand *tempOp = AS_Operand_Temp(temp_ptr);
        emit_irs.emplace_back(L_Alloca(tempOp));
        emit_irs.emplace_back(L_Store(ptrOp, tempOp));
        localVarMap[*u] = temp_ptr;
        return ptrOp;
      } else if (tmp->type == TempType::STRUCT_TEMP) {
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
    auto u = e->u.memberExpr;
    auto lval = ast2llvmLeftVal(u->structId);
    auto name = lval->kind == OperandKind::NAME ? lval->u.NAME->structname
                                                : lval->u.TEMP->structname;
    auto structinfo = structInfoMap.find(name)->second;
    auto memberinfo = structinfo.memberinfos.find(*u->memberId)->second;
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
  // 获取到每一个基本块的指令集；基本块以label开头，以跳转语句或者return结束
  list<list<L_stm *>> block_instrs;
  for (auto instr : instrs) {
    if (instr->type ==
        L_StmKind::T_LABEL) { // 为label时，向集合末尾添加一个新的空集合
      block_instrs.push_back(list<L_stm *>());
    }
    block_instrs.back().push_back(instr); // 插入时，只需考虑最后一个集合
  }
  for (auto block_instr : block_instrs) {
    blocks.push_back(L_Block(block_instr));
  }
  auto func = new L_func(name, ret, args, blocks);
  return func;
}

void ast2llvm_moveAlloca(LLVMIR::L_func *f) {
  auto firstBlock = f->blocks.front();
  for (auto i = f->blocks.begin(); i != f->blocks.end(); i++) {
    // 确保每个block都以label开头
    assert((*(*i)->instrs.begin())->type == LLVMIR::L_StmKind::T_LABEL);
    cout << "label: " << (*i)->label->name << endl;
    cout << "instrs: " << (*i)->instrs.size() << endl;
    auto instrs = (*i)->instrs;
    auto allocaInstrs = list<L_stm *>(); // 用于存储当前block的alloca指令
    // 倒着遍历指令，找到alloca指令，将其移动到第一个block的最前面
    for (auto it = instrs.rbegin(); it != instrs.rend();) {
      auto instr = *it;
      if (instr->type == L_StmKind::T_ALLOCA) {
        // 存储到allocaInstrs中
        allocaInstrs.push_front(instr);
        // 删除当前block的alloca指令，由于list实现是一个链表，直接使用reverse_iterator跳过当前元素
        it = reverse_iterator(instrs.erase(std::next(it).base()));
      } else {
        ++it;
      }
    }
    // 更新当前block的指令集（删除alloca之后）
    (*i)->instrs = instrs;
    // 更新firstBlock的指令集（添加alloca）
    firstBlock->instrs.insert(++firstBlock->instrs.begin(),
                              allocaInstrs.begin(), allocaInstrs.end());
  }
}

L_block *FindLabel(L_func *f, Temp_label *label) {
  for (auto blk : f->blocks) {
    if (blk->label == label) {
      return blk;
    }
  }
  return nullptr;
}

L_block *FindPred(L_func *f, Temp_label *label) {
  for (auto blk : f->blocks) {
    if (blk->succs.find(label) != blk->succs.end()) {
      return blk;
    }
  }
  return nullptr;
}

// 自上而下遍历所有只含一个jmp的block,将其删除，并更新对应pred block的succs
// 不删除block本身，而只是重定向其jmp的目标
void ast2llvm_renameEmptyLabel(LLVMIR::L_func *f) {
  auto renameJumpLabel = [](L_block *blk, Temp_label *old_label,
                            Temp_label *new_label) {
    for (auto i = blk->instrs.begin(); i != blk->instrs.end(); i++) {
      auto instr = *i;
      if (instr->type == L_StmKind::T_JUMP &&
          instr->u.JUMP->jump == old_label) {
        instr->u.JUMP->jump = new_label;
        blk->succs.erase(old_label);
        blk->succs.insert(new_label);
      } else if (instr->type == L_StmKind::T_CJUMP) {
        auto u = instr->u.CJUMP;
        if (u->true_label == old_label) {
          u->true_label = new_label;
        }
        if (u->false_label == old_label) {
          u->false_label = new_label;
        }
        blk->succs.erase(old_label);
        blk->succs.insert(new_label);
      }
    }
  };
  auto isSingleJumpBlock = [](L_block *blk) {
    if (blk->instrs.size() == 2) {
      auto firstInstr = *(++blk->instrs.begin());
      if (firstInstr->type == L_StmKind::T_JUMP) {
        return true;
      }
    }
    return false;
  };
  vector<L_block *> emptyBlocks;
  for (auto blk = f->blocks.begin(); blk != f->blocks.end(); blk++) {
    if (isSingleJumpBlock(*blk)) {
      auto oldLabel = (*blk)->label;
      auto newLabel = (*blk)->instrs.back()->u.JUMP->jump;
      // 在blk前，找到blk的所有引用
      for (auto i = f->blocks.begin(); i != blk; i++) {
        renameJumpLabel(*i, oldLabel, newLabel);
      }
    }
  }
  // 不需要主动remove,rename之后，相关的跳转块会因0引用而被后面的removeUnusedBlock删除
  // for (auto emptyBlock : emptyBlocks) {
  //   f->blocks.remove(emptyBlock);
  // }
}

// 删除所有block中return之后的指令，如果后续指令有跳转，
// 删除对应的succs
// 不删除之后跳转的block本身
void ast2llvm_removeAfterReturn(LLVMIR::L_func *f) {
  for (auto blk : f->blocks) {
    auto instrs = blk->instrs;
    vector<L_stm *> instrsAfterReturn = vector<L_stm *>();
    bool afterReturn = false;
    for (auto instr : instrs) {
      if (afterReturn)
        instrsAfterReturn.push_back(instr);
      if (instr->type == L_StmKind::T_RETURN)
        afterReturn = true;
    }
    for (auto instr : instrsAfterReturn) {
      blk->instrs.remove(instr);
      // 别忘记同时删除instr对应的succs
      if (instr->type == L_StmKind::T_JUMP) {
        blk->succs.erase(instr->u.JUMP->jump);
      } else if (instr->type == L_StmKind::T_CJUMP) {
        blk->succs.erase(instr->u.CJUMP->true_label);
        blk->succs.erase(instr->u.CJUMP->false_label);
      }
    }
  }
}

// 使用不动点算法：refCounter大小不再改变时，算法结束
// 原理：该算法如果有删除block,会导致下一次运行该算法refCounter大小发生变化
// 反复删除没有被引用的block，直到refCounter大小不再改变，因为
// 如果没有被引用的block单独又引用了其他block，那么refCounter大小会发生变化
// 不需要更新对应的succs，前面已经针对succs进行了更新
std::unordered_map<Temp_label *, int> ast2llvm_removeUnusedBlock(LLVMIR::L_func *f) {
  // 维护一个引用计数器，记录每个block的引用次数
  auto refCounter = std::unordered_map<Temp_label *, int>();
  for (auto blk : f->blocks) {
    if (blk == f->blocks.front()) {
      refCounter.emplace(blk->label, 1);
      continue;
    }
    refCounter.emplace(blk->label, 0);
  }
  for (auto blk : f->blocks) {
    auto instrs = blk->instrs;
    for (auto instr : instrs) {
      // 如果命令是jump或者cjump,则将其跳转的label的引用计数加1
      if (instr->type == L_StmKind::T_JUMP) {
        auto target = instr->u.JUMP->jump;
        refCounter[target]++;
      } else if (instr->type == L_StmKind::T_CJUMP) {
        auto true_label = instr->u.CJUMP->true_label;
        auto false_label = instr->u.CJUMP->false_label;
        refCounter[true_label]++;
        refCounter[false_label]++;
      }
    }
  }
  // 一旦发现引用计数器中有为0的label，则需要递归删除该label对应的block
  for (auto it = refCounter.begin(); it != refCounter.end(); ++it) {
    auto label = it->first;
    auto count = it->second;
    if (count == 0) {
      auto unusedBlock = FindLabel(f, label);
      cout << "Found unused block: " << unusedBlock->label->name << endl;
      if (unusedBlock == nullptr) {
        cout << "No block for label: " << label->name << endl;
        continue;
      }
      f->blocks.remove(unusedBlock);
    }
  }
  return refCounter;
}