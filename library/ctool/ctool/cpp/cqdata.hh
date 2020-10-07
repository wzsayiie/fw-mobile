#pragma once

#include "cqctoolbase.hh"

_CQCTOOL_BEGIN_VERSION_NS

struct cqData {
    
    static bool readFile(const std::string &path, std::vector<uint8_t> *data);
    static bool readFile(const std::string &path, std::string *string);
    
    template<class T, class N>
    static bool writeFile(const std::string &path, T *items, N count) {
        return _writeFile(path, (uint8_t *)items, (int)(sizeof(T) * count));
    }
    
    //NOTE: if input file data is empty(bytes == null || length <= 0),
    //the file will be made empty.
    static bool _writeFile(const std::string &path, uint8_t *bytes, int length);
};

_CQCTOOL_END_VERSION_NS
