#include "Token.h"

#include <iostream>

Token::Token(TYPE type, char value) : value(value), type(type) {
}

Token::Token(const Token& orig) : type(orig.type), value(orig.value) {}

bool Token::operator==(const Token& other) {
    if (type == Token::TYPE::CHAR && other.type == Token::TYPE::NON_TERMINAL && other.value == Token::NON_TERMINAL::LETTER)
        return true;
    
    if (type == other.type) {
        if (type == Token::TYPE::CHAR) return true;
        return value == other.value;
    }
    return false;
}
