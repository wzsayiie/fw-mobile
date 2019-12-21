#pragma once

#include "toolset.hh"

namespace fmtcvt {

    enum class type {
        none, unix, win,
    };

    struct handler {
        virtual void proc(const vector<string> &paths);
        virtual void once(const string &path);
        virtual void adir(const string &name, int deep);
        virtual void afil(const string &name, int deep);
        virtual type pick(const string &name);
    };
}
