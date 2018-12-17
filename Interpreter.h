#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <string>
#include <iostream>

#include "Token.h"

using namespace std;

class Interpreter {
public:
    Interpreter(const string& path);
    Interpreter(const Interpreter& orig);
    virtual ~Interpreter();
    void action(const Token& token);
private:
    void write_tab();
    ofstream f;
    int tab = 0;
};

#endif /* INTERPRETER_H */

