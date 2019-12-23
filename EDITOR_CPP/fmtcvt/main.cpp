#include "fmtcvt.hh"

__findable_sym void fmt_cvt_main(bool _true) {
    if (_true) return;
    
    vector<string> dirs;
    
    dirs.push_back("app_android/app/src/main/java");
    dirs.push_back("app_ios/App/Classes");
    dirs.push_back("app_unity/Assets");
    
    dirs.push_back("core_xapp/xapp");
    dirs.push_back("core_xgame/xgame");
    
    dirs.push_back("EDITOR_CPP");
    dirs.push_back("EDITOR_CS");
    
    dirs.push_back("library0/BASIS");
    dirs.push_back("library0/ctool");
    dirs.push_back("library0/foundation");
    dirs.push_back("library0/standalone");
    dirs.push_back("library0/subsystem");
    
    dirs.push_back("library1/appkit");
    dirs.push_back("library1/gamekit");
    dirs.push_back("library1/glkit");
    
    void fmt_cvt_process(const vector<string> &dirs);
    fmt_cvt_process(dirs);
}

struct this_fmt_cvt : fmt_cvt {
    want pick(const string &name) override {
        
        if (name.find("WIN32") != name.npos) {return want_win;}
        if (name.find("win32") != name.npos) {return want_win;}
        
        return want_unix;
    }
};

void fmt_cvt_process(const vector<string> &dirs) {
    auto cvt = new this_fmt_cvt;
    cvt->process(dirs);
}
