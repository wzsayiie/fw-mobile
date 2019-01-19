#pragma once

#include "types.h"

struct utf8_finfo {
    
    //there isn't BOM on start.
    //only contains '\n' (not contain '\r' and '\r\n')
    vector<char> content;
    
    bool has_bom = false;
    bool has_rn  = false;
    bool has_r   = false;
    bool has_n   = false;
};

enum class utf8_ferr {
    no_err       = 0,
    param_invail = 1,
    open_failed  = 2,
    not_utf8     = 3,
};

utf8_ferr utf8_fread(const string &path, utf8_finfo *info);

utf8_ferr utf8_fwrite(const string &path, const utf8_finfo &info);
