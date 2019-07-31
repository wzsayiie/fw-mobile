#include "cqstandalonearche.h"
#include "cqjnihelper.hh"

extern "C" JNIEXPORT void JNICALL Java_src_library_standalone_PORT_cqStandaloneUpdate
    (JNIEnv *, jclass)
{
    cq_standalone_update();
}

static std::vector<char *> newStringsFrom(JNIEnv *env, jobjectArray args) {

    if (args == nullptr) {
        return std::vector<char *>();
    }

    std::vector<char *> store;
    jsize count = env->GetArrayLength(args);
    for (jsize it = 0; it < count; ++it) {
        char *string = nullptr;

        auto javaObject = (jstring)env->GetObjectArrayElement(args, it);
        if (javaObject != nullptr) {
            std::string middle = cqJNIU8StringFromJNI(env, javaObject);
            string = new char[middle.size() + 1];
            strcpy(string, middle.c_str());
        } else {
            string = new char[1];
            *string = '\0';
        }

        store.push_back(string);
    }

    return store;
}

extern "C" JNIEXPORT void JNICALL Java_src_library_standalone_PORT_cqStandaloneLaunch
    (JNIEnv *env, jclass, jobjectArray args)
{
    std::vector<char *> store = newStringsFrom(env, args);

    auto argc = (int)store.size();
    auto argv = (const char **)store.data();
    cq_standalone_launch(argc, argv);

    for (char *it : store) {
        delete it;
    }
}
