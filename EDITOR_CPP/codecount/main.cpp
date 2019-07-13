#include "cccsharp.hh"
#include "ccgeneral.hh"
#include "ccjava.hh"
#include "cclua.hh"
#include "ccobjcpp.hh"

void push_cpp(vector<string> *sources) {
    //editor
    sources->push_back("EDITOR_CPP");
    
    //library
    sources->push_back("library/BASIS/android/cpp");
    sources->push_back("library/BASIS/libbasis");
    
    sources->push_back("library/ctool/libctool");
    
    sources->push_back("library/foundation/android/cpp");
    sources->push_back("library/foundation/libfoundation");
    
    sources->push_back("library/standalone/android/cpp");
    sources->push_back("library/standalone/libstandalone");
    
    sources->push_back("library/subsystem/android/cpp");
    sources->push_back("library/subsystem/libsubsystem");
    
    //program
    sources->push_back("program_basis/android/cpp");
    sources->push_back("program_basis/libbasisprogram");
    
    sources->push_back("program_cpp/android/cpp");
    sources->push_back("program_cpp/libcppprogram");
    
    sources->push_back("program_lua/android/cpp");
    sources->push_back("program_lua/libluaprogram");
}

void push_cppcli(vector<string> *sources) {
    sources->push_back("library/foundation/windows");
}

void push_csharp(vector<string> *sources) {
    sources->push_back("app_unity/Assets/Scripts");
    sources->push_back("EDITOR_CS");
};

void push_java(vector<string> *sources) {
    //app
    sources->push_back("app_android/app/src/main/java");
    
    //library
    sources->push_back("library/BASIS/android/java");
    sources->push_back("library/foundation/android/java");
    sources->push_back("library/standalone/android/java");
    sources->push_back("library/subsystem/android/java");
    
    //program
    sources->push_back("program_basis/android/java");
    sources->push_back("program_cpp/android/java");
    sources->push_back("program_lua/android/java");
}

void push_lua(vector<string> *sources) {
    sources->push_back("program_lua/libluascript");
};

void push_objc(vector<string> *sources) {
    //app
    sources->push_back("app_ios/App/Sources");
    
    //library
    sources->push_back("library/BASIS/MacBasis");
    sources->push_back("library/foundation/MacFoundation");
    sources->push_back("library/standalone/MacStandalone");
    sources->push_back("library/subsystem/IOSSubsystem");
    
    //program
    sources->push_back("program_basis/IOSBasisProgram");
    sources->push_back("program_cpp/IOSCPPProgram");
    sources->push_back("program_lua/IOSLuaProgram");
}

bool codecount_launch = 0;
void codecount_main() {
    
    vector<string> sources;
    
//    push_cpp   (&sources);
//    push_cppcli(&sources);
//    push_csharp(&sources);
//    push_java  (&sources);
//    push_lua   (&sources);
//    push_objc  (&sources);
    
//    (new ccGeneral)->count(sources);
//    (new ccJava   )->count(sources);
//    (new ccObjcpp )->count(sources);
//    (new ccCSharp )->count(sources);
//    (new ccLua    )->count(sources);
}
