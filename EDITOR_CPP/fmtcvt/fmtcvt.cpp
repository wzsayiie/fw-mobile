#include "fmtcvt.hh"

namespace fmtcvt {

//supported files:

bool endwith(const string &suf, const string &val) {
    size_t v = val.size();
    size_t s = suf.size();
    return v > s && !val.compare(v - s, s, suf);
}

bool supported(const string &name) {
    static const vector<string> options = {
        ".h" , ".hh" , ".cpp", ".cxx", ".cc",
        ".m" , ".mm" ,
        ".cs",".java", ".lua"
    };
    for (auto &it : options) {
        if (endwith(it, name)) {
            return true;
        }
    }
    return false;
}

//print:

const char *idtname(const string &name, int deep) {
    static char str[64];
    sprintf(str, "%*s%s", deep * 2, "", name.c_str());
    return str;
}

void logdir  (const string &n, int d) {newline.i("|        | %s/", idtname(n, d));}
void logferr (const string &n, int d) {newline.i("[FILE ERR] %s" , idtname(n, d));}
void logempty(const string &n, int d) {newline.i("[ EMPTY  ] %s" , idtname(n, d));}
void logu8err(const string &n, int d) {newline.i("[UTF8 ERR] %s" , idtname(n, d));}

struct fmtdat {
    bool ch  = false;
    bool bom = false;
    bool rn  = false;
    bool n   = false;
    bool r   = false;
};

void logupdat(const string &name, int deep, fmtdat fmt) {
    newline.i(fmt.bom ?"[B ":"[  ");
    closeto.i(fmt.rn  ? "RN": "  ");
    closeto.i(fmt.n   ? " N": "  ");
    closeto.i(fmt.r   ? " R": "  ");
    closeto.i("] %s", idtname(name, deep));
}

void loglodat(const string &name, int deep, fmtdat fmt) {
    newline.i(fmt.bom ?"[b ":"[  ");
    closeto.i(fmt.rn  ? "rn": "  ");
    closeto.i(fmt.n   ? " n": "  ");
    closeto.i(fmt.r   ? " r": "  ");
    closeto.i("] %s", idtname(name, deep));
}

//scan:

bool scandat(const vector<char> &dat, type tp, fmtdat *newfmt, vector<char> *newdat) {
    //TODO
    return true;
}

//process:

void handler::proc(const vector<string> &paths) {
    for (auto &it : paths) {
        spac(1).i("@ %s:", it.c_str());
        spac(1);
        
        once(it);
    }
}

void handler::once(const string &path) {
    scan(path, [&](const fitem &item, int deep) {
        if (item.isdir) {
            adir(item.name, deep);
        } else {
            afil(item.name, deep);
        }
    });
}

void handler::adir(const string &name, int deep) {
    logdir(name, deep);
}

void handler::afil(const string &name, int deep) {
    if (!supported(name)) {
        return;
    }
    
    //read file.
    vector<char> dat;
    bool okay = readf(name, &dat);
    if (!okay) {
        logferr(name, deep);
        return;
    }
    
    if (dat.empty()) {
        logempty(name, deep);
        return;
    }
    
    //scan file.
    fmtdat newfmt;
    vector<char> newdat;
    
    okay = scandat(dat, pick(name), &newfmt, &newdat);
    if (!okay) {
        logu8err(name, deep);
        return;
    }
    
    //rewrite file if needed.
    if (newfmt.ch) {
        writef(name, newdat);
        logupdat(name, deep, newfmt);
    } else {
        loglodat(name, deep, newfmt);
    }
}

type handler::pick(const string &name) {
    return type::none;
}

} //namespace fmtcvt
