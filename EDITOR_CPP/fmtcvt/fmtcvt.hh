#pragma once

#include "toolset.hh"

namespace fmtcvt {

    enum class want {
        none, unix, win,
    };

    struct handler {
        virtual void proc(const vector<string> &paths);
        virtual int  once(const string &path);
        virtual int  adir(const string &name, int deep);
        virtual int  afil(const string &name, int deep);
        virtual want pick(const string &name);
    };
}
