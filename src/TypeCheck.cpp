#include "TypeCheck.h"

// maps to store the type information. Feel free to design new data structures if you need.
typeMap g_token2Type;               // global token ids to type
arrayDeclMap g_token2ArrayDeclType; // 用于存放全局数组信息
arrayDefMap g_token2ArrayDefType;


vector<intMap *> local_intVec;//用于保存局部的数值变量值 
vector<typeMap *> local_tokenVec;// 用于保存局部变量***       
vector<arrayDeclMap *> localArrDeclVec;// 用于存放局部数组变量声明信息
vector<arrayDefMap *> localArrDefVec;//用于存放局部数组变量定义信息

fnStateMap fnState;//用来保存函数处于被声明还是被定义状态
typeMap funcparam_token2Type;           // func params token ids to type，用于临时保存函数的参数，用来检查一个函数参数是否重复
typeMap func_token2Type;    //用来保存函数的返回类型
posMap fun2Pos;//用来保存函数声明位置
paramMemberMap func2Param; //用于保存所有函数名和其参数信息

typeMap structMembers2Type;//用于临时保存结构体内变量，用于确定是否变量重复
paramMemberMap struct2Members;//用于保存所有结构体和内部信息

// private util functions. You can use these functions to help you debug.
void error_print(std::ostream *out, A_pos p, string info)
{
    *out << "Typecheck error in line " << p->line << ", col " << p->col << ": " << info << std::endl;
    exit(0);
}

void print_token_map(typeMap *map)
{
    for (auto it = map->begin(); it != map->end(); it++)
    {
        std::cout << it->first << " : ";
        switch (it->second->type)
        {
        case A_dataType::A_nativeTypeKind:
            switch (it->second->u.nativeType)
            {
            case A_nativeType::A_intTypeKind:
                std::cout << "int";
                break;
            default:
                break;
            }
            break;
        case A_dataType::A_structTypeKind:
            std::cout << *(it->second->u.structType);
            break;
        default:
            break;
        }
        std::cout << std::endl;
    }
}

// public functions
// This is the entrace of this file.
void check_Prog(std::ostream *out, aA_program p)
{
    std::vector<aA_varDeclStmt> varDeclStmtVector;
    std::vector<aA_structDef> structDefVector;
    // p is the root of AST tree.
    for (auto ele : p->programElements)
    {
        /*
            Write your code here.

            Hint:
            1. Design the order of checking the program elements to meet the requirements that funtion declaration and global variable declaration can be used anywhere in the program.

            2. Many types of statements indeed collapse to some same units, so a good abstract design will help you reduce the amount of your code.
        */
        // 先检查结构体，再检查变量，再检查函数声明和定义，函数声明和定义有顺序要求
        switch (ele->kind)
        {

        case A_programElementType::A_programVarDeclStmtKind:
            varDeclStmtVector.push_back(ele->u.varDeclStmt);
            /* code */
            break;
        case A_programElementType::A_programStructDefKind:
            structDefVector.push_back(ele->u.structDef);
            /* code */
            break;
        default:
            break;
        }
    }
    
    for (aA_structDef structDef : structDefVector)
    {
        check_StructDef(out, structDef);
    }
    for (aA_varDeclStmt varDeclStmt : varDeclStmtVector)
    {
        check_VarDecl(out, varDeclStmt, true);
    }
    
    
    for (auto ele : p->programElements)
    {
        switch (ele->kind)
        {
        case A_programElementType::A_programFnDeclStmtKind :
            check_FnDeclStmt(out, ele->u.fnDeclStmt);
            break;
        case A_programElementType::A_programFnDefKind :
            check_FnDef(out, ele->u.fnDef);
            break;
        default:
            break;
        }
    }
    for (auto ele : p->programElements)
    {
    }

    (*out) << "Typecheck passed!" << std::endl;
    return;
}
//TODO：变量作用域声明周期还没做
/* 比如下面的示例应该合法,但如何处理这种情况还没做,考虑使用栈+map的方式
    fn main(){
        {let a:int = 0;}
        let a:int = 0;
    } */
