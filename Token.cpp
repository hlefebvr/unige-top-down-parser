#include "Token.h"

Token::Token(TYPE type, char value) : value(value), type(type) {
}

Token::Token(const Token& orig) : type(orig.type), value(orig.value) {}
