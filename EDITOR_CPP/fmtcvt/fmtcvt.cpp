#include "fmtcvt.hh"

namespace fmtcvt {

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
    newline.i(fmt.bom ?"[B ":"[- ");
    closeto.i(fmt.rn  ? "RN": "--");
    closeto.i(fmt.n   ? " N": " -");
    closeto.i(fmt.r   ? " R": " -");
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

void push(vector<char> *dat, const char *ptr, int len) {
    dat->insert(dat->end(), ptr, ptr + len);
}

void pushbom(fmtdat *fmt, vector<char> *dat) {fmt->bom = true; push(dat, utf8bom, 3);}
void pushrn (fmtdat *fmt, vector<char> *dat) {fmt->rn  = true; push(dat, "\r\n" , 2);}
void pushn  (fmtdat *fmt, vector<char> *dat) {fmt->n   = true; push(dat, "\n"   , 1);}
void pushr  (fmtdat *fmt, vector<char> *dat) {fmt->r   = true; push(dat, "\r"   , 1);}

bool scandat(const vector<char> &dat, want wt, fmtdat *newfmt, vector<char> *newdat) {
    *newfmt = fmtdat();
    newdat->clear();
    
    auto ptr = dat.data();
    auto end = dat.data() + dat.size();
    
    //process bom:
    if (startwith(utf8bom, ptr, end)) {
        /**/ if (wt == want::unix) {/*....................*/ newfmt->ch = true;}
        else if (wt == want::win ) {pushbom(newfmt, newdat);}
        else /*..wt == want::none*/{pushbom(newfmt, newdat);}
        ptr += 3;
    } else {
        /**/ if (wt == want::unix) {}
        else if (wt == want::win ) {pushbom(newfmt, newdat); newfmt->ch = true;}
        else /*..wt == want::none*/{}
    }
    
    //process content:
    while (ptr < end) {
        int size = utf8get(ptr, end);
        
        //not utf8 char.
        if (size == 0) {
            return false;
        }
        
        if (size > 1) {
            push(newdat, ptr, size);
            ptr += size;
            continue;
        }
        
        if (startwith("\r\n", ptr, end)) {
            /**/ if (wt == want::unix) {pushn (newfmt, newdat); newfmt->ch = true;}
            else if (wt == want::win ) {pushrn(newfmt, newdat);}
            else /*..wt == want::none*/{pushrn(newfmt, newdat);}
            ptr += 2;
        } else if (*ptr == '\n') {
            /**/ if (wt == want::unix) {pushn (newfmt, newdat);}
            else if (wt == want::win ) {pushrn(newfmt, newdat); newfmt->ch = true;}
            else /*..wt == want::none*/{pushn (newfmt, newdat);}
            ptr += 1;
        } else if (*ptr == '\r') {
            /**/ if (wt == want::unix) {pushn (newfmt, newdat); newfmt->ch = true;}
            else if (wt == want::win ) {pushrn(newfmt, newdat); newfmt->ch = true;}
            else /*..wt == want::none*/{pushr (newfmt, newdat);}
            ptr += 1;
        } else {
            push(newdat, ptr, size);
            ptr += size;
        }
    }
    
    return true;
}

//process:

void handler::proc(const vector<string> &paths) {
    int modified = 0;
    
    for (auto &it : paths) {
        spac(1).i("@ %s:", it.c_str());
        spac(1);
        
        modified += once(it);
    }
    
    spac(1).i("modified: %d files.", modified);
}

int handler::once(const string &path) {
    int modified = 0;
    
    scan(path, [&](const fitem &item, int deep) {
        if (item.isdir) {
            modified += adir(item.name, deep);
        } else {
            modified += afil(item.name, deep);
        }
    });
    
    return modified;
}

int handler::adir(const string &name, int deep) {
    logdir(name, deep);
    
    return 0;
}

int handler::afil(const string &name, int deep) {
    if (!codext(name)) {
        return 0;
    }
    
    //read file.
    vector<char> dat;
    bool okay = readf(name, &dat);
    if (!okay) {
        logferr(name, deep);
        return 0;
    }
    
    if (dat.empty()) {
        logempty(name, deep);
        return 0;
    }
    
    //scan file.
    fmtdat newfmt;
    vector<char> newdat;
    
    okay = scandat(dat, pick(name), &newfmt, &newdat);
    if (!okay) {
        logu8err(name, deep);
        return 0;
    }
    
    //rewrite file if needed.
    if (newfmt.ch) {
        writef(name, newdat);
        logupdat(name, deep, newfmt);
    } else {
        loglodat(name, deep, newfmt);
    }
    
    if (newfmt.ch) {
        return 1;
    } else {
        return 0;
    }
}

want handler::pick(const string &name) {
    return want::none;
}

} //namespace fmtcvt
