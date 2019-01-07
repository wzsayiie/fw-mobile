#pragma once

#include "types.h"

struct utf8_finfo {
    
    //there isn't BOM on start.
    //only contains '\n' (not contain '\r' and '\r\n')
    vector<char> content;
    
    bool only_ascii;
    bool has_bom;
    bool has_rn;
    bool has_r;
    bool has_n;
};

enum class utf8_ferr {
    no_err       = 0,
    param_invail = 1,
    open_failed  = 2,
    not_utf8     = 3,
};

utf8_ferr utf8_fread(const string &path, utf8_finfo *info);

utf8_ferr utf8_fwrite(const string &path, const utf8_finfo &info);
