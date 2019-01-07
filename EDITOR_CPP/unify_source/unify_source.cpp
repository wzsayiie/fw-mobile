#include "base/entry.h"
#include "base/logging.h"

//help ->

static void print_help() {
    
    const char *text =
    "\nfunction:"
    "\n  edit utf8 files' BOM and line-ending"
    "\n"
    "\nuse:"
    "\n  unity_source/unis --arguments path1 path2 ..."
    "\n"
    "\narguments:"
    "\n  --suffix specify files need handle, e.g. '--suffix .cpp --suffix makefile'"
    "\n           if not set, use default '.h/hpp/c/cpp/m/mm/java/cs/lua/md'"
    "\n  --view   view file states of BOM and line-ending (default)"
    "\n  --bom    add bom for files"
    "\n  --no-bom remove bom of files"
    "\n  --rn     edit line-ending to '\\r\\n'"
    "\n  --n      edit line-ending to '\\n'"
    "\n";
    
    cinfo/text;
}

//types ->

enum class edit_bom {
    retain, //retain current bom state
    add,    //add bom
    remove, //remove bom
};

enum class edit_eol {
    retain, //retain current line break state
    rn,     //change line-ending to \r\n
    n,      //change line-ending to \n
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
    if (out->action == action::view || out->action == action::edit) {
        if (out->paths.empty()) {
            return "no input paths";
        }
    }
    if (!out->paths.empty() && out->action == action::unkown) {
        out->action = action::view;
    }
    if (out->suffixes.empty()) {
        
        //default suffixes
        out->suffixes.insert(".h"   );
        out->suffixes.insert(".hpp" );
        out->suffixes.insert(".c"   );
        out->suffixes.insert(".cpp" );
        out->suffixes.insert(".m"   );
        out->suffixes.insert(".mm"  );
        out->suffixes.insert(".java");
        out->suffixes.insert(".cs"  );
        out->suffixes.insert(".lua" );
        out->suffixes.insert(".md"  );
    }
    
    return "";
}

//entry ->

//ENTR(unify_source, "unis")
void unify_source() {
    
    intent intent;
    string error = analyze_intent(&intent);
    if (!error.empty()) {
        cerr/error;
        return;
    }
    
    if (intent.action == action::edit) {
        
        //edit(intent.paths, it.options, it.suffixes);
        
    } else if (intent.action == action::view) {
        
        //view(intent.paths, it.suffixes);
        
    } else {
        
        print_help();
    }
}
