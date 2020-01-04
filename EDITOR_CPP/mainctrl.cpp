#include "toolset.hh"

static
void init() {

    string root = "fw-mobile";
    string path = __FILE__;

    size_t pos = path.find(root);
    if (pos != string::npos) {
        string dir = path.substr(0, pos + root.size());
        goto_dir(dir);
        close_to.i("work path: %s", dir.c_str());
    } else {
        close_to.i("failed to change the path");
    }
}

static
void run(const char *name) {
    void *sym = find_sym(name);
    if (sym == nullptr) {
        return;
    }
    
    auto func = (void (*)(bool))sym;
    func(true);
    
    space(1);
}

int main() {
    init();
    
    run("bridge_main");
    run("code_count_main");
    run("fmt_cvt_main");
    
    run("cpp_main");
    run("objcpp_main");
}
