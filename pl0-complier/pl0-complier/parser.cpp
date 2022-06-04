//
//  parser.cpp
//  pl0-complier
//
//  Created by sl on 2022/6/4.
//

#include "parser.hpp"

int ind;
bool success = 1;

//检查变量申明
bool isExist(string id)
{
    for (int i = 0; i < vars.size(); i++)
        if (id == vars[i])
            return 1;
    return 0;
}

//主程序
void  program()
{
    cout << "Grammar analyse：\n\t";
    
    ind = 0;
    subProgram();
    if (res[ind] != ".") {
        cout << "  grammar error: program should end up with '.'\n";
        exit(0);
    }
    
    cout << "  grammar annalyse pass!\n";
}

//子程序
void subProgram()
{

    //常量解析
    if (res[ind] == "const")
        consExplain();
    
    //变量解析
    if (res[ind] == "var")
        varExplain();
    
    //过程解析
    if (res[ind] == "procedure")
        proExplain();
    
    //语句解析
    stmt();
}

//常量说明
void consExplain()
{
    if (res[ind] != "const")
    {
        cout << "  consExplain error: mismatch keyword 'const'\n ";
        exit(0);
    }
    
    ++ind;
    consDef();
    while (res[ind] == "，")
    {
        ++ind;
        consDef();
    }
    
    if (res[ind] != ";"){
        cout << "  consExplain error: mismatch the ';' in the end\n";
        exit(0);
    }
    
    ++ind;
}

//变量说明
void varExplain()
{
    if (res[ind] != "var"){
        cout << "  varExplain error: missmath keyword 'var'\n ";
        exit(0);
    }
    
    ++ind;
    id();
    while (res[ind] == ","){
        ++ind;
        id();
    }

    if (res[ind] != ";"){
        cout << "  varExplain error: mismatch the ';' in the end\n";
        exit(0);
    }
    
    ++ind;
}

// 过程说明
void proExplain()
{
    proHead();
    subProgram();
    
    if (res[ind] != ";"){
        cout << "  proExplain error: mismatch the ';' in the end\n";
        exit(0);
    }
    
    ++ind;
    while (res[ind] == "procedure")
        proExplain();
}

// 语句
void stmt()
{
    if (isExist(res[ind]))                   //赋值语句
        assignStmt();
    else if (res[ind] == "if")               //条件语句
        CondStmt();
    else if (res[ind] == "while")            //dowhile
        doWhile();
    else if (res[ind] == "call")             //过程调用
        proCall();
    else if (res[ind] == "read")             //读语句
        readStmt();
    else if (res[ind] == "write")            //写语句
        writeStmt();
    else if (res[ind] == "begin")            //复合语句
        composeStmt();
    else if (res[ind] == "end")
        ;
    else{
        cout << "stmt error: undefined state (" << res[ind] << ") in parser.cpp::stmt()\n";
        exit(0);
    }
}

//常量定义
void consDef()
{
    id();
    
    if (res[ind] != "="){
        cout << "  consDef error: mismatch the '=' " << endl;
        exit(0);
    }
    
    ++ind;
    uInt();
}

//标识符
void id()
{
    if (! isExist(res[ind])){
        cout << "  id error: illegal id" << endl;
        exit(0);
    }
    
    ++ind;
}

//无符号整数
void uInt()
{
    if (! isConst(res[ind])){
        cout << "  uInt error: illegal uInt" << endl;
        exit(0);
    }
    
    ++ind;
}

//过程首部
void proHead()
{
    if (res[ind] != "procedure"){
        cout << "  proHead error: mismatch keyword 'procedure'\n";
        exit(0);
    }
    
    ++ind;
    id();
    
    if (res[ind] != ";"){
        cout << "  proHead error: mismatch the ';' in the end\n";
        exit(0);
    }
    
    ++ind;
}

//赋值语句
void assignStmt()
{
    id();
    
    if (res[ind] != ":="){
        cout << "  assignStmt error: mismatch the ‘:=’\n";
        exit(0);
    }
    
    ++ind;
    exp();
}

//表达式
void exp()
{
    if (res[ind] == "+" || res[ind] == "-")
        ++ind;
    
    item();
    while (res[ind] == "+" || res[ind] == "-"){
        addOrSub();
        item();
    }

}