// 这里添加了参数global，方便确定对哪一个map进行操作
void check_VarDecl(std::ostream *out, aA_varDeclStmt vd, bool global)
{
    // variable declaration statement
    if (!vd)
        return;
    string name;
    string error_info;
    A_pos pos;
    // 确定变量是数组类型还是，scalar类型
    if (vd->u.varDecl->kind == A_varDeclType::A_varDeclScalarKind)
    {
        name = *(vd->u.varDecl->u.declScalar->id);
        pos = vd->u.varDecl->u.declScalar->pos;
    }
    else if (vd->u.varDecl->kind == A_varDeclType::A_varDeclArrayKind)
    {
        name = *(vd->u.varDecl->u.declArray->id);
        pos = vd->u.varDecl->u.declArray->pos;
    }

    // 如果是全局变量，要加入到全局变量map中
    if (global)
    {
        // 先检查全局变量是否有，如果重复定义，报错
        // 检查全局变量map
        if (g_token2Type.count(name) != 0)
        {
            error_print(out, pos, "duplicate definition of the global variable");
        }
        // 检查全局数组变量map
        if (g_token2ArrayDeclType.count(name) != 0 || g_token2ArrayDefType.count(name) != 0)
        {
            error_print(out, pos, "duplicate definition of the global variable");
        }
        // 对于“声明”和“声明及定义”要单独判断，因为存储时vd->u中内容不一样
        // 判断声明
        if (vd->kind == A_varDeclStmtType::A_varDeclKind)
        {
            // 对于变量和数组要用不同的map存储
            if (vd->u.varDecl->kind == A_varDeclType::A_varDeclScalarKind)
            {
                g_token2Type[name] = vd->u.varDecl->u.declScalar->type;
            }
            else if (vd->u.varDecl->kind == A_varDeclType::A_varDeclArrayKind)
            {
                g_token2ArrayDeclType[name] = vd->u.varDecl->u.declArray;
            }
        }
        else if (vd->kind == A_varDeclStmtType::A_varDefKind)
        { // 判断声明以及定义
            // 对于变量和数组要用不同的map存储
            if (vd->u.varDef->kind == A_varDefType::A_varDefScalarKind)
            {
                g_token2Type[name] = vd->u.varDef->u.defScalar->type;
            }
            else if (vd->u.varDef->kind == A_varDefType::A_varDefArrayKind)
            {
                g_token2ArrayDefType[name] = vd->u.varDef->u.defArray;
            }
        }
        return;
    }

    // 进行局部变量的检查
    // 对于非全局变量，要检查是否与全局变量，和函数参数冲突，并且超出作用域用完后要将map清空
    //是否和全局变量冲突
    if (g_token2Type.count(name) != 0){
        error_print(out, pos, "duplicate definition of the global variable");
    }
    //是否和局部变量冲突
    if(localExist(name)){
        error_print(out, pos, "duplicate definition of the local variable");
    }
    //局部变量和函数参数是否冲突
    if(funcparam_token2Type.count(name)!=0){
        error_info = "local variables dplicates with function params";
        error_print(out, pos, error_info);
    }
    // 检查数组(这里未考虑对函数参数中含有数组，且局部变量数组和参数数组冲突的情况)
    //检查是否与全局数组冲突
    if (g_token2ArrayDeclType.count(name) != 0 
        || g_token2ArrayDefType.count(name) != 0 ){
        error_print(out, pos, "duplicate definition of the global array variable");
    }

    //TODO:检查是否与参数数组冲突

    //检查是否与局部数组冲突
    if(localArrDeclExist(name)||localArrDefExist(name)){
        error_info = "duplicate definition of the local array variable";
        error_print(out, pos, error_info);
    }

    // if declaration only
    // Example:
    //   let a:int;
    //   let a[5]:int;
    /* write your code here*/

    // if both declaration and initialization
    // Example:
    //   let a:int = 5;

    /* write your code here */
    // 对于“声明”和“声明及定义”要单独判断，因为存储时vd->u中内容不一样
    // 判断声明
    if (vd->kind == A_varDeclStmtType::A_varDeclKind)
    {
        // 对于变量和数组要用不同的map存储
        if (vd->u.varDecl->kind == A_varDeclType::A_varDeclScalarKind)
        {
            addLocal2Type(name,vd->u.varDecl->u.declScalar->type);
        }
        else if (vd->u.varDecl->kind == A_varDeclType::A_varDeclArrayKind)
        {
            addLocalArrDecl(name,vd->u.varDecl->u.declArray);
        }
    }
    else if (vd->kind == A_varDeclStmtType::A_varDefKind)
    { // 判断声明以及定义
        // 对于变量和数组要用不同的map存储
        if (vd->u.varDef->kind == A_varDefType::A_varDefScalarKind)
        {
            addLocal2Type(name,vd->u.varDef->u.defScalar->type);
        }
        else if (vd->u.varDef->kind == A_varDefType::A_varDefArrayKind)
        {
            addLocalArrDef(name,vd->u.varDef->u.defArray);
        }
    }

    return;
}

