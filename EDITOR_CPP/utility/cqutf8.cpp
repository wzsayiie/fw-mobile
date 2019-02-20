#include "cqutf8.hh"

bool CQStartsWithUTF8BOM(const char *ptr, const char *end) {
    if (ptr == nullptr) {
        return false;
    }
    if (ptr + CQUTF8BOMSize > end) {
        return false;
    }
    
    if (strncmp(ptr, CQUTF8BOM, CQUTF8BOMSize) == 0) {
        return true;
    } else {
        return false;
    }
}

size_t CQGetUTF8Char(const char *ptr, const char *end, char *ascii) {
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

bool CQUTF8Check(const char *ptr, const char *end, bool *_adjusted, vector<char> *_out) {
    bool adjusted = false;
    vector<char> out;
    
    if (CQStartsWithUTF8BOM(ptr, end)) {
        ptr += CQUTF8BOMSize;
        adjusted = true;
    }
    
    while (ptr < end) {
        char ascii = 0;
        size_t size = CQGetUTF8Char(ptr, end, &ascii);
        
        if (size == 1) {
            
            if (ascii == '\r' && ptr + 1 < end && ptr[1] == '\n') {
                out.push_back('\n');
                ptr += 2;
            } else if (ascii == '\r') {
                out.push_back('\n');
                ptr += 1;
            } else {
                out.push_back(ascii);
                ptr += 1;
            }
            
        } else if (size > 1) {
            
            out.insert(out.end(), ptr, ptr + size);
            ptr += size;
            
        } else /* size == 0 */ {
            
            break;
        }
    }
    
    if (ptr == end) {
        if (_adjusted != nullptr) {
            *_adjusted = adjusted;
        }
        if (_out != nullptr) {
            _out->clear();
            _out->swap(out);
        }
        return true;
    } else {
        return false;
    }
}
