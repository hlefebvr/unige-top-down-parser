#ifndef PARSINGTABLE_H
#define PARSINGTABLE_H

#include <vector>
#include <iostream>

#include "Token.h"

using namespace std;

class ParsingTable {
public:
    ParsingTable();
    ParsingTable(const ParsingTable& orig);
    virtual ~ParsingTable();
    vector<Token> operator()(const Token& X, const Token& a) const;
private:

};

#endif /* PARSINGTABLE_H */

