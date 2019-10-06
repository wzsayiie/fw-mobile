#include "codecount.hh"

__findable_sym void codecount_main(bool _true) {
    if (_true) return;
    
    vector<string> dirs;
    
    dirs.push_back("app_android/app/src/main/java");
    dirs.push_back("app_ios/App/Classes");
    dirs.push_back("app_unity/Assets");

    dirs.push_back("EDITOR_CPP");
    dirs.push_back("EDITOR_CS");

    dirs.push_back("library/BASIS");
    dirs.push_back("library/ctool");
    dirs.push_back("library/foundation");
    dirs.push_back("library/standalone");
    dirs.push_back("library/subsystem");

    dirs.push_back("program_app");
    dirs.push_back("program_game");
    dirs.push_back("program_gl");
    
    codecount(dirs);
}
