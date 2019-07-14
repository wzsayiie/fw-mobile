#include "codecount.hh"

void push_cpp(vector<string> *dirs) {
    //editor
    dirs->push_back("EDITOR_CPP");
    
    //library
    dirs->push_back("library/BASIS/android/cpp");
    dirs->push_back("library/BASIS/libbasis");
    
    dirs->push_back("library/ctool/libctool");
    
    dirs->push_back("library/foundation/android/cpp");
    dirs->push_back("library/foundation/libfoundation");
    
    dirs->push_back("library/standalone/android/cpp");
    dirs->push_back("library/standalone/libstandalone");
    
    dirs->push_back("library/subsystem/android/cpp");
    dirs->push_back("library/subsystem/libsubsystem");
    
    //program
    dirs->push_back("program_basis/android/cpp");
    dirs->push_back("program_basis/libbasisprogram");
    
    dirs->push_back("program_cpp/android/cpp");
    dirs->push_back("program_cpp/libcppprogram");
    
    dirs->push_back("program_lua/android/cpp");
    dirs->push_back("program_lua/libluaprogram");
}

void push_cppcli(vector<string> *dirs) {
    dirs->push_back("library/foundation/windows");
}

void push_csharp(vector<string> *dirs) {
    dirs->push_back("app_unity/Assets/Scripts");
    dirs->push_back("EDITOR_CS");
};

void push_java(vector<string> *dirs) {
    //app
    dirs->push_back("app_android/app/src/main/java");
    
    //library
    dirs->push_back("library/BASIS/android/java");
    dirs->push_back("library/foundation/android/java");
    dirs->push_back("library/standalone/android/java");
    dirs->push_back("library/subsystem/android/java");
    
    //program
    dirs->push_back("program_basis/android/java");
    dirs->push_back("program_cpp/android/java");
    dirs->push_back("program_lua/android/java");
}

void push_lua(vector<string> *dirs) {
    dirs->push_back("program_lua/libluascript");
};

void push_objc(vector<string> *dirs) {
    //app
    dirs->push_back("app_ios/App/Sources");
    
    //library
    dirs->push_back("library/BASIS/MacBasis");
    dirs->push_back("library/foundation/MacFoundation");
    dirs->push_back("library/standalone/MacStandalone");
    dirs->push_back("library/subsystem/IOSSubsystem");
    
    //program
    dirs->push_back("program_basis/IOSBasisProgram");
    dirs->push_back("program_cpp/IOSCPPProgram");
    dirs->push_back("program_lua/IOSLuaProgram");
}

bool codecount_launch = 0;
void codecount_main() {
    
    vector<string> dirs;
    
//    push_cpp   (&dirs);
//    push_cppcli(&dirs);
//    push_csharp(&dirs);
//    push_java  (&dirs);
//    push_lua   (&dirs);
//    push_objc  (&dirs);
    
    codecount(dirs);
}
