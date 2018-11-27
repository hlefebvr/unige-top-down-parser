#include <cstdlib>
#include <string>
#include <iostream>
#include <stack>

#include "Buffer.h"
#include "SyntacticAnalyser.h"
#include "ParsingTable.h"

using namespace std;

string to_words(const Token& token) {
    if (token.get_type() == Token::TYPE::NON_TERMINAL) {
        switch(token.get_value()) {
            case Token::NON_TERMINAL::LETTER: return "<LETTER>";
            case Token::NON_TERMINAL::STMTS: return "<STMTS>";
            case Token::NON_TERMINAL::PGM: return "<PGM>";
            case Token::NON_TERMINAL::TXT: return "<TXT>";
        }
    }
    if (token.get_type() == Token::TYPE::KEYWORD) {
        switch(token.get_value()) {
            case Token::KEYWORD::BEGIN: return "begin";
            case Token::KEYWORD::END: return "end";
            case Token::KEYWORD::LEFT_PARENTHESIS: return "(";
            case Token::KEYWORD::RIGHT_PARENTHESIS: return ")";
        }
    }
    
    if (token.get_type() == Token::TYPE::CHAR) return "a-z...";
    
    return "EOF";
}

void print(const Token& a) {
    auto type = a.get_type();
    char value = a.get_value();
    
    if (type == Token::TYPE::CHAR) cout << "found : '" << value << "'" << endl;
    else if (type == Token::TYPE::END_OF_FILE) cout << "EOF";
    else if (value == Token::KEYWORD::BEGIN) cout << "found keyword 'begin'" << endl;
    else if (value == Token::KEYWORD::END) cout << "found keyword 'end'" << endl;
    else if (value == Token::KEYWORD::LEFT_PARENTHESIS) cout << "found keyword '('" << endl;
    else if (value == Token::KEYWORD::RIGHT_PARENTHESIS) cout << "found keyword ')'" << endl;
    else cout << "wtf : " << value << endl;
}

int main(int argc, char** argv) {
    // string input_file = "./input_example";
    string input_file = "./false_example";
    
    auto analyzer = SyntacticAnalyser(input_file);
    
    // initialize table
    auto M = ParsingTable();
    
    // initialize stack
    stack<Token> stack;
    stack.push(Token(Token::TYPE::END_OF_FILE, 0));
    stack.push(Token(Token::TYPE::NON_TERMINAL, Token::NON_TERMINAL::PGM));
    
    // read first token
    Token a = analyzer.get_next_token();
    
    // iterate over tokens
    int i = 0;
    while(a.get_type() != Token::TYPE::END_OF_FILE && ++i < 200) {
        
        Token X = stack.top();
        stack.pop();
        
        cout << "Trying to reduce " << to_words(X) << endl;
        cout << "with... " << to_words(a) << endl;

        if ( a == X ) {
            
            print(a);
            
            a = analyzer.get_next_token(); // read next input token
            continue;
        }
        
        if ( X.get_type() != Token::TYPE::NON_TERMINAL ) {
            throw invalid_argument("Non terminal symbol expected");
        }
        
        vector<Token> rule = M(X, a);
        for (auto it = rule.rbegin() ; it != rule.rend() ; it++) stack.push(*it);
        
    }
    
    if (stack.top().get_type() != Token::TYPE::END_OF_FILE)
        cout << "REJECTED" << endl;
    
    cout << "Terminated" << endl;
    
    return 0;
}

// recognizing "end" : space or eof
