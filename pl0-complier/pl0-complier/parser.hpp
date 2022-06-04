//
//  parser.hpp
//  pl0-complier
//
//  Created by sl on 2022/6/4.
//

#ifndef parser_hpp
#define parser_hpp

#include "lexer.hpp"

#include<iostream>
#include<string>
#include <fstream>
#include <sstream>

using namespace std;

extern bool success;    //语法正确标志

void program();         //主程序
void subProgram();      //子程序
void constExplain();     //常量说明
void varExplain();      //变量说明
void proExplain();      //过程说明

void consDef();         //常量定义
void stmt();            //语句
void id();              //标识符
void uInt();            //无符号整数

void proHead();         //过程首部
void proCall();         //过程调用

void item();            //项
void factor();          //因子
void addOrSub();        //加减
void mulOrDiv();        //乘除
void relOp();           //关系运算
void expr();             //表达式
void condition();       //条件

void assignStmt();      //赋值语句
void composeStmt();     //复合语句
void CondStmt();        //条件语句
void doWhile();         //do-while

void readStmt();        //读语句
void writeStmt();       //写语句

bool isExist(string);   //变量是否声明


#endif /* parser_hpp */
