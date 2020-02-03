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

std::string cqJNIU8StringFromJNI(JNIEnv *env, jstring src) {
    if (env == nullptr) {
        return "";
    }
    if (src == nullptr) {
        return "";
    }

    auto middle = env->GetStringUTFChars(src, nullptr);
    if (cqJNIException(env)) {
        return "";
    }
    if (middle == nullptr) {
        return "";
    }
    std::string dst = middle;
    env->ReleaseStringUTFChars(src, middle);

    return dst;
}

jstring cqJNIStringFromU8(JNIEnv *env, const char *src) {
    if (env != nullptr && src != nullptr) {
        return env->NewStringUTF(src);
    } else {
        return nullptr;
    }
}

cqJNIByteArrayHelper::cqJNIByteArrayHelper(JNIEnv *env, jbyteArray data) {
    if (env != nullptr && data != nullptr) {
        _env    = env;
        _data   = data;
        _length = env->GetArrayLength(data);
        _bytes  = env->GetByteArrayElements(data, nullptr);
    } else {
        _env    = nullptr;
        _data   = nullptr;
        _length = 0;
        _bytes  = nullptr;
    }
}

cqJNIByteArrayHelper::~cqJNIByteArrayHelper() {
    if (_env != nullptr) {
        _env->ReleaseByteArrayElements(_data, _bytes, JNI_ABORT);
    }
}

const void *cqJNIByteArrayHelper::bytes() const {
    return (const void *)_bytes;
}

int32_t cqJNIByteArrayHelper::length() const {
    return (int32_t)_length;
}

void cqJNIByteArrayHelper::write(int32_t begin, const void *bytes, int32_t length) {
    if (_env != nullptr) {
        _env->SetByteArrayRegion(_data, (jsize)begin, (jsize)length, (const jbyte *)bytes);
    }
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
    value.l = cqJNIStringFromU8(_env, param);

    _signature.append("Ljava/lang/String;");
    _params.push_back(value);
    _objects.push_back(value.l);
}

std::string cqJNIStaticMethod::callString() {
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

    std::string ret = cqJNIU8StringFromJNI(_env, jString);
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
    return *_methodID != nullptr;
}
