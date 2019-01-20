#pragma once

#include "types.h"

bool utf8_verify(
    const char *stream,
    const char *end,
    bool *only_ascii = nullptr,
    bool *has_rn = nullptr,
    bool *has_n = nullptr,
    bool *has_r = nullptr
);

struct utf8_finfo {
    
    //there isn't BOM on start.
    //only contains '\n' (not contain '\r' and '\r\n')
    string content;
    
    bool has_bom = false;
    bool has_rn  = false;
    bool has_n   = false;
    bool has_r   = false;
};

bool utf8_fread(const string &path, utf8_finfo *info);
bool utf8_fwrite(const string &path, const utf8_finfo &info);
