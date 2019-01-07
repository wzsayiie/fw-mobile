#include "base/entry.h"
#include "base/filesystem.h"
#include "base/logging.h"

extern "C" void demo_objc();
void demo_cpp();

int main(int argc, const char *argv[]) {

    //simulated arguments
    change_dir("/Users/wujia/Local");
    
    const char *args[] = {
        "editor.exe",
        "unis"
    };
    argc = sizeof(args) / sizeof(*args);
    argv = args;
    
    //action
    auto entry_name = (argc >= 2 ? argv[1] : NULL);
    app_entry entry = get_entry(entry_name);
    if (entry != NULL) {
        set_args(argc, argv, 2);
        entry();
    } else {
        cinfo/"not set entry, execute demo function";
        set_args(argc, argv, 1);
        demo_objc();
        demo_cpp();
    }
}
