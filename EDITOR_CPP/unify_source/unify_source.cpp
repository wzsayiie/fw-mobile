#include "base/base.h"

//help ->

static void print_help() {
    
    const char *text =
    "function:"
    "\n  edit utf8 files' BOM and ending-of-line"
    "\n"
    "\nuse:"
    "\n  unity_source/unis --arguments path1 path2 ..."
    "\n"
    "\narguments:"
    "\n  --suffix specify files need handle, e.g. '--suffix .cpp --suffix makefile'"
    "\n           if not set, use default '.h/hpp/c/cpp/m/mm/java/cs/lua/md'"
    "\n  --view   view file states of BOM and ending-of-line (default)"
    "\n  --bom    add bom for files"
    "\n  --no-bom remove bom of files"
    "\n  --rn     edit ending-of-line to '\\r\\n'"
    "\n  --n      edit ending-of-line to '\\n'";
    
    cprint/text;
}

//types ->

enum class edit_bom {
    retain, //retain current bom state
    add,    //add bom
    remove, //remove bom
};

enum class edit_eol {
    retain, //retain current ending-of-line state
    rn,     //change ending-of-line to \r\n
    n,      //change ending-of-line to \n
};

struct edit_options {
    edit_bom bom = edit_bom::retain;
    edit_eol eol = edit_eol::retain;
};

enum class action {
    unkown, //unknown user intent
    view,   //view bom and ending-of-ling state of files
    edit,   //change bom and eol of files
};

struct intent {
    action         action = action::unkown;
    edit_options   options;
    vector<string> paths;
    set<string>    suffixes;
};

//file type ->

static set<string> default_suffixes() {
    set<string> suffixes;
    
    suffixes.insert(".h"   );
    suffixes.insert(".hpp" );
    suffixes.insert(".c"   );
    suffixes.insert(".cpp" );
    suffixes.insert(".m"   );
    suffixes.insert(".mm"  );
    suffixes.insert(".java");
    suffixes.insert(".cs"  );
    suffixes.insert(".lua" );
    suffixes.insert(".md"  );
    
    return suffixes;
}

static bool available_path(const string &path, const set<string> &suffixes) {
    for (const string &it : suffixes) {
        if (has_suffix(path, it)) {
            return true;
        }
    }
    return false;
}

//analyze argument ->

static string analyze_intent(intent *out) {
    
    vector<string> args = get_args();
    *out = intent();
    
    bool wait_suffix = false;
    for (const string &it : args) {
        
        if (wait_suffix) {
            
            out->suffixes.insert(it);
            wait_suffix = false;
            
        } else if (it == "--suffix") {
            
            wait_suffix = true;
            
        } else if (it == "--view") {
            
            if (out->action == action::edit) {
                return "'--view' only be used alone";
            }
            out->action = action::view;
            
        } else if (it == "--bom") {
            
            if (out->action == action::view) {
                return "'--view' only be used alone";
            }
            if (out->options.bom == edit_bom::remove) {
                return "'--bom' can't be used with '--no-bom'";
            }
            out->action = action::edit;
            out->options.bom = edit_bom::add;
            
        } else if (it == "--no-bom") {
            
            if (out->action == action::view) {
                return "'--view' only be used alone";
            }
            if (out->options.bom == edit_bom::add) {
                return "'--no-bom' can't be used with '--bom'";
            }
            out->action = action::edit;
            out->options.bom = edit_bom::remove;
            
        } else if (it == "--rn") {
            
            if (out->action == action::view) {
                return "'--view' only be used alone";
            }
            if (out->options.eol == edit_eol::n) {
                return "'--rn' can't be used with '--n'";
            }
            out->action = action::edit;
            out->options.eol = edit_eol::rn;
            
        } else if (it == "--n") {
            
            if (out->action == action::view) {
                return "'--view' only be used alone";
            }
            if (out->options.eol == edit_eol::rn) {
                return "'--n' can't be used with '--rn'";
            }
            out->action = action::edit;
            out->options.eol = edit_eol::n;
            
        } else if (it.size() >= 1 && it[0] == '-') {
            
            return "unsupported argument '" + it + "'";
            
        } else if (it != "") {
            
            out->paths.push_back(it);
        }
    }
    
    //default behaviour
    if (out->action != action::unkown && out->paths.empty()) {
        return "no input file";
    }
    if (!out->paths.empty() && out->action == action::unkown) {
        out->action = action::view;
    }
    
    if (out->suffixes.empty()) {
        out->suffixes = default_suffixes();
    }
    
    return "";
}

//print ->

static void line(const char *flag, const string &name, int indent, bool is_dir) {
    const size_t size = 80;
    char buffer[size];
    snprintf(buffer, size, "%s %*s%s%s", flag, indent * 2, "", name.c_str(), (is_dir ? "/" : ""));
    cprint/buffer;
}

