#include "unicode.hh"

int check_utf8(const char *ptr, const char *end) {
    int size = 0;
    
    //check first byte:
    if (ptr == nullptr) {
        return 0;
    }
    else if ((*ptr & 0b10'00'0000) == 0b00'00'0000) { size = 1; }
    else if ((*ptr & 0b11'10'0000) == 0b11'00'0000) { size = 2; }
    else if ((*ptr & 0b11'11'0000) == 0b11'10'0000) { size = 3; }
    else if ((*ptr & 0b11'11'1000) == 0b11'11'0000) { size = 4; }
    else {
        return 0;
    }
    if (ptr + size > end) {
        return 0;
    }
    
    //check followed bytes:
    for (const char *it = ptr + 1; it < ptr + size; ++it) {
        if ((*it & 0b11'00'0000) != 0b10'00'0000) {
            return 0;
        }
    }
    
    return size;
}
