//
//  Num.hpp
//  pl0-complier
//
//  Created by sl on 2022/5/31.
//

#ifndef Num_hpp
#define Num_hpp

#include <stdio.h>
#include "string"
#include "Token.hpp"

class Num : public Token{
    int value;
    
public:
    Num(int _value,Tag _tag){
        value = _value;
        tag = _tag;
    }
    
    std::string toString(){return std::to_string(value);}
};

#endif /* Num_hpp */
