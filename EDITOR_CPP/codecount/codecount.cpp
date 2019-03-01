#include "csharptraverser.hh"
#include "generaltraverser.hh"
#include "javatraverser.hh"
#include "luatraverser.hh"
#include "objcpptraverser.hh"

void CodeCountMain() {
    
    vector<string> javas = {
        "app_android/app/src/main/java",
        "library/bridge/java",
        "library/foundation/java",
    };
    vector<string> objcpps = {
        "app_ios/App/Kits",
        "app_ios/App/Sources",
        "EDITOR_CPP",
        "library/bridge/Bridge",
        "library/bridge/libbridge",
        "library/extension/libextension/extension",
        "library/foundation/Foundation",
        "subsystem_cpp",
    };
    vector<string> csharps = {
        "app_unity/Assets/Scripts",
        "EDITOR_CS",
    };
    vector<string> luas = {
        "subsystem_lua",
    };
    
    vector<string> generals;
    generals.insert(generals.end(), javas  .begin(), javas  .end());
    generals.insert(generals.end(), objcpps.begin(), objcpps.end());
    generals.insert(generals.end(), csharps.begin(), csharps.end());
    generals.insert(generals.end(), luas   .begin(), luas   .end());
    
    Traverser::count(generals, new GeneralTraverser);
//    Traverser::count(javas   , new JavaTraverser   );
//    Traverser::count(objcpps , new ObjcppTraverser );
//    Traverser::count(csharps , new CSharpTraverser );
//    Traverser::count(luas    , new LuaTraverser    );
}