void check_StructDef(std::ostream *out, aA_structDef sd)
{
    if (!sd)
        return;
    // structure definition
    // Example:
    //      struct A{
    //          a:int;
    //          b:int;
    //      }

    /* write your code here */

    // 1.先判断是否有重复结构体定义
    string name = *(sd->id);
    string error_info;
    // 如果有重复结构体报错
    if (struct2Members.count(name) != 0){   
        error_info = "duplicate definition of the structure";
        error_print(out, sd->pos, error_info);
    }
    // 2.检查结构体内变量是否重复定义，以及变量类型是否存在
    string varName;
    for(aA_varDecl varDecl : sd->varDecls){
        varName = aA_varDecl2Name(varDecl);
        if(structMembers2Type.count(varName)!=0){
            error_info = "duplicate definition of the variable in struct "+ name;
            error_print(out, sd->pos, error_info);
        }
        aA_type type = aA_varDecl2Type(varDecl);
        if(!typeCheck(type)){
            string structName = *(type->u.structType);
            error_info = "undefine type" + structName + " in struct "+ name;
            error_print(out, type->pos, error_info);
        }
        structMembers2Type[varName] = type;
    }
    //清理struct内容临时存储map
    structMembers2Type.clear();
    // 3.没有重复的放入struct2Members这个map中
    struct2Members[name] = &(sd->varDecls);
    return;
}

void check_FnDecl(std::ostream *out, aA_fnDecl fd)
{
    // Example:
    //      fn main(a:int, b:int)->int
    if (!fd)
        return;

    /*
        write your code here
        Hint: you may need to check if the function is already declared
    */
    string name = *(fd->id);//获取函数名
    string error_info;//用来保存报错信息

    //0.要保证只出现一次声明或者一次声明加定义，在外部进行判断

    //1.对map中重名的函数，必然是map中存在的是声明，当前输入是定义，检查声明和定义间是否存在差异，要是有差异，报错
    if(func2Param.count(name)!=0){
        //1.1获得第一次声明的位置
        A_pos funPos = fun2Pos[name];
        aA_type firstType = func_token2Type[name];//第一次声明函数时的类型
        aA_type nowFnType = fd->type;//当前声明函数类型
        //1.2比较返回类型是否相同,直接比较有问题,因为aA_type_中含有string*指针变量
        if(!com_aA_type(firstType,nowFnType)){
            error_info = "function definition type on line "+ std::to_string(fd->pos->line) + " doesn't match the declaration on line "+std::to_string(funPos->line);
            error_print(out,fd->pos,error_info);
        }
        //1.3比较参数是否相同，要把每个参数的类型都进行比较
        vector<aA_varDecl> vec1 = *(func2Param[name]);
        vector<aA_varDecl> vec2 = fd->paramDecl->varDecls;
        if(!com_paramList(vec1,vec2)){
            error_info = "function definition parameter on line "+ std::to_string(fd->pos->line) + " doesn't match the declaration on line "+std::to_string(funPos->line);
            error_print(out,fd->pos,error_info);
        }
    }
    //检查函数参数是否有问题，如参数值是否合法，参数是否重复，返回类型是否存在
    //2.先检查返回类型
    if(!typeCheck(fd->type)){
        //类型不存在，必然是结构体不存在
        string structName=*(fd->type->u.structType);
        error_info = "function " + name + " return type " + structName +" undefined";
        error_print(out,fd->pos,error_info); 
    }
    
    //3.检查每个参数类型是否都存在，以及参数名是否重复
    for(aA_varDecl varDecl:fd->paramDecl->varDecls){
        string param_name;
        aA_type param_type;
        //参数可能是数组也可能是单个变量
        if(varDecl->kind==A_varDeclType::A_varDeclScalarKind){
            param_name = *(varDecl->u.declScalar->id);
            param_type = varDecl->u.declScalar->type;
        }else if(varDecl->kind==A_varDeclType::A_varDeclArrayKind){
            param_name = *(varDecl->u.declArray->id);
            param_type = varDecl->u.declArray->type;
        }
        if(funcparam_token2Type.count(param_name)!=0){
            error_info = "function " + name + " parameter name duplicate definition";
            error_print(out,fd->pos,error_info); 
        }
        if(!typeCheck(param_type)){
            //类型不存在，必然是结构体不存在
            string structName=*(param_type->u.structType);
            error_info = "function " + name + " parameter type " + structName +" undefined";
            error_print(out,fd->pos,error_info); 
        }
        //函数一个参数无误，就把一个参数保存，后面的参数需要和保存的参数进行比较
        funcparam_token2Type[param_name]=param_type;
    }
    funcparam_token2Type.clear();//清空这个函数参数在map临时保存的信息
    //4.通过检查，将函数信息保存到map中
    func2Param[name] = &(fd->paramDecl->varDecls);//保存参数信息
    func_token2Type[name] = fd->type;//保存类型信息
    fun2Pos[name] = fd->pos;//保存位置信息
    return;
}

