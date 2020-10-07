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

void cqJNIRefTransfer::deleteGlobalRef(jobject ref) {
    if (ref != nullptr) {
        cqJNIEnv::env()->DeleteGlobalRef(ref);
    }
}

void cqJNIRefTransfer::deleteLocalRef(jobject ref) {
    if (ref != nullptr) {
        cqJNIEnv::env()->DeleteLocalRef(ref);
    }
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

cqJNIRef<jstring> cqJNIType::jniStringAuto(JNIEnv *env, const char *src) {
    jstring ret = jniString(env, src);
    return cqJNIRefTransfer::local(ret);
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

cqJNIRef<jbyteArray> cqJNIType::jniDataAuto(JNIEnv *env, const std::vector<uint8_t> &src) {
    jbyteArray ret = jniData(env, src);
    return cqJNIRefTransfer::local(ret);
}

cqJNIRef<jbyteArray> cqJNIType::jniDataAuto(JNIEnv *env, const void *src, int32_t len) {
    jbyteArray ret = jniData(env, src, len);
    return cqJNIRefTransfer::local(ret);
}

void *cqJNIType::voidPtr(JNIEnv *env, jobject src) {
    return CPtr_valueFromObject(env, src);
}

cqJNIRef<jobject> cqJNIType::jniPtrAuto(JNIEnv *env, const void *src) {
    jobject ret = jniPtr(env, src);
    return cqJNIRefTransfer::local(ret);
}

jstring cqJNIType::jniString(JNIEnv *env, const char *src) {
    if (env != nullptr && src != nullptr) {
        return env->NewStringUTF(src);
    } else {
        return nullptr;
    }
}

jbyteArray cqJNIType::jniData(JNIEnv *env, const std::vector<uint8_t> &src) {
    auto ptr = (const void *)src.data();
    auto len = (int32_t)src.size();

    return jniData(env, ptr, len);
}

jbyteArray cqJNIType::jniData(JNIEnv *env, const void *src, int32_t len) {
    if (env == nullptr) {
        return nullptr;
    }
    if (!src || len <= 0) {
        return nullptr;
    }

    jbyteArray dst = env->NewByteArray((jsize)len);
    env->SetByteArrayRegion(dst, 0, len, (jbyte *)src);

    return dst;
}

jobject cqJNIType::jniPtr(JNIEnv *env, const void *src) {
    return CPtr_objectFromValue(env, src);
}

cqJNIStaticMethod::cqJNIStaticMethod(jclass clazz, jmethodID *prefer, const char *name) {

    _env       = cqJNIEnv::env();
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
    value.l = cqJNIType::jniString(_env, param);

    _signature.append("Ljava/lang/String;");
    _params.push_back(value);
    _objects.push_back(value.l);
}

void cqJNIStaticMethod::push(const std::string &param) {
    push(param.c_str());
}

void cqJNIStaticMethod::push(const void *param) {
    if (_env == nullptr) {
        return;
    }

    jvalue value;
    value.l = cqJNIType::jniPtr(_env, param);

    _signature.append("Lsrc/library/basis/CPtr;");
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

    jstring string = (jstring)_env->CallStaticObjectMethodA(_clazz, *_methodID, _params.data());
    if (cqJNIEnv::checkException(_env)) {
        return "";
    }

    std::string ret = cqJNIType::string(_env, string);
    _env->DeleteLocalRef(string);
    return ret;
}

void *cqJNIStaticMethod::callPtr() {
    if (_env == nullptr) {
        return nullptr;
    }

    _signature.append(")Lsrc/library/basis/CPtr;");
    if (!check()) {
        return nullptr;
    }

    jobject ptr = _env->CallStaticObjectMethodA(_clazz, *_methodID, _params.data());
    if (cqJNIEnv::checkException(_env)) {
        return nullptr;
    }

    void *ret = cqJNIType::voidPtr(_env, ptr);
    _env->DeleteLocalRef(ptr);
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
    cqJNIEnv::staticMethod(_methodID, _env, _clazz, _name.c_str(), _signature.c_str());
    return *_methodID != nullptr;
}
