#include "Interpreter.h"

Interpreter::Interpreter(const string& path) {
    f.open(path);
}

Interpreter::Interpreter(const Interpreter& orig) {
}

Interpreter::~Interpreter() {
    f.close();
}

void Interpreter::action(const Token& token) {
    auto type = token.get_type();
    auto value = token.get_value();
    
    if (type == Token::TYPE::KEYWORD) {
        string str;
        f << '\n';
        
        if (value == Token::KEYWORD::BEGIN || value == Token::KEYWORD::LEFT_PARENTHESIS) {
            if (value == Token::KEYWORD::BEGIN) str = "begin";
            if (value == Token::KEYWORD::LEFT_PARENTHESIS) str = "(";
            
            write_tab();
            tab++;
            f << str << "\n";
            write_tab();
        }
        
        if (value == Token::KEYWORD::END || value == Token::KEYWORD::RIGHT_PARENTHESIS) {
            if (value == Token::KEYWORD::END) str = "end";
            if (value == Token::KEYWORD::RIGHT_PARENTHESIS) str = ")";
            
            tab--;
            write_tab();
            f << str << "\n";
            write_tab();
        }

    }
    
    else if (type == Token::TYPE::CHAR) {
        if (value != '\t') f << value;
        if (value == '\n') write_tab();
    }
}

void Interpreter::write_tab() {
    for (int i = 0 ; i < tab ; i++) f << '\t';
}
