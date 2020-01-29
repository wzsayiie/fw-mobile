#include "codecount.hh"

//check if is utf8:

static
bool tidy_utf8(const vector<char> &bytes, vector<char> *out) {
    const char *ptr = bytes.data();
    const char *end = bytes.data() + bytes.size();
    
    //skip bom.
    if (start_with(UTF8_BOM, ptr, end)) {
        ptr += UTF8_BOM_SIZE;
    }
    
    while (ptr < end) {
        int size = check_utf8(ptr, end);
        
        //not utf8 char.
        if (size == 0) {
            return false;
        }
        
        if (size > 1) {
            out->insert(out->end(), ptr, ptr + size);
            ptr += size;
            continue;
        }
        
        //size == 1:
        if (start_with("\r\n", ptr, end)) {
            out->push_back('\n');
            ptr += 2;
        } else if (*ptr == '\r') {
            out->push_back('\n');
            ptr += 1;
        } else {
            out->push_back(*ptr);
            ptr += 1;
        }
    }
    return true;
}

//scan file content:

struct count_dat {
    
    int src_files   = 0;
    int code_lines  = 0;
    int empty_lines = 0;
    
    void operator+=(const count_dat &that) {
        src_files   += that.src_files  ;
        code_lines  += that.code_lines ;
        empty_lines += that.empty_lines;
    }
    
    int total_lines() const {
        return code_lines + empty_lines;
    }
};

static
void count(const vector<char> &utf8, count_dat *dat) {
    const char *ptr = utf8.data();
    const char *end = utf8.data() + utf8.size();
    
    bool coded = false;
    for (; ptr < end; ++ptr) {
        if (*ptr == '\n') {
            if (coded) {
                dat->code_lines += 1;
                coded = false;
            } else {
                dat->empty_lines += 1;
            }
        } else if (*ptr != ' ' && *ptr != '\t') {
            coded = true;
        }
    }
    if (coded) {
        dat->code_lines += 1;
    } else {
        dat->empty_lines += 1;
    }
}

//print:

static
const char *I(const string &name, int deep) {
    static char str[64];
    sprintf(str, "%*s%s", deep * 2, "", name.c_str());
    return str;
}

static void log_head (/*..................*/) {new_line.i("| sum|  code  |  empty  |");
/*........................................*/   new_line.i("|----|--------|---------|");}
static void log_f_err(const string &n, int d) {new_line.i("[      READ ERROR       ] %s" , I(n, d));}
static void log_not_u(const string &n, int d) {new_line.i("[       NOT UTF8        ] %s" , I(n, d));}
static void log_dir  (const string &n, int d) {new_line.i("[                       ] %s/", I(n, d));}

static
void log_dat(const string &name, int deep, count_dat dat) {
    int total = dat.total_lines();
    int code  = dat.code_lines;
    int empty = dat.empty_lines;
    
    new_line.i("[%4d"       , total);
    close_to.i(" %4d/%02d%%", code , code  * 100 / total);
    close_to.i(" %4d/%02d%%", empty, empty * 100 / total);
    close_to.i(" ] %s"      , I(name, deep));
}

static
const char *formated_num(int part, int total) {
    static char str[64];
    
    if (part >= 1000) {
        sprintf(str, "%4d,%03d", part / 1000, part % 1000);
    } else {
        sprintf(str, "%8d", part);
    }
    
    if (part < total) {
        sprintf(str + 8, " (%2d%%)", part * 100 / total);
    }
    
    return str;
}
    
static
void log_total(const count_dat &dat) {
    int files = dat.src_files;
    int total = dat.total_lines();
    int code  = dat.code_lines;
    int empty = dat.empty_lines;
    
    space(1).i("file count: %s", formated_num(files, 0));
    new_line.i("total line: %s", formated_num(total, 0));
    new_line.i("code line : %s", formated_num(code , total));
    new_line.i("empty line: %s", formated_num(empty, total));
}

//code count process:

static
void on_file(const string &name, int deep, count_dat *stage) {
    if (!is_src_file(name)) {
        return;
    }
    
    if (stage->src_files % 10 == 0) {
        log_head();
    }
    
    //read file.
    vector<char> bytes;
    bool okay = read_file(name, &bytes);
    if (!okay) {
        log_f_err(name, deep);
        stage->src_files += 1;
        return;
    }
    
    //check if is utf8.
    vector<char> utf8;
    okay = tidy_utf8(bytes, &utf8);
    if (!okay) {
        log_not_u(name, deep);
        stage->src_files += 1;
        return;
    }
    
    //count.
    count_dat one;
    one.src_files = 1;
    
    count(utf8, &one);
    log_dat(name, deep, one);
    
    *stage += one;
}

static
void for_dir(const string &name, int deep, count_dat *stage) {
    log_dir(name, deep);
}

void code_count(const vector<string> &paths) {
    
    count_dat global;
    
    for (const string &it : paths) {
        space(1).i("@ %s:", it.c_str());
        space(1);
        
        count_dat stage;
        bool okay = traverse(it, [&](traverse_item item) {
            if (item.file.is_dir) {
                for_dir(item.file.name, item.deep, &stage);
            } else {
                on_file(item.file.name, item.deep, &stage);
            }
        });
        
        if (okay) {
            log_total(stage);
            global += stage;
        }
    }
    
    if (paths.size() > 1) {
        space(1).i("total:");
        log_total(global);
    }
}
