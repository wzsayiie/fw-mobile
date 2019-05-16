#include "cccsharp.hh"
#include "ccgeneral.hh"
#include "ccjava.hh"
#include "cclua.hh"
#include "ccobjcpp.hh"

void AppendJavas(vector<string> *sources) {
    sources->push_back("app_android/app/src/main/java");
    sources->push_back("library/BASIS/android/java");
    sources->push_back("library/foundation/android/java");
    sources->push_back("library/subsystem/android/java");
}

void AppendObjcpps(vector<string> *sources) {
    sources->push_back("app_ios/App/Sources");
    
    sources->push_back("EDITOR_CPP");
    
    sources->push_back("library/BASIS/android/cpp");
    sources->push_back("library/BASIS/libbasis");
    
    sources->push_back("library/foundation/android/cpp");
    sources->push_back("library/foundation/IOSFoundation");
    sources->push_back("library/foundation/libfoundation");
    
    sources->push_back("library/subsystem/android/cpp");
    sources->push_back("library/subsystem/IOSSubsystem");
    sources->push_back("library/subsystem/libsubsystem");
    
    sources->push_back("program_cpp/android/cpp");
    sources->push_back("program_cpp/IOSCPPProgram");
    sources->push_back("program_cpp/libcppprogram");
    
    sources->push_back("program_lua/android/cpp");
    sources->push_back("program_lua/IOSLuaProgram");
    sources->push_back("program_lua/libluaprogram");
}

void AppendCSharps(vector<string> *sources) {
    sources->push_back("app_unity/Assets/Scripts");
    sources->push_back("EDITOR_CS");
};

void AppendLuas(vector<string> *sources) {
    sources->push_back("program_lua/libluascript");
};

bool ccMainEnabled = 0;
void ccMain() {
    
    vector<string> sources;
    
//    AppendJavas  (&sources);
//    AppendObjcpps(&sources);
//    AppendCSharps(&sources);
//    AppendLuas   (&sources);
    
//    (new ccGeneral)->count(sources);
//    (new ccJava   )->count(sources);
//    (new ccObjcpp )->count(sources);
//    (new ccCSharp )->count(sources);
//    (new ccLua    )->count(sources);
}
