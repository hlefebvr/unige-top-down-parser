#ifndef TOKEN_H
#define TOKEN_H

class Token {
public:
    enum TYPE { CHAR, KEYWORD, END_OF_FILE };
    enum KEYWORD { BEGIN, END, LEFT_PARENTHESIS, RIGHT_PARENTHESIS };
    
    Token(TYPE type, char value);
    Token(const Token& orig);
    TYPE get_type() const { return type; }
    char get_value() const { return value; }
    
private:
    TYPE type;
    char value;
};

#endif /* TOKEN_H */

