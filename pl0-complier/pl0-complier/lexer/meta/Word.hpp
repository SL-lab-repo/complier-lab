//
//  Word.hpp
//  pl0-complier
//
//  Created by sl on 2022/5/31.
//

#ifndef Word_hpp
#define Word_hpp

#include <stdio.h>
#include "string"
#include "Token.hpp"

class Word : public Token{
public:
    std::string lexeme;
    
    Word(std::string _lexeme, Tag _tag){
        lexeme = _lexeme;
        tag = _tag;
    }
    
    std::string toString(){return lexeme;}
};

namespace ConstWord{

inline Word and_w("&&",Tag::AND);
inline Word or_w("||",Tag::OR);

};


#endif /* Word_hpp */
