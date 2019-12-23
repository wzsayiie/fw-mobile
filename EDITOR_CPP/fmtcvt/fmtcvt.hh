#pragma once

#include "toolset.hh"

struct fmt_cvt {
    
    virtual void process(const vector<string> &paths);
    
    virtual int a_stage(const string &path);
    virtual int for_dir(const string &name, int deep);
    virtual int on_file(const string &name, int deep);
    
    enum want {
        want_none,
        want_unix,
        want_win ,
    };
    virtual want pick(const string &name);
};