//复合语句
void composeStmt()
{
    if (res[ind] != "begin"){
        cout << "  composeStmt error: 'begin'-like error\n";
        exit(0);
    }
    
    ++ind;
    stmt();
    while (res[ind] == ";"){
        ++ind;
        stmt();

    }
    
    if (res[ind] != "end"){
        cout << "  composeStmt error: 'end'-like error\n";
        exit(0);
    }
    
    ++ind;

}

//条件
void condition()
{
    if (res[ind] == "odd"){
        ++ind;
        exp();
    }
    else{
        exp();
        relOp();
        exp();
    }
}

//项
void item()
{
    factor();
    
    while (res[ind] == "*" || res[ind] == "/"){
        mulOrDiv();
        factor();
    }
}

//因子
void factor()
{
    if ((res[ind].at(0) <= 122 && res[ind].at(0) >= 97))      //首字符是字母---标识符
        id();
    else if ((res[ind].at(0) <= 57 && res[ind].at(0) >= 48))  //首字符是数字---无符号整数
        uInt();
    else if ((res[ind] == "(")){
        exp();
        
        if (res[ind] != ")"){
            cout << "  factor error: lack ')'\n";
            exit(0);
        }
        
        ++ind;
    }
    else{
        cout << "  factor error: lack '('\n";
        exit(0);
    }

}

//加减运算符
void addOrSub()
{
    if (res[ind] == "+" || res[ind] == "-")
        ++ind;
    else{
        cout << "  addORsub error: operator error\n";
        exit(0);
    }
}

//乘除运算符
void mulOrDiv()
{
    if (res[ind] == "*" || res[ind] == "/")
        ++ind;
    else{
        cout << "  mulORdiv error: operator error\n";
        exit(0);
    }
}

//关系运算符
void relOp()
{
    if (res[ind] == "="
        || res[ind] == "#"
        || res[ind] == "<"
        || res[ind] == "<="
        || res[ind] == ">"
        || res[ind] == ">=")
        ++ind;
    else{
        cout << "  relOp error: operator error\n";
        exit(0);
    }
}

//条件语句
void CondStmt()
{
    if (res[ind] != "if"){
        cout << "  condStmt error: mismatch keyword 'if'\n";
        exit(0);
    }
    
    ++ind;
    condition();
    
    if (res[ind] != "then"){
        cout << "  condStmt error: mismatch keyword 'then'\n";
        exit(0);
    }
    
    ++ind;
    stmt();
}

//过程调用语句
void proCall()
{
    if (res[ind] != "call"){
        cout << "  proCall error: mismatch keyword 'call'\n";
        exit(0);
    }
    
    ++ind;
    id();
}

//do-while
void doWhile()
{
    if (res[ind] != "while"){
        cout << "  doWhile error: mismatch keyword 'while'\n";
        exit(0);
    }
    
    ++ind;
    condition();
    
    if (res[ind] != "do"){
        cout << "  doWhile error: mismatch keyword 'do'\n";
//        success = 0;
        exit(0);
    }
    
    ++ind;
    stmt();
}

//读语句
void readStmt()
{
    if (res[ind] != "read"){
        cout << "  readStmt error: mismatch keyword 'read'\n";
        exit(0);
    }
    
    ++ind;
    if (res[ind] != "("){
        cout << "  readStmt error: lack '('\n";
        exit(0);
    }
    
    ++ind;
    id();
    
    while (res[ind] == ",")
    {
        ++ind;
        id();

    }
    
    if (res[ind] != ")"){
        cout << "  readStmt error: lack ')'\n";
        exit(0);
    }
    
    ++ind;
}

//写语句
void writeStmt()
{

    if (res[ind] != "write"){
        cout << "  writeStmt error: mismatch keyword 'write'\n";
        exit(0);
    }
    
    ++ind;
    
    if (res[ind] != "("){
        cout << "  writeStmt error: lack '('\n";
        exit(0);
    }
    
    ++ind;
    exp();
    while (res[ind] == ","){
        ++ind;
        exp();

    }
    
    if (res[ind] != ")"){
        cout << "  writeStmt error: lack ')'\n";
        exit(0);
    }
    
    ++ind;
}
