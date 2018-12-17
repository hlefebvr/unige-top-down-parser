#include "Buffer.h"

Buffer::Buffer(const string& file_path) {
    f.open(file_path);
    buffer = new char[2 * BUFFER_SIZE];
    
    f.readsome(buffer, 2 * BUFFER_SIZE);
    int n_char_read = f.gcount();
    
    size_left = (n_char_read < BUFFER_SIZE) ? n_char_read : BUFFER_SIZE;
    size_right = (n_char_read > BUFFER_SIZE) ? n_char_read - BUFFER_SIZE : 0;
    
    ptr_begin = 0;
    ptr_end = -1;
}

Buffer::Buffer(const Buffer& orig) {}

Buffer::~Buffer() {
    f.close();
}

void Buffer::print() {
    
    for (int i = 0 ; i < size_left ; i++) {
        if (i == ptr_begin) cout << "[";
        if (i == ptr_end) cout << "]";
        
        if (buffer[i] == '\n') cout << "\\n";
        else cout << buffer[i];
    }
    
    cout << "|";
    
    for (int i = BUFFER_SIZE ; i < BUFFER_SIZE + size_right ; i++) {
        if (i == ptr_begin) cout << "[";
        if (i == ptr_end) cout << "]";
        
        if (buffer[i] == '\n') cout << "\\n";
        else cout << buffer[i];
    }
    
    cout << endl;
}

char Buffer::current() const {
    return buffer[ptr_end];
}

void Buffer::settle() {
    if (ptr_begin <= BUFFER_SIZE && ptr_end > BUFFER_SIZE)
        load_buffer_left();
    if (ptr_begin >= BUFFER_SIZE && ptr_end <= BUFFER_SIZE)
        load_buffer_right();
    
    ptr_begin = ptr_end;
}
 
char Buffer::next() {
    ptr_end = (ptr_end + 1) % (2 * BUFFER_SIZE);
    
    return current();
}

bool Buffer::done() const {
    return (size_left == 0 && ptr_begin >= BUFFER_SIZE + size_right) ||
            (size_right == 0 && ptr_begin >= size_left);
}

void Buffer::load_buffer_left() {
    f.readsome(buffer, BUFFER_SIZE);
    size_left = f.gcount();
}

void Buffer::load_buffer_right() {
    f.readsome(buffer + BUFFER_SIZE, BUFFER_SIZE);
    size_right = f.gcount();
}

char Buffer::retract(int n) {
    ptr_end -= n;
    
    // if (ptr_end <= ptr_begin) throw std::invalid_argument("Cannot retract beyond");

    return current();
}
