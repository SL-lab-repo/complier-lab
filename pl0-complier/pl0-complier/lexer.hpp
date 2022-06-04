//
//  lexer.hpp
//  pl0-complier
//
//  Created by sl on 2022/6/4.
//

#ifndef lexer_hpp
#define lexer_hpp

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

extern vector<string>  res;      //词法分析结果
extern vector<string>  vars;    //合法声明变量

/**
 Handle Char
 */
bool isNumber(char);                // 识别数字
bool isLetter(char);                // 识别字符
bool isDelimiter(string);           // 识别界符
bool isOperator(string);            // 识别运算符


/**
 Handle Word
 */
int isKeyword(string);              // 识别保留字

bool isConst(string);               // 识别无符号整数

void scan(string&);                //单词处理

void printToken(string, string);    // 打印token

void getSym();                      //词法分析

#endif /* lexer_hpp */
