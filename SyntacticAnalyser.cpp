#include "SyntacticAnalyser.h"

using namespace std;

SyntacticAnalyser::SyntacticAnalyser(const string& path_to_file)
    : buffer(Buffer(path_to_file)) {}

SyntacticAnalyser::SyntacticAnalyser(const SyntacticAnalyser& orig)
    : buffer(Buffer(orig.buffer)) {}

SyntacticAnalyser::~SyntacticAnalyser() {}

bool SyntacticAnalyser::is_char(char current) {
    return is_letter(current) || current == '(' || current == ')';
}

bool SyntacticAnalyser::is_letter(char current) {
    return (current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z') || current == '.' || current == ',' || current == ';' || is_space(current) || (current >= '0' && current <= '9');
}

bool SyntacticAnalyser::is_space(char current) {
    return current == '\t' || current == '\n' || current == ' ';
}

Token SyntacticAnalyser::automaton(int state) {
    if (buffer.done()) return Token(Token::TYPE::END_OF_FILE, 0);
    
    char current = buffer.next();
    
    if (state == 0) {
        if (current == 'b') return automaton(1);
        if (current == 'e') return automaton(7);
        if (current == '(') return Token(Token::TYPE::KEYWORD, Token::KEYWORD::LEFT_PARENTHESIS);
        if (current == ')') return Token(Token::TYPE::KEYWORD, Token::KEYWORD::RIGHT_PARENTHESIS);
        if (is_letter(current)) return Token(Token::TYPE::CHAR, current);
    }
    
    if (state == 1) {
        if (current == 'e') return automaton(2);
        if (is_char(current)) return retract_return(1);
    }
    
    if (state == 2) {
        if (current == 'g') return automaton(3);
        if (is_char(current)) return retract_return(2);
    }
    
    if (state == 3) {
        if (current == 'i') return automaton(4);
        if (is_char(current)) return retract_return(3);
    }
    
    if (state == 4) {
        if (current == 'n') return automaton(5);
        if (is_char(current)) return retract_return(4);
    }
    
    if (state == 5) {
        if (is_space(current)) return Token(Token::TYPE::KEYWORD, Token::KEYWORD::BEGIN);
        if (is_char(current)) return retract_return(5);
    }
    
    if (state == 7) {
        if (current == 'n') return automaton(8);
        if (is_char(current)) return retract_return(1);
    }
    
    if (state == 8) {
        if (current == 'd') return automaton(9);
        if (is_char(current)) return retract_return(2);
    }
    
    if (state == 9) {
        if (is_space(current) || buffer.out()) return Token(Token::TYPE::KEYWORD, Token::KEYWORD::END);
        if (is_char(current)) return retract_return(3);
    }
    
    string error = "Unrecognized character : ' '.";
    error[25] = current;
    throw std::invalid_argument(error);
    
}

Token SyntacticAnalyser::retract_return(int n_retract) {
    return Token(Token::TYPE::CHAR, buffer.retract(n_retract));
}


Token SyntacticAnalyser::get_next_token() {
    Token t = automaton();
    buffer.settle();
    return t;
}