void check_FnDeclStmt(std::ostream *out, aA_fnDeclStmt fd)
{
    // Example:
    //      fn main(a:int, b:int)->int;
    if (!fd)
        return;
    string name = *(fd->fnDecl->id);
    //如果已经声明或定义，则直接报错，无需检查
    if(fnState.count(name)!=0){
        string error_info = "function " + name + " is declared multiple times on "+std::to_string(fun2Pos[name]->line);
        error_print(out,fd->pos,error_info); 
    }
    check_FnDecl(out, fd->fnDecl);
    //如果未声明和定义，声明之后应该修改fn状态为已经声明
    fnState[name] = A_programElementType::A_programFnDeclStmtKind; 
    return;
}

void check_FnDef(std::ostream *out, aA_fnDef fd)
{
    // Example:
    //      fn main(a:int, b:int)->int{
    //          let c:int;
    //          c = a + b;
    //          return c;
    //      }
    if (!fd)
        return;
    string name = *(fd->fnDecl->id);
    //如果已经定义则直接报错，如果只是声明或未声明，进入检查
    if(fnState.count(name)!=0 && fnState[name]==A_programElementType::A_programFnDefKind){
        string error_info = "function " + name + " is defined multiple times";
        error_print(out,fd->pos,error_info);
    }
    
    check_FnDecl(out, fd->fnDecl);
    fnState[name] = A_programElementType::A_programFnDefKind;
    //检查后将fn状态改为已定义
    /*
        write your code here
        Hint: you may pay attention to the function parameters, local variables and global variables.
    */
    // 要把参数放入临时的map里，用于和局部变量比较查重。并且将函数名和参数保存起来，保证函数调用时参数正确
    string varName;
    for(aA_varDecl varDecl : *(func2Param[name])){
        if(varDecl->kind==A_varDeclType::A_varDeclScalarKind){
            varName = *(varDecl->u.declScalar->id);
            funcparam_token2Type[varName] = varDecl->u.declScalar->type;
        }else if(varDecl->kind==A_varDeclType::A_varDeclArrayKind){
            varName = *(varDecl->u.declArray->id);
            funcparam_token2Type[varName] = varDecl->u.declArray->type;
        }
    }

    beforeBlock();
    // 对函数中的每一段代码块进行检查
    for (size_t i = 0; i < fd->stmts.size(); ++i)
    {
        check_CodeblockStmt(out, fd->stmts[i]);
    }
    afterBlock();
    //清理参数临时map
    funcparam_token2Type.clear();

    return;
}

void check_CodeblockStmt(std::ostream *out, aA_codeBlockStmt cs)
{
    if (!cs)
        return;
    switch (cs->kind)
    {
    case A_codeBlockStmtType::A_varDeclStmtKind:
        check_VarDecl(out, cs->u.varDeclStmt,false);
        break;
    case A_codeBlockStmtType::A_assignStmtKind:
        check_AssignStmt(out, cs->u.assignStmt);
        break;
    case A_codeBlockStmtType::A_ifStmtKind:
        check_IfStmt(out, cs->u.ifStmt);
        break;
    case A_codeBlockStmtType::A_whileStmtKind:
        check_WhileStmt(out, cs->u.whileStmt);
        break;
    case A_codeBlockStmtType::A_callStmtKind:
        check_CallStmt(out, cs->u.callStmt);
        break;
    case A_codeBlockStmtType::A_returnStmtKind:
        check_ReturnStmt(out, cs->u.returnStmt);
        break;
    default:
        break;
    }
    return;
}

