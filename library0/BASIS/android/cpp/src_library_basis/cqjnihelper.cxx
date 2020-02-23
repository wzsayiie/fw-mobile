#include "cqjnihelper.hh"
#include "CPtr.hh"

static JavaVM *sJavaVM = nullptr;
static int sJNIVersion = 0;

jint JNI_OnLoad(JavaVM *vm, void *) {
    sJavaVM = vm;
    sJNIVersion = JNI_VERSION_1_6;
    return sJNIVersion;
}

JNIEnv *cqJNIEnv::env() {
    if (sJavaVM != nullptr) {
        JNIEnv *env = nullptr;
        sJavaVM->GetEnv((void **)&env, sJNIVersion);
        return env;
    } else {
        return nullptr;
    }
}

bool cqJNIEnv::checkException(JNIEnv *env) {
    if (env != nullptr && env->ExceptionCheck()) {
        env->ExceptionDescribe();
        env->ExceptionClear();
        return true;
    } else {
        return false;
    }
}

jclass cqJNIEnv::findClass(jclass *prefer, JNIEnv *env, const char *name) {
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
        if (!cqJNIEnv::checkException(env)) {
            globalRef = (jclass)env->NewGlobalRef(localRef);
            cqJNIEnv::checkException(env);
            env->DeleteLocalRef(localRef);
            cqJNIEnv::checkException(env);
        }
    };

    if (prefer != nullptr) {
        *prefer = globalRef;
    }
    return globalRef;
}

jmethodID cqJNIEnv::staticMethod(jmethodID *prefer, JNIEnv *env, jclass clazz, const char *name, const char *signature) {
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
    if (cqJNIEnv::checkException(env)) {
        return nullptr;
    }

    if (prefer != nullptr) {
        *prefer = methodID;
    }
    return methodID;
}

std::string cqJNIType::string(JNIEnv *env, jstring src) {
    if (env == nullptr) {
        return "";
    }
    if (src == nullptr) {
        return "";
    }

    //NOTE: get the utf8 string.
    auto middle = env->GetStringUTFChars(src, nullptr);
    if (cqJNIEnv::checkException(env)) {
        return "";
    }
    if (middle == nullptr) {
        return "";
    }
    std::string dst = middle;
    env->ReleaseStringUTFChars(src, middle);

    return dst;
}

jstring cqJNIType::jniString(JNIEnv *env, const char *src) {
    if (env != nullptr && src != nullptr) {
        return env->NewStringUTF(src);
    } else {
        return nullptr;
    }
}

std::vector<uint8_t> cqJNIType::data(JNIEnv *env, jbyteArray src) {
    std::vector<uint8_t> dst;

    if (env && src) {
        jbyte *bytes = env->GetByteArrayElements(src, nullptr);
        jsize  len   = env->GetArrayLength(src);

        dst.insert(dst.end(), (uint8_t *)bytes, (uint8_t *)bytes + len);

        env->ReleaseByteArrayElements(src, bytes, JNI_ABORT);
    }

    return dst;
}

jbyteArray cqJNIType::jniData(JNIEnv *env, const std::vector<uint8_t> &src) {
    if (env == nullptr) {
        return nullptr;
    }

    auto bytes = (jbyte *)src.data();
    auto len = (jsize)src.size();

    jbyteArray dst = env->NewByteArray(len);
    env->SetByteArrayRegion(dst, 0, len, bytes);

    return dst;
}

void *cqJNIType::ptr_void(jobject ptr) {
    return CPtr_valueFromObject(ptr);
}

jobject cqJNIType::jniPtr(const void *ptr) {
    return CPtr_objectFromValue(ptr);
}

cqJNIStatic::cqJNIStatic(jclass clazz, jmethodID *prefer, const char *name) {

    _env       = cqJNIEnv::env();
    _clazz     = clazz;
    _methodID  = prefer ? prefer : &_METHOD_ID;
    _METHOD_ID = nullptr;
    _name      = name ? name : "";

    _signature.append("(");
}

cqJNIStatic::~cqJNIStatic() {
    if (_env == nullptr) {
        return;
    }

    for (jobject it : _objects) {
        _env->DeleteLocalRef(it);
    }
}

void cqJNIStatic::push(const char *param) {
    if (_env == nullptr) {
        return;
    }

    jvalue value;
    value.l = cqJNIType::jniString(_env, param);

    _signature.append("Ljava/lang/String;");
    _params.push_back(value);
    _objects.push_back(value.l);
}

void cqJNIStatic::push(const void *param) {
    if (_env == nullptr) {
        return;
    }

    jvalue value;
    value.l = cqJNIType::jniPtr(param);

    _signature.append("Lsrc/library/basis/CPtr;");
    _params.push_back(value);
    _objects.push_back(value.l);
}

std::string cqJNIStatic::callString() {
    if (_env == nullptr) {
        return "";
    }

    _signature.append(")Ljava/lang/String;");
    if (!check()) {
        return "";
    }

    cqJNILocal<jstring> string = (jstring)_env->CallStaticObjectMethodA(_clazz, *_methodID, _params.data());
    if (cqJNIEnv::checkException(_env)) {
        return "";
    }

    return cqJNIType::string(_env, string.get());
}

void *cqJNIStatic::callPtr_void() {
    if (_env == nullptr) {
        return nullptr;
    }

    _signature.append(")Lsrc/library/basis/CPtr;");
    if (!check()) {
        return nullptr;
    }

    cqJNILocal<jobject> ptr = _env->CallStaticObjectMethodA(_clazz, *_methodID, _params.data());
    if (cqJNIEnv::checkException(_env)) {
        return nullptr;
    }

    return cqJNIType::ptr_void(ptr.get());
}

void cqJNIStatic::push(const char *type, jvalue value) {
    _signature.append(type);
    _params.push_back(value);
}

bool cqJNIStatic::check() {
    if (_env == nullptr) {
        return false;
    }
    if (_clazz == nullptr) {
        return false;
    }
    cqJNIEnv::staticMethod(_methodID, _env, _clazz, _name.c_str(), _signature.c_str());
    return *_methodID != nullptr;
}
