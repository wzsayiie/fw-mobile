#include "cccsharp.hh"
#include "ccgeneral.hh"
#include "ccjava.hh"
#include "cclua.hh"
#include "ccobjcpp.hh"

void AppendJavas(vector<string> *sources) {
    sources->push_back("app_android/app/src/main/java");
    sources->push_back("library/bridge/java");
    sources->push_back("library/foundation/java");
}

void AppendObjcpps(vector<string> *sources) {
    sources->push_back("app_ios/App/Kits");
    sources->push_back("app_ios/App/Sources");
    sources->push_back("EDITOR_CPP");
    sources->push_back("library/bridge/Bridge");
    sources->push_back("library/bridge/libbridge");
    sources->push_back("library/extension/libextension/extension");
    sources->push_back("library/foundation/Foundation");
    sources->push_back("subsystem_cpp");
}

void AppendCSharps(vector<string> *sources) {
    sources->push_back("app_unity/Assets/Scripts");
    sources->push_back("EDITOR_CS");
};

void AppendLuas(vector<string> *sources) {
    sources->push_back("subsystem_lua");
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