void check_AssignStmt(std::ostream *out, aA_assignStmt as)
{
    if (!as)
        return;
    string name;
    string error_info;//用来保存报错信息
    //先得到各种情况的左值类型，再与右值类型对比
    aA_type leftType;
    switch (as->leftVal->kind)
    {
    case A_leftValType::A_varValKind:
    {
        /* write your code here */
        //对于左值是变量名类型的，要判断这个id是否能被赋值
        name = *(as->leftVal->u.id);
        //不能给函数赋值
        if(func2Param.count(name)!=0){
            error_info = "cannot assign a value to function " + name;
            error_print(out, as->pos, error_info);
        }
        //不能给函数参数赋值
        if(funcparam_token2Type.count(name)!=0){
            error_info = "cannot assign a value to parameter " + name;
            error_print(out, as->pos, error_info);
        }
        //检查变量是否存在
        //全局变量包含，则返回类型
        if(g_token2Type.count(name)!=0){
            leftType = g_token2Type[name];
            
        }else if(localExist(name)){
            //局部变量包含，则返回类型
            leftType = local2Type(name);
            
        }else{
            //如果变量未定义，报错
            error_info = "var " + name + " is not defined";
            error_print(out, as->pos, error_info);
        }
        
    }
    break;
    //对于数组类型左值
    case A_leftValType::A_arrValKind:
    {
        //检查数组形式是否符合规范,并返回类型
        leftType=check_ArrayExpr(out,as->leftVal->u.arrExpr);
    }
    break;
    case A_leftValType::A_memberValKind:
    {   
        /* write your code here */
        //检查结构体的member是否存在
        leftType = check_MemberExpr(out,as->leftVal->u.memberExpr);
    }
    break;
    }
    aA_type rightType =  rightVal2Type(out,as->rightVal);
    //检查左值和右值类型是否相同
    string leftTypeName=type2Name(leftType);
    string rightTypeName=type2Name(rightType);
    if(leftTypeName!=rightTypeName){
        error_info = rightTypeName + " can not be assigned to "+leftTypeName;
        error_print(out, as->pos, error_info);
    }
    return;
}

aA_type check_ArrayExpr(std::ostream *out, aA_arrayExpr ae)
{
    if (!ae)
        return nullptr;
    /*
        Example:
            a[1] = 0;
        Hint:
            check the validity of the array index
    */
    string name = *(ae->arr);
    int index;
    switch(ae->idx->kind){
        //数组下标为数字时
        case A_indexExprKind::A_numIndexKind :
            index = ae->idx->u.num;
        break;
        //数组下标为变量时，需要将变量转化为真实数字
        case A_indexExprKind::A_idIndexKind :
            //先获得变量类型
            aA_type idIndexType = id2Type(out,ae->pos,*(ae->idx->u.id));
            //当类型是基本类型且是int类型时，可以转化
            if(idIndexType->type==A_dataType::A_nativeTypeKind
                &&idIndexType->u.nativeType==A_nativeType::A_intTypeKind){
                    //TODO:要获得具体数字，变量值的存储还没写
            }else{
                string error_info = "The index of array "+name+" is not of type int";
                error_print(out, ae->pos, error_info);
            }
            
        break;
    }
    //TODO：下标要与数组定义的长度对比


    //获得数组元素的类型
    aA_type arrType;
    //TODO：当数组是右值时，还需要考虑函数参数为数组的情况
    if(g_token2ArrayDeclType.count(name)!=0){
        arrType=g_token2ArrayDeclType[name]->type;
    }else if(g_token2ArrayDefType.count(name)!=0){
        arrType=g_token2ArrayDefType[name]->type;
    }else if(localArrDeclExist(name)||localArrDefExist(name)){
        arrType=localArr2Type(name);
    }
}

aA_type check_MemberExpr(std::ostream *out, aA_memberExpr me)
{
    // check if the member exists and return the type of the member
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way. Feel
    // free to change the design pattern if you need.
    if (!me)
        return nullptr;
    /*
        Example:
            a.b
    */
    string error_info;
    string structID = *(me->structId);
    aA_type type=id2Type(out,me->pos,structID);
    string structName = type2Name(type);
    if(struct2Members.count(structName)==0){
        error_info = structID +" is not a struct";
        error_print(out, me->pos, error_info);
    }
    string memberId = *(me->memberId);
    
    bool contain = false;
    aA_type membertype = NULL;
    for(aA_varDecl varDecl :*(struct2Members[structName])){
        if(aA_varDecl2Name(varDecl)==memberId){
            membertype = aA_varDecl2Type(varDecl);
            contain = true;
            break;
        }
    }
    if(contain == false){
        error_info = "member '" + memberId + "' is not defined";
        error_print(out, me->pos, error_info);
    }
    return membertype;
}

void check_IfStmt(std::ostream *out, aA_ifStmt is)
{
    if (!is)
        return;
    check_BoolExpr(out, is->boolExpr);

    beforeBlock();
    for (aA_codeBlockStmt s : is->ifStmts)
    {
        check_CodeblockStmt(out, s);
    }
    afterBlock();

    beforeBlock();
    for (aA_codeBlockStmt s : is->elseStmts)
    {
        check_CodeblockStmt(out, s);
    }
    afterBlock();

    return;
}

void check_BoolExpr(std::ostream *out, aA_boolExpr be)
{
    if (!be)
        return;
    switch (be->kind)
    {
    case A_boolExprType::A_boolBiOpExprKind:
        /* write your code here */
        break;
    case A_boolExprType::A_boolUnitKind:
        check_BoolUnit(out, be->u.boolUnit);
        break;
    default:
        break;
    }
    return;
}

