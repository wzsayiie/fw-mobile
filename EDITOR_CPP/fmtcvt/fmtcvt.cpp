#include "fmtcvt.hh"

//print:

static
const char *indented(const string &name, int deep) {
    static char str[64];
    sprintf(str, "%*s%s", deep * 2, "", name.c_str());
    return str;
}

static void log_dir  (const string &n, int d) {new_line.i("|        | %s/", indented(n, d));}
static void log_f_err(const string &n, int d) {new_line.i("[FILE ERR] %s" , indented(n, d));}
static void log_empty(const string &n, int d) {new_line.i("[ EMPTY  ] %s" , indented(n, d));}
static void log_not_u(const string &n, int d) {new_line.i("[NOT UTF8] %s" , indented(n, d));}

struct fmt_info {
    bool ch  = false;
    bool bom = false;
    bool rn  = false;
    bool n   = false;
    bool r   = false;
};

static
void log_up_fmt(const string &name, int deep, fmt_info fmt) {
    new_line.i(fmt.bom ?"[B ":"[- ");
    close_to.i(fmt.rn  ? "RN": "--");
    close_to.i(fmt.n   ? " N": " -");
    close_to.i(fmt.r   ? " R": " -");
    close_to.i("] %s", indented(name, deep));
}

static
void log_lo_fmt(const string &name, int deep, fmt_info fmt) {
    new_line.i(fmt.bom ?"[b ":"[  ");
    close_to.i(fmt.rn  ? "rn": "  ");
    close_to.i(fmt.n   ? " n": "  ");
    close_to.i(fmt.r   ? " r": "  ");
    close_to.i("] %s", indented(name, deep));
}

//scan:

static
void push(vector<char> *dat, const char *ptr, int len) {
    dat->insert(dat->end(), ptr, ptr + len);
}

static void push_bom(fmt_info *f, vector<char> *d) {f->bom = true; push(d, UTF8_BOM, 3);}
static void push_rn (fmt_info *f, vector<char> *d) {f->rn  = true; push(d, "\r\n"  , 2);}
static void push_n  (fmt_info *f, vector<char> *d) {f->n   = true; push(d, "\n"    , 1);}
static void push_r  (fmt_info *f, vector<char> *d) {f->r   = true; push(d, "\r"    , 1);}

static
bool scan(const vector<char> &dat, fmt_cvt::want wt, fmt_info *fmt, vector<char> *out) {
    *fmt = fmt_info();
    out->clear();
    
    auto ptr = dat.data();
    auto end = dat.data() + dat.size();
    
    //process bom:
    if (start_with(UTF8_BOM, ptr, end)) {
        /**/ if (wt == fmt_cvt::want_unix) {/*...............*/ fmt->ch = true;}
        else if (wt == fmt_cvt::want_win ) {push_bom(fmt, out);}
        else /*.........................*/ {push_bom(fmt, out);}
        ptr += UTF8_BOM_SIZE;
    } else {
        /**/ if (wt == fmt_cvt::want_unix) {}
        else if (wt == fmt_cvt::want_win ) {push_bom(fmt, out); fmt->ch = true;}
        else /*.........................*/ {}
    }
    
    //process content:
    while (ptr < end) {
        int size = check_utf8(ptr, end);
        
        //not utf8 char.
        if (size == 0) {
            return false;
        }
        
        if (size > 1) {
            push(out, ptr, size);
            ptr += size;
            continue;
        }
        
        if (start_with("\r\n", ptr, end)) {
            /**/ if (wt == fmt_cvt::want_unix) {push_n (fmt, out); fmt->ch = true;}
            else if (wt == fmt_cvt::want_win ) {push_rn(fmt, out);}
            else /*.........................*/ {push_rn(fmt, out);}
            ptr += 2;
        } else if (*ptr == '\n') {
            /**/ if (wt == fmt_cvt::want_unix) {push_n (fmt, out);}
            else if (wt == fmt_cvt::want_win ) {push_rn(fmt, out); fmt->ch = true;}
            else /*.........................*/ {push_n (fmt, out);}
            ptr += 1;
        } else if (*ptr == '\r') {
            /**/ if (wt == fmt_cvt::want_unix) {push_n (fmt, out); fmt->ch = true;}
            else if (wt == fmt_cvt::want_win ) {push_rn(fmt, out); fmt->ch = true;}
            else /*.........................*/ {push_r (fmt, out);}
            ptr += 1;
        } else {
            push(out, ptr, size);
            ptr += size;
        }
    }
    
    return true;
}

//process:

void fmt_cvt::process(const vector<string> &paths) {
    int modified = 0;
    
    for (auto &it : paths) {
        space(1).i("@ %s:", it.c_str());
        space(1);
        
        modified += a_stage(it);
    }
    
    space(1).i("modified: %d files.", modified);
}

int fmt_cvt::a_stage(const string &path) {
    int modified = 0;
    
    traverse(path, [&](const file_info &file, int deep) {
        if (file.is_dir) {
            modified += for_dir(file.name, deep);
        } else {
            modified += on_file(file.name, deep);
        }
    });
    
    return modified;
}

int fmt_cvt::for_dir(const string &name, int deep) {
    log_dir(name, deep);
    
    return 0;
}

int fmt_cvt::on_file(const string &name, int deep) {
    if (!is_src_file(name)) {
        return 0;
    }
    
    //read file.
    vector<char> dat;
    bool okay = read_file(name, &dat);
    if (!okay) {
        log_f_err(name, deep);
        return 0;
    }
    
    if (dat.empty()) {
        log_empty(name, deep);
        return 0;
    }
    
    //scan file.
    fmt_info fmt;
    vector<char> out;
    
    okay = scan(dat, pick(name), &fmt, &out);
    if (!okay) {
        log_not_u(name, deep);
        return 0;
    }
    
    //rewrite file if needed.
    if (fmt.ch) {
        write_file(name, out);
        log_up_fmt(name, deep, fmt);
    } else {
        log_lo_fmt(name, deep, fmt);
    }
    
    if (fmt.ch) {
        return 1;
    } else {
        return 0;
    }
}

fmt_cvt::want fmt_cvt::pick(const string &name) {
    return want_none;
}
