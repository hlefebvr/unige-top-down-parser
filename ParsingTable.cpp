#include <stdexcept>

#include "ParsingTable.h"

using namespace std;

ParsingTable::ParsingTable() {}

ParsingTable::ParsingTable(const ParsingTable& orig) {}

ParsingTable::~ParsingTable() {}

vector<Token> ParsingTable::operator()(const Token& X, const Token& a) const {
    if (X.get_type() != Token::TYPE::NON_TERMINAL)
        throw invalid_argument("Expected non_terminal symbol as first argument");
    if (a.get_type() == Token::TYPE::NON_TERMINAL)
        throw invalid_argument("Expected terminal symbol as first argument");

    auto X_value = X.get_value();
    auto a_type = a.get_type();
    auto a_value = a.get_value();
    
    if (X_value == Token::NON_TERMINAL::PGM) {
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::BEGIN)
            return { Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::STMTS) };
    }
    
    if (X_value == Token::NON_TERMINAL::STMTS) {
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::BEGIN)
            return { Token(Token::TYPE::KEYWORD, Token::KEYWORD::BEGIN),
                    Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::TXT),
                    Token(Token::TYPE::KEYWORD, Token::KEYWORD::END)
            };
    }
    
    if (X_value == Token::NON_TERMINAL::TXT) {
        if (a_type == Token::TYPE::CHAR)
            return { Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::LETTER),
                    Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::TXT)
            };
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::LEFT_PARENTHESIS)
            return { 
                Token(Token::TYPE::KEYWORD, Token::KEYWORD::LEFT_PARENTHESIS),
                Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::TXT),
                Token(Token::TYPE::KEYWORD, Token::KEYWORD::RIGHT_PARENTHESIS),
                Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::TXT) // added
            };
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::RIGHT_PARENTHESIS)
            return {}; // empty string ?
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::BEGIN)
            return { Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::STMTS),
                    Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::TXT)
            };
        if (a_type == Token::TYPE::KEYWORD && a_value == Token::KEYWORD::END)
            return {}; // empty string ?
    }
    
    if (X_value == Token::NON_TERMINAL::LETTER && a_type == Token::TYPE::CHAR) {
        return {}; // empty string ? WTF ?
    }
    
    cout << "X : (" << X.get_type() << ", " << (int) X.get_value() << ")" << endl;
    cout << "a : (" << X.get_type() << ", " << a.get_value() << ")" << endl;
    
    throw invalid_argument("No entry in parsing table");
}
