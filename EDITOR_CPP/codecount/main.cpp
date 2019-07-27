#include "codecount.hh"

#define  S_CPP(x) x
#define   S_CS(x) x
#define S_JAVA(x) x
#define  S_JNI(x) x
#define  S_LUA(x) x
#define S_OBJC(x) x

bool codecount_launch = 0;
void codecount_main() {
    
    vector<string> dirs;
    
    S_JAVA(dirs.push_back("app_android/app/src/main/java"));
    S_OBJC(dirs.push_back("app_ios/App/Sources"));
    S_CS  (dirs.push_back("app_unity/Assets/Scripts"));

    S_CPP (dirs.push_back("EDITOR_CPP"));
    S_CS  (dirs.push_back("EDITOR_CS"));
    
    S_JNI (dirs.push_back("library/BASIS/android/cpp"));
    S_JAVA(dirs.push_back("library/BASIS/android/java"));
    S_CPP (dirs.push_back("library/BASIS/libbasis"));
    S_OBJC(dirs.push_back("library/BASIS/MacBasis"));
    
    S_CPP (dirs.push_back("library/ctool/libctool"));
    
    S_JNI (dirs.push_back("library/foundation/android/cpp"));
    S_JAVA(dirs.push_back("library/foundation/android/java"));
    S_CPP (dirs.push_back("library/foundation/libfoundation"));
    S_OBJC(dirs.push_back("library/foundation/MacFoundation"));
    S_CPP (dirs.push_back("library/foundation/win32foundation"));
    
    S_JNI (dirs.push_back("library/standalone/android/cpp"));
    S_JAVA(dirs.push_back("library/standalone/android/java"));
    S_CPP (dirs.push_back("library/standalone/libstandalone"));
    S_OBJC(dirs.push_back("library/standalone/MacStandalone"));

    S_JNI (dirs.push_back("library/subsystem/android/cpp"));
    S_JAVA(dirs.push_back("library/subsystem/android/java"));
    S_OBJC(dirs.push_back("library/subsystem/IOSSubsystem"));
    S_CPP (dirs.push_back("library/subsystem/libsubsystem"));

    S_JNI (dirs.push_back("program_basis/android/cpp"));
    S_JAVA(dirs.push_back("program_basis/android/java"));
    S_OBJC(dirs.push_back("program_basis/IOSBasisProgram"));
    S_CPP (dirs.push_back("program_basis/libbasisprogram"));

    S_JNI (dirs.push_back("program_cpp/android/cpp"));
    S_JAVA(dirs.push_back("program_cpp/android/java"));
    S_OBJC(dirs.push_back("program_cpp/IOSCPPProgram"));
    S_CPP (dirs.push_back("program_cpp/libcppprogram"));

    S_JNI (dirs.push_back("program_lua/android/cpp"));
    S_JAVA(dirs.push_back("program_lua/android/java"));
    S_OBJC(dirs.push_back("program_lua/IOSLuaProgram"));
    S_CPP (dirs.push_back("program_lua/libluaprogram"));
    
    codecount(dirs);
}
