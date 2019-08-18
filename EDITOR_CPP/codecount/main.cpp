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
void app_ios    () { dirs(_OBJC, "app_ios/App/Sources"          ); }
void app_unity  () { dirs(_CS  , "app_unity/Assets/Scripts"     ); }

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

void program_basis() {
    dirs(_JNI , "program_basis/android/cpp"    );
    dirs(_JAVA, "program_basis/android/java"   );
    dirs(_OBJC, "program_basis/IOSBasisProgram");
    dirs(_CPP , "program_basis/libbasisprogram");
}

void program_cpp() {
    dirs(_JNI , "program_cpp/android/cpp"  );
    dirs(_JAVA, "program_cpp/android/java" );
    dirs(_OBJC, "program_cpp/IOSCPPProgram");
    dirs(_CPP , "program_cpp/libcppprogram");
}

void program_lua() {
    dirs(_JNI , "program_lua/android/cpp"  );
    dirs(_JAVA, "program_lua/android/java" );
    dirs(_OBJC, "program_lua/IOSLuaProgram");
    dirs(_CPP , "program_lua/libluaprogram");
    dirs(_LUA , "program_lua/libluascript" );
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
    
    program_basis();
    program_cpp();
    program_lua();
    
    codecount(dirs(false, nullptr));
}
