#include <cstdlib>
#include <string>
#include <iostream>

#include "Buffer.h"
#include "SyntacticAnalyser.h"

using namespace std;

int main(int argc, char** argv) {
    string input_file = "./input_example";
    
    auto analyzer = SyntacticAnalyser(input_file);
    
    for (int i = 0 ; i < 100 ; i++) {
        Token t = analyzer.get_next_token();
        Token::TYPE type = t.get_type();
        char value = t.get_value();
        
        if (type == Token::TYPE::CHAR) cout << "found : '" << value << "'" << endl;
        else if (type == Token::TYPE::END_OF_FILE) break;
        else if (value == Token::KEYWORD::BEGIN) cout << "found keyword 'begin'" << endl;
        else if (value == Token::KEYWORD::END) cout << "found keyword 'end'" << endl;
        else if (value == Token::KEYWORD::LEFT_PARENTHESIS) cout << "found keyword '('" << endl;
        else if (value == Token::KEYWORD::RIGHT_PARENTHESIS) cout << "found keyword ')'" << endl;
        else cout << "wtf : " << value << endl;
    }
    
    return 0;
}
