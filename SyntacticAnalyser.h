#ifndef SYNTACTICANALYSER_H
#define SYNTACTICANALYSER_H

#define BUFFER_SIZE 10

#include <string>
#include <iostream>
#include "Token.h"
#include "Buffer.h"

using namespace std;

class SyntacticAnalyser {
public:
    SyntacticAnalyser(const string& path_to_file);
    SyntacticAnalyser(const SyntacticAnalyser& orig);
    virtual ~SyntacticAnalyser();
    Token get_next_token();
private:
    Buffer buffer;
    
    bool is_letter(char current);
    bool is_space(char current);
    bool is_char(char current);
    Token automaton(int state = 0);
    Token retract_return(int n_retract);
};

#endif /* SYNTACTICANALYSER_H */

