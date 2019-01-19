#include "base/entry.h"
#include "base/filesystem.h"
#include "base/logging.h"

void demo_objcpp();
void demo_cpp();

string root_dir() {
    
    string root = "fw-mobile";
    string self = __FILE__;
    
    size_t pos = self.find(root);
    if (pos != string::npos) {
        return self.substr(0, pos + root.size());
    } else {
        return "";
    }
}

int main(int argc, const char *argv[]) {

    //simulated arguments
    const char *args[] = {
        "editor.exe"
    };
    argc = sizeof(args) / sizeof(*args);
    argv = args;
    
    //work dir
    string root = root_dir();
    if (!root.empty()) {
        change_dir(root);
        cinfo/"goto work dir:"/root;
    } else {
        cinfo/"current dir:"/get_work_dir();
    }

    //run command
    auto entry_name = (argc >= 2 ? argv[1] : "");
    app_entry entry = get_entry(entry_name);
    if (entry != NULL) {
        set_args(argc, argv, 2);
        entry();
    } else {
        cinfo/"not set entry, execute demo function";
        set_args(argc, argv, 1);
        demo_objcpp();
        demo_cpp();
    }
}
