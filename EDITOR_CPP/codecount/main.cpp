#include "codecount.hh"

bool _CPP  = false;
bool _CS   = false;
bool _JAVA = false;
bool _JNI  = false;
bool _LUA  = false;
bool _OBJC = false;

const vector<string> &dirs(bool push, const char *item) {
    static vector<string> vec;
    if (push && item != nullptr) {
        vec.push_back(item);
    }
    return vec;
}

void app_android() { dirs(_JAVA, "app_android/app/src/main/java"); }
void app_ios    () { dirs(_OBJC, "app_ios/App/Classes"          ); }
void app_unity  () { dirs(_CS  , "app_unity/Assets/Script"      ); }

void EDITOR_CPP() { dirs(_CPP, "EDITOR_CPP"); }
void EDITOR_CS () { dirs(_CS , "EDITOR_CS" ); }

void library_BASIS() {
    dirs(_JNI , "library/BASIS/android/cpp" );
    dirs(_JAVA, "library/BASIS/android/java");
    dirs(_CPP , "library/BASIS/libbasis"    );
    dirs(_OBJC, "library/BASIS/MacBasis"    );
}

void library_ctool() {
    dirs(_CPP, "library/ctool/libctool");
}

void library_foundation() {
    dirs(_JNI , "library/foundation/android/cpp"    );
    dirs(_JAVA, "library/foundation/android/java"   );
    dirs(_CPP , "library/foundation/libfoundation"  );
    dirs(_OBJC, "library/foundation/MacFoundation"  );
    dirs(_CPP , "library/foundation/win32foundation");
}

void library_standalone() {
    dirs(_JNI , "library/standalone/android/cpp"  );
    dirs(_JAVA, "library/standalone/android/java" );
    dirs(_CPP , "library/standalone/libstandalone");
    dirs(_OBJC, "library/standalone/MacStandalone");
}

void library_subsystem() {
    dirs(_JNI , "library/subsystem/android/cpp" );
    dirs(_JAVA, "library/subsystem/android/java");
    dirs(_OBJC, "library/subsystem/IOSSubsystem");
    dirs(_CPP , "library/subsystem/libsubsystem");
}

void program_app() {
    dirs(_JNI , "program_app/appkit/android/cpp" );
    dirs(_JAVA, "program_app/appkit/android/java");
    dirs(_OBJC, "program_app/appkit/IOSAppKit"   );
    dirs(_CPP , "program_app/appkit/libappkit"   );
    dirs(_CPP , "program_app/userapp"            );
}

void program_game() {
    dirs(_JNI , "program_game/gamekit/android/cpp" );
    dirs(_JAVA, "program_game/gamekit/android/java");
    dirs(_OBJC, "program_game/gamekit/IOSGameKit"  );
    dirs(_CPP , "program_game/gamekit/libgamekit"  );
    dirs(_CPP , "program_game/usergame"            );
    dirs(_LUA , "program_game/userscript"          );
}

void program_gl() {
    dirs(_JNI , "program_gl/glkit/android/cpp"  );
    dirs(_JAVA, "program_gl/glkit/android/java" );
    dirs(_OBJC, "program_gl/glkit/IOSGLKit"     );
    dirs(_CPP , "program_gl/glkit/libglkit"     );
}

bool codecount_launch = 0;
void codecount_main() {
    
    _CPP  = true;
    _CS   = true;
    _JAVA = true;
    _JNI  = true;
    _LUA  = true;
    _OBJC = true;
    
    app_android();
    app_ios();
    app_unity();

    EDITOR_CPP();
    EDITOR_CS ();
    
    library_BASIS();
    library_ctool();
    library_foundation();
    library_standalone();
    library_subsystem();
    
    program_app();
    program_game();
    program_gl();
    
    codecount(dirs(false, nullptr));
}
