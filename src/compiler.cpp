#include <fstream>
#include <iostream>
#include "TeaplAst.h"
#include "TeaplaAst.h"
#include "PrintTeaplaAst.h"
// #include "TypeCheck.h"
#include "y.tab.hpp"
#include "llvm_ir.h"
#include "ast2llvm.h"
#include "printLLVM.h"

#define YACCDEBUG 1

using namespace std;
using namespace LLVMIR;

extern int yyparse();
extern YYSTYPE yylval;
extern int yydebug;

int line, col;

A_program root;
aA_program aroot;

int main(int argc, char * argv[]) {

    #if YACCDEBUG
        yydebug = 1;
    #endif

    line = 1;
    col = 1;

    string input_name = argv[1];
    auto dot_pos = input_name.find('.');
    if(dot_pos == input_name.npos)
    {
        cout << "input error";
        return -1;
    }
    string file_name(input_name.substr(0,dot_pos));
    
    freopen(argv[1], "r", stdin);  
    ofstream ASTStream;
    std::cout <<  "print AST file" << endl;
    ASTStream.open(file_name+".ast");
    yyparse();
    aroot = aA_Program(root);
    print_aA_Program(aroot, ASTStream);
    ASTStream.close();

    // check_Prog(&std::cout, aroot);
    std::cout << "print LL file" << endl;
    ofstream LLVMStream;
    LLVMStream.open(file_name + ".ll");
    auto prog = ast2llvm(aroot);
    std::cout << "prog" << endl;
    printL_prog(LLVMStream,prog);
    LLVMStream.close();
    return 0;
}

