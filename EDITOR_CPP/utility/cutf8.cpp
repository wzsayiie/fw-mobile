#include "cutf8.h"

bool CStartsWithUTF8BOM(const char *ptr, const char *end) {
    if (ptr == nullptr) {
        return false;
    }
    if (ptr + CUTF8BOMSize > end) {
        return false;
    }
    
    if (strncmp(ptr, CUTF8BOM, CUTF8BOMSize) == 0) {
        return true;
    } else {
        return false;
    }
}

size_t CGetUTF8Char(const char *ptr, const char *end, char *ascii) {
    int size = 0;
    
    //check first byte
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
    
    //check followed bytes
    for (const char *it = ptr + 1; it < ptr + size; ++it) {
        if ((*it & 0b11'00'0000) != 0b10'00'0000) {
            return 0;
        }
    }
    
    //return
    if (ascii != nullptr) {
        if (size == 1) {
            *ascii = *ptr;
        } else {
            *ascii = 0;
        }
    }
    return size;
}