void check_BoolUnit(std::ostream *out, aA_boolUnit bu)
{
    if (!bu)
        return;
    switch (bu->kind)
    {
    case A_boolUnitType::A_comOpExprKind:
    {
        /* write your code here */
        aA_type leftType = check_ExprUnit(out,bu->u.comExpr->left);
        aA_type rightType = check_ExprUnit(out,bu->u.comExpr->right);
        if(!com_aA_type(leftType,rightType)){
            
            string leftTypeName = type2Name(leftType);
            string rightTypeName = type2Name(rightType);
            string error_info = leftTypeName +" is not comparable with "+ rightTypeName;

            error_print(out, bu->pos, error_info);
        }

    }
    break;
    case A_boolUnitType::A_boolExprKind:
        /* write your code here */
        break;
    case A_boolUnitType::A_boolUOpExprKind:
        /* write your code here */
        break;
    default:
        break;
    }
    return;
}

aA_type check_ExprUnit(std::ostream *out, aA_exprUnit eu)
{
    // validate the expression unit and return the aA_type of it
    // you may need to check if the type of this expression matches with its
    // leftvalue or rightvalue, so return its aA_type would be a good way.
    // Feel free to change the design pattern if you need.
    if (!eu)
        return nullptr;
    aA_type ret;
    switch (eu->kind)
    {
        //TODO:id可以为数组
    case A_exprUnitType::A_idExprKind:
    {
        /* write your code here */
        string name = *(eu->u.id);
        ret = id2Type(out,eu->pos,name);
    }
    break;
    case A_exprUnitType::A_numExprKind:
    {
        /* write your code here */
        ret = aA_Type(A_NativeType(eu->pos,A_nativeType::A_intTypeKind));
    }
    break;
    case A_exprUnitType::A_fnCallKind:
    {
        ret=check_FuncCall(out,eu->u.callExpr);
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arrayExprKind:
    {
        ret= check_ArrayExpr(out,eu->u.arrayExpr);
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_memberExprKind:
    {
        ret=check_MemberExpr(out,eu->u.memberExpr);
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arithExprKind:
    {
        ret = arithExpr2Type(out,eu->u.arithExpr);
        /* write your code here */
    }
    break;
    case A_exprUnitType::A_arithUExprKind:
    {
        ret= check_ExprUnit(out,eu->u.arithUExpr->expr);
        /* write your code here */
    }
    break;
    }
    return ret;
}

aA_type check_FuncCall(std::ostream *out, aA_fnCall fc)
{
    if (!fc)
        return nullptr;
    aA_type type;
    string error_info;
    //TODO:检查调用参数输入类型是否正确
    //获得函数名称
    string name = *(fc->fn);
    //检查函数是否存在
    if(func2Param.count(name)==0){
        //函数不存在，报错
        error_info= "function "+name+" is not defined";
        error_print(out, fc->pos, error_info);
    }else{
        //函数存在，比较参数列表
        vector<aA_rightVal> vals=fc->vals;
        vector<aA_varDecl> params = *(func2Param[name]);
        bool equal = true;
        if (vals.size() != params.size()) {
            equal = false;
            // 处理长度不同的情况
        } else {
            // 逐个比较两个 vector 的元素
            
            for (size_t i = 0; i < params.size(); ++i) {
                aA_type valType = rightVal2Type(out,vals[i]);
                if(params[i]->kind==A_varDeclType::A_varDeclScalarKind
                    &&!com_aA_type(params[i]->u.declScalar->type,valType)){
                        equal = false;
                        break;
                    }
                if(params[i]->kind==A_varDeclType::A_varDeclArrayKind
                    &&!com_aA_type(params[i]->u.declArray->type,valType)){
                        equal = false;
                        break;
                }
                
            }
        }
        if(!equal){
            error_info= "Mismatched function parameter types.";
            error_print(out, fc->pos, error_info);
        }
    }
    //返回函数类型
    type=func_token2Type[name];
    return type;
    // Example:
    //      foo(1, 2);

    /* write your code here */
    
}

void check_WhileStmt(std::ostream *out, aA_whileStmt ws)
{
    if (!ws)
        return;
    check_BoolExpr(out, ws->boolExpr);
    beforeBlock();
    for (aA_codeBlockStmt s : ws->whileStmts)
    {
        check_CodeblockStmt(out, s);
    }
    afterBlock();
    return;
}

void check_CallStmt(std::ostream *out, aA_callStmt cs)
{
    if (!cs)
        return;
    check_FuncCall(out, cs->fnCall);
    return;
}

void check_ReturnStmt(std::ostream *out, aA_returnStmt rs)
{
    if (!rs)
        return;
    return;
}
//比较参数列表类型
bool com_paramList(vector<aA_varDecl> vec1,vector<aA_varDecl> vec2){
    bool equal = true;
    // 检查两个 vector 的长度是否相同
    if (vec1.size() != vec2.size()) {
        equal = false;
        // 处理长度不同的情况
    } else {
        // 逐个比较两个 vector 的元素
        
        for (size_t i = 0; i < vec1.size(); ++i) {
            if ((vec1[i] == nullptr && vec2[i] != nullptr) 
                || (vec1[i] != nullptr && vec2[i] == nullptr) 
                || (vec1[i]->kind != vec2[i]->kind)) {
                equal = false;
                break;
            }else if(vec1[i]->kind==A_varDeclType::A_varDeclScalarKind && !com_aA_type(vec1[i]->u.declScalar->type,vec2[i]->u.declScalar->type)){
                //单个变量要进行类型对比
                equal = false;
                break;
            }else if(vec1[i]->kind==A_varDeclType::A_varDeclArrayKind && !com_aA_type(vec1[i]->u.declArray->type,vec2[i]->u.declArray->type)){
                //数组变量也要对比
                equal = false;
                break;
            }
        }
    }
    return equal;
}

//比较两个aA_type类型变量是否相等
bool com_aA_type(aA_type type1,aA_type type2){
    bool equal = true;
    //1.先比较是不是都是基本类型或者都是结构体类型
    if(type1->type!=type2->type){
        equal = false;
    //2.如果都是基本类型，比较基本类型是否相同,注意比较结构体时要比较string名称，而不是地址
    }else if((type1->type==A_dataType::A_nativeTypeKind && 
        type1->u.nativeType!=type2->u.nativeType)
        ||
        (type1->type==A_dataType::A_structTypeKind && 
        *(type1->u.structType)!=*(type2->u.structType))){
        equal = false;
    }
    return equal;
    
}

//得到变量声明的id
string aA_varDecl2Name(aA_varDecl varDecl){
    string name="";
    if(varDecl->kind==A_varDeclType::A_varDeclScalarKind){
        name = *(varDecl->u.declScalar->id);
    }else if(varDecl->kind==A_varDeclType::A_varDeclArrayKind){
        name = *(varDecl->u.declArray->id);
    }
    return name;
}

//得到变量声明的类型
aA_type aA_varDecl2Type(aA_varDecl varDecl){
    aA_type type;
    if(varDecl->kind==A_varDeclType::A_varDeclScalarKind){
        type = varDecl->u.declScalar->type;
    }else if(varDecl->kind==A_varDeclType::A_varDeclArrayKind){
        type = varDecl->u.declArray->type;
    }
    return type;
}

//检查类型是否存在
bool typeCheck(aA_type type){
    bool exist = true;
    if(type->type==A_dataType::A_nativeTypeKind){
        //返回类型为基本类型时,基本类型必定存在，合法
    }else if(type->type==A_dataType::A_structTypeKind&&struct2Members.count(*(type->u.structType))==0){
        //返回类型为结构体时，检查该结构体是否存在，若不存在，报错
        exist = false;
    }
    return exist;
}

//获得aA_type对应的真实类型
string type2Name(aA_type type){
    string name = "";
    if(type==NULL){
        
    }else if(type->type==A_dataType::A_nativeTypeKind){
        //返回类型为基本类型时,基本类型必定存在，合法
        switch(type->u.nativeType){
            case A_nativeType::A_intTypeKind:
                name = "int";
            break;
        }
    }else if(type->type==A_dataType::A_structTypeKind&&struct2Members.count(*(type->u.structType))!=0){
        //返回类型为结构体时，若结构体是否存在，返回结构体名称
        name = *(type->u.structType);
    }
    return name;
}

//通过id找到对应的类型
aA_type id2Type(std::ostream *out, A_pos pos ,string id){
    aA_type ret =NULL;
    if(g_token2Type.count(id)!=0){
        ret = g_token2Type[id];
    }
    if(funcparam_token2Type.count(id)!=0){
        ret = funcparam_token2Type[id];
    }
    if(localExist(id)){
        ret = local2Type(id);
    }
    if(ret==NULL){
        string error_info = id + " is not defined";
        error_print(out, pos, error_info);
    }
    return ret;
}

//通过变量名获得存储内容


//TODO:localExist用于检查局部变量是否处于作用域中,遍历之前的每一个大的代码块，如果有说明局部变量存在
bool localExist(string name){
    bool exist=false;
    for(typeMap* map :local_tokenVec){
        if(map->count(name)!=0){
            exist = true;
        }
    }
    return exist;
    
}
//TODO:local2Type用于获得局部变量的类型
aA_type local2Type(string name){
    for(typeMap* map :local_tokenVec){
        if(map->count(name)!=0){
            return map->at(name);
        }
    }
}

//TODO:addLocal2Type用于添加局部变量和类型,简易版，待修改
void addLocal2Type(string name,aA_type type){
    typeMap* map = local_tokenVec.back();
    (*map)[name] = type;
}

//用于检查局部变量中是否有该数组名的声明
bool localArrDeclExist(string name){
    bool exist=false;
    for(arrayDeclMap * map :localArrDeclVec){
        if(map->count(name)!=0){
            exist = true;
        }
    }
    return exist;
}
//用于检查局部变量中是否有该数组名的定义
bool localArrDefExist(string name){
    bool exist=false;
    for(arrayDefMap * map :localArrDefVec){
        if(map->count(name)!=0){
            exist = true;
        }
    }
    return exist;
}
//添加局部数组声明
void addLocalArrDecl(string name,aA_varDeclArray varDeclArray){
    arrayDeclMap * map = localArrDeclVec.back();
    (*map)[name] = varDeclArray;
}
//添加局部数组定义
void addLocalArrDef(string name,aA_varDefArray varDefArray){
    arrayDefMap * map = localArrDefVec.back();
    (*map)[name] = varDefArray;
}
//将局部数组类型返回
aA_type localArr2Type(string name){
    aA_type type;
    for(arrayDeclMap * map :localArrDeclVec){
        if(map->count(name)!=0){
            type = (*map)[name]->type;
        }
    }
    for(arrayDefMap * map :localArrDefVec){
        if(map->count(name)!=0){
            type = (*map)[name]->type;
        }
    }
    return type;
}


//必须与afterBlock()搭配使用，每次进入代码块都要新建一个管理生命周期的map，并添加到vector中
void beforeBlock(){
    //普通变量的map
    typeMap* block_token2Type = new typeMap;
    local_tokenVec.push_back(block_token2Type);

    //数组变量声明map
    arrayDeclMap * block_arrDecl= new arrayDeclMap;
    localArrDeclVec.push_back(block_arrDecl);
    //数组定义map
    arrayDefMap * block_arrDef= new arrayDefMap;
    localArrDefVec.push_back(block_arrDef);
}
//必须与beforeBlock()搭配使用，代码块结束，从vector中删除，表示生命周期结束，并释放内存
void afterBlock(){
    typeMap* block_token2Type = local_tokenVec.back();
    local_tokenVec.pop_back();
    delete block_token2Type;

    arrayDeclMap * block_arrDecl=localArrDeclVec.back();
    localArrDeclVec.pop_back();
    delete block_arrDecl;

    arrayDefMap * block_arrDef=localArrDefVec.back();
    localArrDefVec.pop_back();
    delete block_arrDef;
}


aA_type rightVal2Type(std::ostream* out,aA_rightVal rightVal){
    aA_type type;
    //检查右值类型是否相同,bool类型的右值暂时无法赋值，原生的类型只有int
    if(rightVal->kind==A_rightValType::A_arithExprValKind){
        type=arithExpr2Type(out,rightVal->u.arithExpr);
    }else if(rightVal->kind==A_rightValType::A_boolExprValKind){
        string error_info = "not supported bool type assign";
        error_print(out, rightVal->pos, error_info);
    }
    return type;
}

aA_type arithExpr2Type(std::ostream* out,aA_arithExpr arithExpr){
    aA_type type;
    aA_type leftType;
    aA_type rightType;
    switch (arithExpr->kind)
    {
        //对于操作表达式类型的右值,操作符两边都是整数可以计算
    case A_arithExprType::A_arithBiOpExprKind :
        leftType=arithExpr2Type(out,arithExpr->u.arithBiOpExpr->left);
        rightType=arithExpr2Type(out,arithExpr->u.arithBiOpExpr->right);
        if(leftType->type!=A_dataType::A_nativeTypeKind
            ||rightType->type!=A_dataType::A_nativeTypeKind
            ||leftType->u.nativeType!=A_nativeType::A_intTypeKind
            ||rightType->u.nativeType!=A_nativeType::A_intTypeKind){
            //如果左值或者右值不是整数，则报错
            string error_info = "rightVal cannot be operated";
            error_print(out, arithExpr->pos, error_info);
        }
        type = leftType;
        /* code */
        break;
        //对于基本表达式
    case A_arithExprType::A_exprUnitKind :
        type = check_ExprUnit(out,arithExpr->u.exprUnit);
        break;
    default:
        break;
    }
    return type;
}