#include "toolset.hh"

static void init() {

    string root = "fw-mobile";
    string path = __FILE__;

    size_t pos = path.find(root);
    if (pos != string::npos) {
        string dir = path.substr(0, pos + root.size());
        chdir(dir);
        closeto.i("work path: %s", dir.c_str());
    } else {
        closeto.i("failed to change the path");
    }
}

static void run(const char *name) {
    void *sym = findsym(name);
    if (sym == nullptr) {
        return;
    }
    
    auto func = (void (*)(bool))sym;
    func(true);
    
    spac(1);
}

int main() {
    init();
    
    run("codecount_main");
    run("fmtcvt_main");
    
    run("cpp_main");
    run("objcpp_main");
}
