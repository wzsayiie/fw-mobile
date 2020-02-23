#pragma once

#include "cqcppbasis.hh"
#include <jni.h>

JNIEnv *cqJNIGetEnv();

//if there was a java exception, remove it and return true.
bool cqJNIException(JNIEnv *env);

//if *prefer != null then return *prefer, else find the class and assign *prefer.
jclass cqJNIFindClass(jclass *prefer, JNIEnv *env, const char *name);

//if *prefer != null then return *prefer, else get the methodID and assign *prefer.
jmethodID cqJNIGetStatic(jmethodID *prefer, JNIEnv *env, jclass clazz, const char *name, const char *signature);

std::string cqJNIU8StringFromJNI(JNIEnv *env, jstring src);
jstring cqJNIStringFromU8(JNIEnv *env, const char *src); //return a local reference.

std::vector<uint8_t> cqJNIDataFromJNI(JNIEnv *env, jbyteArray src);
jbyteArray cqJNIByteArrayFromData(JNIEnv *env, const std::vector<uint8_t> &src); //return a local reference.

void *_cqJNIPtrFromJNI(jobject ptr);
jobject cqJNIJavaPtrFromPtr(const void *ptr);

template<class T> T cqJNIPtrFromJNI(jobject ptr) {
    return (T)_cqJNIPtrFromJNI(ptr);
}

template<class T> struct cqJNILocalRef {

    cqJNILocalRef(T ref) {
        _ref = ref;
    }

    ~cqJNILocalRef() {
        JNIEnv *env = cqJNIGetEnv();
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

struct cqJNIByteArrayHelper {

    cqJNIByteArrayHelper(JNIEnv *env, jbyteArray data);
    ~cqJNIByteArrayHelper();

    const void *bytes() const;
    int32_t length() const;

    void write(int32_t begin, const void *bytes, int32_t length);

private:
    JNIEnv *_env;
    jbyteArray _data;
    jbyte *_bytes;
    jsize _length;
};

struct cqJNIStaticMethod {

    cqJNIStaticMethod(jclass clazz, jmethodID *prefer, const char *name);
    ~cqJNIStaticMethod();

    cqJNIStaticMethod(const cqJNIStaticMethod &) = delete;
    void operator=(const cqJNIStaticMethod &) = delete;

    void push(bool    param) { push("Z", from(param)); }
    void push(int8_t  param) { push("B", from(param)); }
    void push(int16_t param) { push("S", from(param)); }
    void push(int32_t param) { push("I", from(param)); }
    void push(int64_t param) { push("J", from(param)); }
    void push(float   param) { push("F", from(param)); }
    void push(double  param) { push("D", from(param)); }

    void    callVoid  () { return call("V", &JNIEnv::CallStaticVoidMethodA   ); }
    bool    callBool  () { return call("Z", &JNIEnv::CallStaticBooleanMethodA); }
    int8_t  callInt8  () { return call("B", &JNIEnv::CallStaticByteMethodA   ); }
    int16_t callInt16 () { return call("S", &JNIEnv::CallStaticShortMethodA  ); }
    int32_t callInt32 () { return call("I", &JNIEnv::CallStaticIntMethodA    ); }
    int64_t callInt64 () { return call("J", &JNIEnv::CallStaticLongMethodA   ); }
    float   callFloat () { return call("F", &JNIEnv::CallStaticFloatMethodA  ); }
    double  callDouble() { return call("D", &JNIEnv::CallStaticDoubleMethodA ); }

    void push(const char *param);
    void push(const void *param);

    std::string callString();
    void *_callPtr();

    template<class T> T callPtr() {
        return (T)_callPtr();
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
