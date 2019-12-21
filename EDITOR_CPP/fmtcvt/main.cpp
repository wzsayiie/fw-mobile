#include "fmtcvt.hh"

namespace fmtcvt {
    struct thishandler : handler {
        want pick(const string &name) override;
    };
}

__findable_sym void fmtcvt_main(bool _true) {
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
    
    (new fmtcvt::thishandler)->proc(dirs);
}

namespace fmtcvt {
    want thishandler::pick(const string &name) {
        return want::none;
    }
}
