#include "codecount.hh"

static bool supported(const string &name) {
    static const vector<string> options = {
        ".h" , ".hh" , ".cpp", ".cxx", ".cc",
        ".m" , ".mm" ,
        ".cs",".java", ".lua"
    };
    for (auto &it : options) {
        size_t n = name.size();
        size_t i = it.size();
        if (n > i && name.compare(n - i, i, it) == 0) {
            return true;
        }
    }
    return false;
}

static bool utf8tidy(const vector<char> &bytes, vector<char> *out) {
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    
    //skip BOM:
    if (ptr + 3 <= end && strncmp(ptr, utf8bom, 3) == 0) {
        ptr += 3;
    }
    
    while (ptr < end) {
        int size = utf8get(ptr, end);
        if (size == 1) {
            if (*ptr == '\r') {
                if (ptr + 1 < end && ptr[1] == '\n') {
                    out->push_back('\n');
                    ptr += 2;
                } else {
                    out->push_back('\n');
                    ptr += 1;
                }
            } else {
                out->push_back(*ptr);
                ptr += 1;
            }
        } else if (size > 1) {
            out->insert(out->end(), ptr, ptr + size);
            ptr += size;
        } else /* size == 0 */ {
            break;
        }
    }
    return ptr == end;
}

struct countdata {
    
    int fnumber = 0;
    int codeln  = 0;
    int emptyln = 0;
    
    void operator+=(const countdata &that) {
        fnumber += that.fnumber;
        codeln  += that.codeln ;
        emptyln += that.emptyln;
    }
    
    int sum() const {
        return codeln + emptyln;
    }
};

static const char *sumformat(int part, int sum) {
    static char str[64];
    
    if (part >= 1000) {sprintf(str, "%4d,%03d", part / 1000, part % 1000);}
    else /* < 1000 */ {sprintf(str, "%8d"     , part);}
    
    if (part < sum) {
        sprintf(str + 8, " (%2d%%)", part * 100 / sum);
    }
    
    return str;
}

static const char *f(const string &name, int deep) {
    static char str[64];
    sprintf(str, "%*s%s", deep * 2, "", name.c_str());
    return str;
}

static void logtitle(/* .... .... .... . */) {newline.i("| sum|  code  |  empty  |");
/* .... .... .... .... .... .... .... .. */   newline.i("|----|--------|---------|");}
static void logferr (const string &n, int d) {newline.i("[      READ ERROR       ] %s" , f(n, d));}
static void logu8err(const string &n, int d) {newline.i("[       NOT UTF8        ] %s" , f(n, d));}
static void logdir  (const string &n, int d) {newline.i("[                       ] %s/", f(n, d));}

static void logfile(const string &name, int deep, const countdata &i) {
    newline.i("[%4d"       , i.sum());
    closeto.i(" %4d/%02d%%", i.codeln , i.codeln  * 100 / i.sum());
    closeto.i(" %4d/%02d%%", i.emptyln, i.emptyln * 100 / i.sum());
    closeto.i(" ] %*s%s"   , deep * 2, "", name.c_str());
}

static void logsum(const countdata &d) {
    spac(1).i("file count: %s", sumformat(d.fnumber, 0));
    newline.i("total line: %s", sumformat(d.sum()  , 0));
    newline.i("code line : %s", sumformat(d.codeln , d.sum()));
    newline.i("empty line: %s", sumformat(d.emptyln, d.sum()));
}

static void count(const vector<char> &utf8, countdata *data) {
    const char *ptr = utf8.data();
    const char *end = utf8.data() + utf8.size();
    
    bool coded = false;
    for (; ptr < end; ++ptr) {
        if (*ptr == '\n') {
            if (coded) {
                data->codeln += 1;
                coded = false;
            } else {
                data->emptyln += 1;
            }
        } else if (*ptr != ' ' && *ptr != '\t') {
            coded = true;
        }
    }
    if (coded) {
        data->codeln += 1;
    } else {
        data->emptyln += 1;
    }
}

static void onfile(const string &name, int deep, countdata *stage) {
    if (!supported(name)) {
        return;
    }
    
    if (stage->fnumber % 10 == 0) {
        logtitle();
    }
    
    countdata one;
    one.fnumber = 1;
    do {
        vector<char> bytes;
        if (!readf(name, &bytes)) {
            logferr(name, deep);
            break;
        }
        vector<char> utf8;
        if (!utf8tidy(bytes, &utf8)) {
            logu8err(name, deep);
            break;
        }
        count(utf8, &one);
        logfile(name, deep, one);
    } while (0);
    *stage += one;
}

static void ondir(const string &name, int deep, countdata *stage) {
    logdir(name, deep);
}

void codecount(const vector<string> &paths) {
    
    countdata global;
    
    for (const string &it : paths) {
        spac(1).i("@ %s:", it.c_str());
        spac(1);
        
        countdata stage;
        scan(it, [&](const fitem &i, int deep) {
            if (i.isdir) {ondir (i.name, deep, &stage);}
            else /* - */ {onfile(i.name, deep, &stage);}
        });
        logsum(stage);
        
        global += stage;
    }
    if (paths.size() > 1) {
        spac(1).i("total:");
        logsum(global);
    }
}
