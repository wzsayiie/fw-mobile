#include "cqjnihelper.hh"

static JavaVM *sJavaVM = nullptr;
static int sJNIVersion = 0;

jint JNI_OnLoad(JavaVM *vm, void *) {
    sJavaVM = vm;
    sJNIVersion = JNI_VERSION_1_6;
    return sJNIVersion;
}

JNIEnv *cqJNIGetEnv() {
    if (sJavaVM != nullptr) {
        JNIEnv *env = nullptr;
        sJavaVM->GetEnv((void **)&env, sJNIVersion);
        return env;
    } else {
        return nullptr;
    }
}

bool cqJNIException(JNIEnv *env) {
    if (env != nullptr && env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return true;
    } else {
        return false;
    }
}

jclass cqJNIFindClass(jclass *prefer, JNIEnv *env, const char *name) {
    if (prefer != nullptr && *prefer != nullptr) {
        return *prefer;
    }

    if (env == nullptr) {
        return nullptr;
    }
    if (name == nullptr) {
        return nullptr;
    }

    jclass globalRef = nullptr; {
        jclass localRef = env->FindClass(name);
        if (!cqJNIException(env)) {
            globalRef = (jclass)env->NewGlobalRef(localRef);
            cqJNIException(env);
            env->DeleteLocalRef(localRef);
            cqJNIException(env);
        }
    };

    if (prefer != nullptr) {
        *prefer = globalRef;
    }
    return globalRef;
}

jmethodID cqJNIGetStatic(jmethodID *prefer, JNIEnv *env, jclass clazz, const char *name, const char *signature) {
    if (prefer != nullptr && *prefer != nullptr) {
        return *prefer;
    }

    if (env == nullptr) {
        return nullptr;
    }
    if (clazz == nullptr) {
        return nullptr;
    }
    if (name == nullptr) {
        return nullptr;
    }
    if (signature == nullptr) {
        return nullptr;
    }

    jmethodID methodID = env->GetStaticMethodID(clazz, name, signature);
    if (cqJNIException(env)) {
        return nullptr;
    }

    if (prefer != nullptr) {
        *prefer = methodID;
    }
    return methodID;
}

string cqJNIFromJString(JNIEnv *env, jstring from) {
    if (env == nullptr) {
        return "";
    }
    if (from == nullptr) {
        return "";
    }

    auto middle = env->GetStringUTFChars(from, nullptr);
    if (cqJNIException(env)) {
        return "";
    }
    if (middle == nullptr) {
        return "";
    }
    string to = middle;
    env->ReleaseStringUTFChars(from, middle);

    return to;
}

cqJNIStaticMethod::cqJNIStaticMethod(jclass clazz, jmethodID *prefer, const char *name) {

    _env       = cqJNIGetEnv();
    _clazz     = clazz;
    _methodID  = prefer ? prefer : &_METHOD_ID;
    _METHOD_ID = nullptr;
    _name      = name ? name : "";

    _signature.append("(");
}

cqJNIStaticMethod::~cqJNIStaticMethod() {
    if (_env == nullptr) {
        return;
    }

    for (jobject it : _objects) {
        _env->DeleteLocalRef(it);
    }
}

void cqJNIStaticMethod::push(const char *param) {
    if (_env == nullptr) {
        return;
    }

    jvalue value;
    if (param != nullptr) {
        value.l = _env->NewStringUTF(param);
    } else {
        value.l = nullptr;
    }

    _signature.append("Ljava/lang/String;");
    _params.push_back(value);
    _objects.push_back(value.l);
}

string cqJNIStaticMethod::callString() {
    if (_env == nullptr) {
        return "";
    }

    _signature.append(")Ljava/lang/String;");
    if (!check()) {
        return "";
    }

    auto jString = (jstring)_env->CallStaticObjectMethodA(_clazz, *_methodID, _params.data());
    if (cqJNIException(_env)) {
        return "";
    }

    string ret = cqJNIFromJString(_env, jString);
    _env->DeleteLocalRef(jString);
    return ret;
}

void cqJNIStaticMethod::push(const char *type, jvalue value) {
    _signature.append(type);
    _params.push_back(value);
}

bool cqJNIStaticMethod::check() {
    if (_env == nullptr) {
        return false;
    }
    if (_clazz == nullptr) {
        return false;
    }
    cqJNIGetStatic(_methodID, _env, _clazz, _name.c_str(), _signature.c_str());
    if (*_methodID == nullptr) {
        return false;
    }

    return true;
}
