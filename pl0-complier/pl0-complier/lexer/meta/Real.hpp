//
//  Real.hpp
//  pl0-complier
//
//  Created by sl on 2022/5/31.
//

#ifndef Real_hpp
#define Real_hpp

#include <stdio.h>
#include "string"
#include "Token.hpp"

class Real:public Token{
    double value;
    
public:
    Real (double _value,Tag _tag){
        value = _value;
        tag = _tag;
    }
    
    std::string toString(){return std::to_string(value);}
};

#endif /* Real_hpp */
