#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <iostream>
#include <fstream>

#define BUFFER_SIZE 10

using namespace std;

class Buffer {
public:
    Buffer(const string& file_path);
    Buffer(const Buffer& orig);
    virtual ~Buffer();
    
    char next();
    char retract(int n = 0);
    
    char current() const;
    bool done() const;
    void settle();
    
    void print();
    
private:
    ifstream f;
    char *buffer;
    int size_left, size_right;
    int ptr_begin, ptr_end;
    
    void load_buffer_left();
    void load_buffer_right();
};

#endif /* BUFFER_H */

