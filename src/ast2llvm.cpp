#include "ast2llvm.h"
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include "llvm_ir.h"
#include "temp.h"
#include <cassert>
#include <iostream>
#include <list>
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

// void printFuncReturnMap() {
//   // print the funcReturnMap
//   for (const auto &f : funcReturnMap) {
//     std::cout << f.first << " ";
//     switch (f.second.type) {
//     case ReturnType::VOID_TYPE: {
//       std::cout << "void";
//       break;
//     }
//     case ReturnType::INT_TYPE: {
//       std::cout << "int";
//       break;
//     }
//     case ReturnType::STRUCT_TYPE: {
//       std::cout << "struct " << f.second.structname;
//       break;
//     }
//     default:
//       break;
//     }
//     std::cout << endl;
//   }
// }

LLVMIR::L_prog *ast2llvm(aA_program p) {
  auto defs = ast2llvmProg_first(p);
  // printFuncReturnMap();
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
  defs.push_back(
      L_Funcdecl("getint", vector<TempDef>(), FuncType(ReturnType::INT_TYPE)));
  defs.push_back(L_Funcdecl("putch",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  defs.push_back(L_Funcdecl("putint",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  defs.push_back(L_Funcdecl("putarray",
                            vector<TempDef>{TempDef(TempType::INT_TEMP),
                                            TempDef(TempType::INT_PTR, -1)},
                            FuncType(ReturnType::VOID_TYPE)));
  defs.push_back(L_Funcdecl("_sysy_starttime",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
  defs.push_back(L_Funcdecl("_sysy_stoptime",
                            vector<TempDef>{TempDef(TempType::INT_TEMP)},
                            FuncType(ReturnType::VOID_TYPE)));
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
      }
      if (v->u.fnDeclStmt->fnDecl->type->type == A_nativeTypeKind) {
        type.type = ReturnType::INT_TYPE;
      } else if (v->u.fnDeclStmt->fnDecl->type->type == A_structTypeKind) {
        type.type = ReturnType::STRUCT_TYPE;
        type.structname = *v->u.fnDeclStmt->fnDecl->type->u.structType;
      } else {
        assert(0);
      }
      if (funcReturnMap.find(*v->u.fnDeclStmt->fnDecl->id) ==
          funcReturnMap.end())
        funcReturnMap.emplace(*v->u.fnDeclStmt->fnDecl->id, std::move(type));
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
    }
  } else {
    assert(0);
  }
  return res;
}

Func_local *ast2llvmFunc(aA_fnDef f) {
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
  cout << vars.size() << endl;
  for (auto var : vars) {
    cout << var->kind << endl;
    TempType kind;
    int len;
    string structname;
    switch (var->kind) {
    case A_varDeclScalarKind: {
      cout << var->u.declScalar->type->type << endl;
      if (var->u.declScalar->type->type == A_structTypeKind) {
        kind = TempType::STRUCT_TEMP;
        len = 0;
        structname = *var->u.declScalar->type->u.structType;
      } else {
        kind = TempType::INT_TEMP;
        len = 0;
        structname = "";
      }
      break;
    }
    case A_varDeclArrayKind: {
      if (var->u.declArray->type->type == A_structTypeKind) {
        kind = TempType::STRUCT_PTR;
        len = var->u.declArray->len;
        structname = *var->u.declArray->type->u.structType;
      } else {
        kind = TempType::INT_PTR;
        len = var->u.declArray->len;
        structname = "";
      }
      break;
    }
    default:
      assert(0);
    }
    cout << "tmpdef" << endl;
    auto tmpdef = Temp_temp(num++, kind, len, structname);
    args.push_back(&tmpdef);
  }
  list<LLVMIR::L_stm *> instrs;
  instrs.push_back(L_Label(Temp_newlabel()));
  for (auto stmt : f->stmts) {
    switch (stmt->kind) {
    case A_nullStmtKind:
      break;
    case A_varDeclStmtKind: {
      auto v = Gen_varDeclStmtKind(stmt->u.varDeclStmt);
      instrs.insert(instrs.end(), v.begin(), v.end());
      break;
    }
    case A_assignStmtKind:
      break;
    case A_callStmtKind:
      break;
    case A_ifStmtKind:
      break;
    case A_whileStmtKind:
      break;
    case A_returnStmtKind: {
      auto u = stmt->u.returnStmt;
      auto ret = u->retVal;
      auto op = ast2llvmRightVal(ret);
      instrs.insert(instrs.end(), emit_irs.begin(), emit_irs.end());
      emit_irs.clear();
      instrs.push_back(L_Ret(op));
      emit_irs.clear();
      break;
    }
    case A_continueStmtKind:
      break;
    case A_breakStmtKind:
      break;
    default:
      break;
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
    AS_operand *res;
    if (arr->kind == OperandKind::TEMP) {
      auto u = arr->u.TEMP;
      if (u->type == TempType::INT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (u->type == TempType::STRUCT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, u->structname));
      } else {
        assert(0);
      }
    } else if (arr->kind == OperandKind::NAME) {
      auto u = arr->u.NAME;
      if (u->type == TempType::INT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (u->type == TempType::STRUCT_PTR) {
        res = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, u->structname));
      } else {
        assert(0);
      }
    } else
      assert(0);
    auto stm = L_Gep(res, arr, idx);
    return res;
  }
  case A_leftValType::A_memberValKind: {
    auto u = l->u.memberExpr;
    auto structid = ast2llvmLeftVal(u->structId);
    auto structname = structid->u.NAME->structname;
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
  }
  case A_leftValType::A_varValKind: {
    auto u = l->u.id;
    // find var in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      return AS_Operand_Temp(tmp);
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      return AS_Operand_Name(name);
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
      return AS_Operand_Temp(tmp);
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      return AS_Operand_Name(name);
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
  auto left = ast2llvmBoolExpr(b->left, true_label, false_label);
  auto right = ast2llvmBoolExpr(b->right, true_label, false_label);
  auto l1 = Temp_newlabel();
  auto l2 = Temp_newlabel();
  auto l3 = Temp_newlabel();
  L_stm *entry;
  auto jump = L_Jump(l3);
  L_stm *end;
  auto dst = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
  if (b->op == A_and) {
    entry = L_Cjump(left, l2, l3);
    // vector<pair<AS_operand *, Temp_label *>> phis = {
    // };
    // end = L_Phi(dst, phis);
  } else {
    entry = L_Cjump(left, l3, l2);
    // vector<pair<AS_operand *, Temp_label *>> phis = {
    // };
    // end = L_Phi(dst, phis);
  }
  auto stm = L_Cjump(dst, true_label, false_label);
  return dst;
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
  auto stm = L_Cmp(kind, left, right, dst);
  auto jmp = L_Cjump(dst, true_label, false_label);
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
  auto op = AS_Operand_Temp(Temp_newtemp_int_ptr(0)); // only int can be arith
  auto stm = L_Binop(kind, left, right, op);
  emit_irs.push_back(stm);
  return op;
}

AS_operand *ast2llvmArithUExpr(aA_arithUExpr a) {
  if (a->op != A_arithUOp::A_neg) // the only possible unary operator
    assert(0);
  auto expr = ast2llvmExprUnit(a->expr);
  auto left = AS_Operand_Const(0);
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
    // find the id in globalVarMap or localVarMap
    auto local = localVarMap.find(*u);
    if (local != localVarMap.end()) { // found in local
      auto tmp = local->second;
      return AS_Operand_Temp(tmp);
    }
    auto global = globalVarMap.find(*u);
    if (global != globalVarMap.end()) { // found in global
      auto name = global->second;
      return AS_Operand_Name(name);
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
      op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    } else if (fn.type == ReturnType::STRUCT_TYPE) {
      op = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, fn.structname));
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
    auto lval = ast2llvmLeftVal(u->arr);
    auto idx = ast2llvmIndexExpr(u->idx);
    if (lval->kind == OperandKind::TEMP) {
      auto tmp = lval->u.TEMP;
      if (tmp->type == TempType::INT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (tmp->type == TempType::STRUCT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, tmp->structname));
      } else {
        assert(0);
      }
    } else if (lval->kind == OperandKind::NAME) {
      auto name = lval->u.NAME;
      if (name->type == TempType::INT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
      } else if (name->type == TempType::STRUCT_PTR) {
        op = AS_Operand_Temp(Temp_newtemp_struct_ptr(0, name->structname));
      } else {
        assert(0);
      }
    } else
      assert(0);
    auto stm = L_Gep(op, lval, idx);
    emit_irs.push_back(stm);
    return op;
  }
  case A_memberExprKind: {
    auto u = e->u.memberExpr;
    auto lval = ast2llvmLeftVal(u->structId);
    auto structinfo = structInfoMap.find(lval->u.NAME->structname)->second;
    auto memberinfo = structinfo.memberinfos.find(*u->memberId)->second;
    AS_operand *op;
    if (memberinfo.def.kind == TempType::INT_TEMP) {
      op = AS_Operand_Temp(Temp_newtemp_int_ptr(0));
    } else if (memberinfo.def.kind == TempType::STRUCT_TEMP) {
      op = AS_Operand_Temp(
          Temp_newtemp_struct_ptr(0, memberinfo.def.structname));
    } else if (memberinfo.def.kind == TempType::INT_PTR) {
      op = AS_Operand_Temp(Temp_newtemp_int_ptr(memberinfo.def.len));
    } else if (memberinfo.def.kind == TempType::STRUCT_PTR) {
      op = AS_Operand_Temp(Temp_newtemp_struct_ptr(memberinfo.def.len,
                                                   memberinfo.def.structname));
    }
    auto stm = L_Gep(op, lval, AS_Operand_Const(memberinfo.offset));
    emit_irs.push_back(stm);
    return op;
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