static void line_null    (const string &n, int i, bool d = false) { line("[        ]", n, i, d); }
static void line_lost    (const string &n, int i, bool d = false) { line("[  lost  ]", n, i, d); }
static void line_rejected(const string &n, int i, bool d = false) { line("[rejected]", n, i, d); }
static void line_empty   (const string &n, int i, bool d = false) { line("[ empty  ]", n, i, d); }
static void line_read_err(const string &n, int i, bool d = false) { line("[read err]", n, i, d); }
static void line_writ_err(const string &n, int i, bool d = false) { line("[writ err]", n, i, d); }
static void line_edited  (const string &n, int i, bool d = false) { line("[ edited ]", n, i, d); }

static void line_state(const string &name, int indent, utf8_finfo info) {
    const size_t size = 80;
    char buffer[size];
    snprintf(buffer, size, "[%s %s %s %s] %*s%s",
        info.has_bom ? "B"  : "-",
        info.has_rn  ? "RN" : "--",
        info.has_n   ? "N"  : "-",
        info.has_r   ? "R"  : "-",
        indent * 2, "",
        name.c_str()
    );
    cprint/buffer;
}

//edit files ->

static void edit(const string &path, int indent, edit_options options, const set<string> &suffixes) {
    
    string name = base_name(path);
    bool is_dir = false;
    bool exist = exist_path(path, &is_dir);
    
    if (!exist) {
        
        line_lost(name, indent);
        
    } else if (is_dir) {
        
        vector<string> contents = contents_of_dir(path);
        if (contents.empty()) {
            line_null(name, indent, true);
            return;
        }
        if (!change_dir(path)) {
            line_rejected(name, indent, true);
            return;
        }
        
        line_null(name, indent, true);
        for (const auto &it : contents) {
            edit(it, indent + 1, options, suffixes);
        }
        change_dir("..");
        
    } else {
        
        if (!available_path(path, suffixes)) {
            line_null(name, indent);
            return;
        }
        
        utf8_finfo finfo;
        if (!utf8_fread(path, &finfo)) {
            line_read_err(name, indent);
            return;
        }
        if (finfo.content.empty() && !finfo.has_bom) {
            line_empty(name, indent);
            return;
        }
        
        bool edited = false;
        
        if (options.bom == edit_bom::add && !finfo.has_bom) {
            finfo.has_bom = true;
            edited = true;
        } else if (options.bom == edit_bom::remove && finfo.has_bom) {
            finfo.has_bom = false;
            edited = true;
        }
        
        if (options.eol == edit_eol::rn && (finfo.has_r || finfo.has_n)) {
            finfo.has_rn = true;
            finfo.has_r = false;
            finfo.has_n = false;
            edited = true;
        } else if (options.eol == edit_eol::n && (finfo.has_rn || finfo.has_r)) {
            finfo.has_rn = false;
            finfo.has_r = false;
            finfo.has_n = true;
            edited = true;
        }
        
        if (edited) {
            if (utf8_fwrite(path, finfo)) {
                line_edited(name, indent);
            } else {
                line_writ_err(name, indent);
            }
        } else {
            line_null(name, indent);
        }
    }
}

static void edit(const vector<string> &paths, edit_options options, const set<string> &suffixes) {
    for (const auto &it : paths) {
        edit(it, 0, options, suffixes);
    }
}

//view files ->

static void view(const string &path, int indent, const set<string> &suffixes) {
    
    string name = base_name(path);
    bool is_dir = false;
    bool exist = exist_path(path, &is_dir);
    
    if (!exist) {
        
        line_lost(name, indent);
        
    } else if (is_dir) {
        
        vector<string> contents = contents_of_dir(path);
        if (contents.empty()) {
            line_null(name, indent, true);
            return;
        }
        if (!change_dir(path)) {
            line_rejected(name, indent, true);
            return;
        }
        
        line_null(name, indent, true);
        for (const auto &it : contents) {
            view(it, indent + 1, suffixes);
        }
        change_dir("..");
        
    } else {
        
        if (!available_path(path, suffixes)) {
            line_null(name, indent);
            return;
        }
        
        utf8_finfo finfo;
        if (!utf8_fread(path, &finfo)) {
            line_read_err(name, indent);
            return;
        }
        
        if (finfo.content.empty() && !finfo.has_bom) {
            line_empty(name, indent);
        } else {
            line_state(name, indent, finfo);
        }
    }
}

static void view(const vector<string> &paths, const set<string> &suffixes) {
    for (const auto &it : paths) {
        view(it, 0, suffixes);
    }
}

//entry ->

//ENTR(unify_source, "unis")
void unify_source() {
    
    intent intent;
    string error = analyze_intent(&intent);
    if (!error.empty()) {
        cprint/error;
        return;
    }

    if (intent.action == action::edit) {
        edit(intent.paths, intent.options, intent.suffixes);
    } else if (intent.action == action::view) {
        view(intent.paths, intent.suffixes);
    } else {
        print_help();
    }
}
