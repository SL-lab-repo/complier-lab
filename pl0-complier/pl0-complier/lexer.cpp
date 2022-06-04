//
//  lexer.cpp
//  pl0-complier
//
//  Created by sl on 2022/6/4.
//

#include "lexer.hpp"
#include <fstream>

/**
 PL / 0 词法构成：
  （1） keyword：begin，call，const，do，end，if，odd，procedure，read，then，var，while，write
  （2） identifier
  （3） number
  （4） operator： + ， - ， * ， / ，: = ，<， <= ，>， >=
  （5） demiliter：, ，.，; ，#
 */

vector<string>  res;
vector<string>  vars;

// symbol table
string symbol[32] = {
    "nul","ident","number","plus","minus","times",
    "slash","oddsym","eql","neq",
    "lss","leq","gtr","geq","lparen","rparen","comma","semicolon",
    "period","becomes",
    "beginsym","endsym","ifsym","thensym","whilesym","writesym",
    "readsym","dosym","callsym",
    "constsym","varsym","programsym"
};

// delimiter and operator
string op[16] = {
    ",",";",".","(",")","+","-","*","/",
    "<",">",":=",">=","<=","#","=" };

// index of operator
int op_index[16] = { 16,17,18,14,15,3,4,5,6,10,12,19,13,11,9,8 };

// keywords
string keyword[13] = {
    "begin","call","const","do","end","if","odd",
    "procedure","read","then","var","while","write"};

// index of keyword
int keyword_index[13] = {20,28,29,27,21,22,7,31,26,23,30,24,25};

// scan number
bool isNumber(char ch)
{
    if (ch >= '0' && ch <= '9')
        return true;
    
    return false;
}

// scan letter
bool isLetter(char ch)
{
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        return true;
    
    return false;
}

// scan delimiter
bool isDelimiter(string word)
{
    if (word[0] == ',' || word[0] == ';' || word[0] == '.' || word[0] == '(' || word[0] == ')')
        return true;
    
    return false;
}

// scan operator
bool isOperator(string word)
{
    if (word[0] == '+' || word[0] == '-' || word[0] == '*' || word[0] == '/' || word[0] == '<' || word[0] == '>' || word == ":=" || word == ">=" || word == "<=" || word[0] == '#' || word[0] == '=')
        return true;
    
    return false;
}

// scan uInt
bool isConst(string word)
{
    if(word=="")
        return false;
    
    for (int i = 0; i < word.length(); i++)
    {
        if (!isNumber(word[i]))   //不是数字
            return false;
    }
    
    return true;
}

// scan keyword
int isKeyword(string word)
{
    for (int i = 0; i < 13; i++)
    {
        if (word == keyword[i])
            return i;
    }
    
    return -1;
}

// print token
void printToken(string sym, string value)
{
    cout << "    ( " << setw(11) << setiosflags(ios::left) << sym << setw(3) << "," << setw(11)<< setiosflags(ios::left) << value << " ) " << endl;
}

void consume(string& word){
    word = "";
}

// 单词识别
void scan(string& word)
{
    // scan delimiter and operator
    if (isDelimiter(word) || isOperator(word)) {
        for (int i = 0; i < 16; i++){
            if (word == op[i]) {
                printToken(word, symbol[op_index[i]]);
                res.push_back(word);
            }
        }
    }
    // scan const
    else if (isConst(word)) {
        printToken(word, symbol[2]);
        res.push_back(word);
    }
    // scan keyword
    else if (isKeyword(word)!=-1) {
        printToken(word, symbol[keyword_index[isKeyword(word)]]);
        res.push_back(word);
    }
    // scan id
    else {
        // illegal
        if (!isLetter(word[0]) && !isNumber(word[0])) {
            return;
        }
        // legal
        else {
            printToken(word, symbol[1]);
            res.push_back(word);
            vars.push_back(word);
        }
    }
    
    consume(word);
}

void getSym() {
    cout << "Tokens：\n";
    
    FILE* file=nullptr;
    string path="test.txt";
    
    file = fopen(path.c_str(), "r");
    if (!file) {
        cout << "failed to open the target file!\n";
        return ;
    }
    // scan by char
    string word;
    char ch=' ';
    while ((ch = fgetc(file)) != EOF) {
        if (ch == ' ' || ch == '\n' || ch == '\t') {
            // not null
            if (word.length() > 0) {
                scan(word);
                word = "";
            }
        }
        else if (isNumber(ch)) {
            if (word.length() > 0) {
                if (!isNumber(word[0]) && !isLetter(word[0])) {
                    scan(word);
                    word = ch;
                }
                else
                    word += ch;
                continue;
            }
            else
                word += ch;
        }
        else if (isLetter(ch)) {
            if (word.length() > 0) {
                if (isNumber(word[0])) {
                    scan(word);
                    word = ch;
                    continue;
                }
                else if (isLetter(word[0])) {
                    word += ch;
                    continue;
                }
                else {
                    scan(word);
                    word = ch;
                    continue;
                }
            }
            else
                word += ch;
        }
        else if (ch == '=') {
            word += ch;
        }
        // other
        else {
            if (word.length() > 0) {
                scan(word);
                word += ch;
                continue;
            }
            else
                word += ch;
        }
    }
    
    // last word
    scan(word);
    fclose(file);
}
