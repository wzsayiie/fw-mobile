#pragma once

#include "toolset.hh"

struct lang_coder {
    
    virtual string process(const string &tl);
    
    virtual bool on_loop(const string &name, string *text) = 0;
    virtual bool on_flag(const string &name, string *text) = 0;
};
