#pragma once

#include "cqcppbasis.hh"
#include <jni.h>

#include "_CQBASIS_VERSION.h"
_CQBASIS_BEGIN_VERSION_NS

struct cqJNIEnv {

    //current thread JNI env.
    static JNIEnv *env();

    //if there was a java exception, remove it and return true.
    static bool checkException(JNIEnv *env);

    //if *prefer != null then return *prefer, else find the class and assign *prefer.
    static jclass findClass(jclass *prefer, JNIEnv *env, const char *name);

    //if *prefer != null then return *prefer, else get the methodID and assign *prefer.
    static jmethodID staticMethod(jmethodID *prefer, JNIEnv *env, jclass clazz, const char *name, const char *signature);
};

struct cqJNIType {

    static std::string string(JNIEnv *env, jstring src);
    static jstring jniString(JNIEnv *env, const char *src);

    static std::vector<uint8_t> data(JNIEnv *env, jbyteArray src);
    static jbyteArray jniData(JNIEnv *env, const std::vector<uint8_t> &src);

    static void *ptr_void(jobject ptr);
    static jobject jniPtr(const void *ptr);

    template<class T> static T ptr(jobject ptr) {
        return (T)ptr_void(ptr);
    }
};

template<class T> struct cqJNILocal {

    cqJNILocal(T ref) {
        _ref = ref;
    }

    ~cqJNILocal() {
        JNIEnv *env = cqJNIEnv::env();
        if (env && _ref) {
            env->DeleteLocalRef(_ref);
        }
    }

    T get() const {
        return _ref;
    }

private:
    T _ref;
};

struct cqJNIStatic {

    cqJNIStatic(jclass clazz, jmethodID *prefer, const char *name);
    ~cqJNIStatic();

    cqJNIStatic   (const cqJNIStatic &) = delete;
    void operator=(const cqJNIStatic &) = delete;
    void *operator new[](size_t) = delete;
    void *operator new  (size_t) = delete;

    void push(bool        param) { push("Z", from(param)); }
    void push(int8_t      param) { push("B", from(param)); }
    void push(int16_t     param) { push("S", from(param)); }
    void push(int32_t     param) { push("I", from(param)); }
    void push(int64_t     param) { push("J", from(param)); }
    void push(float       param) { push("F", from(param)); }
    void push(double      param) { push("D", from(param)); }
    void push(const char *param);
    void push(const void *param);

    //NOTE: function pointer can not match "const void *".
    template<class T> void push(T param) {
        push((const void *)param);
    }

    void        callVoid    () { return call("V", &JNIEnv::CallStaticVoidMethodA   ); }
    bool        callBool    () { return call("Z", &JNIEnv::CallStaticBooleanMethodA); }
    int8_t      callInt8    () { return call("B", &JNIEnv::CallStaticByteMethodA   ); }
    int16_t     callInt16   () { return call("S", &JNIEnv::CallStaticShortMethodA  ); }
    int32_t     callInt32   () { return call("I", &JNIEnv::CallStaticIntMethodA    ); }
    int64_t     callInt64   () { return call("J", &JNIEnv::CallStaticLongMethodA   ); }
    float       callFloat   () { return call("F", &JNIEnv::CallStaticFloatMethodA  ); }
    double      callDouble  () { return call("D", &JNIEnv::CallStaticDoubleMethodA ); }
    std::string callString  ();
    void *      callPtr_void();

    template<class T> T callPtr() {
        return (T)callPtr_void();
    }

private:

    jvalue from(bool    param) { jvalue v; v.z = (jboolean)param; return v; }
    jvalue from(int8_t  param) { jvalue v; v.b = (jbyte   )param; return v; }
    jvalue from(int16_t param) { jvalue v; v.s = (jshort  )param; return v; }
    jvalue from(int32_t param) { jvalue v; v.i = (jint    )param; return v; }
    jvalue from(int64_t param) { jvalue v; v.j = (jlong   )param; return v; }
    jvalue from(float   param) { jvalue v; v.f = (jfloat  )param; return v; }
    jvalue from(double  param) { jvalue v; v.d = (jdouble )param; return v; }

    void push(const char *type, jvalue value);

    bool check();

    template<class F> auto call(const char *s, F f)
        -> decltype((((JNIEnv *)nullptr)->*f)(nullptr, nullptr, nullptr))
    {
        _signature.append(")");
        _signature.append(s);

        if (check()) {
            return (_env->*f)(_clazz, *_methodID, _params.data());
        } else {
            return decltype((((JNIEnv *)nullptr)->*f)(nullptr, nullptr, nullptr))();
        }
    }

private:

    JNIEnv *_env;
    jclass _clazz;
    jmethodID *_methodID;
    jmethodID _METHOD_ID;

    std::string _name;
    std::string _signature;

    std::vector<jvalue> _params;
    std::vector<jobject> _objects;
};

_CQBASIS_END_VERSION_NS
