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

template<class T> struct __cqJNIRefPointedStruct {
    using Type = typename std::remove_reference<decltype(*(T)nullptr)>::type;
};
template<class T> using cqJNIRef = std::shared_ptr<typename __cqJNIRefPointedStruct<T>::Type>;

struct cqJNIRefTransfer {

    static void deleteGlobalRef(jobject ref);
    static void deleteLocalRef (jobject ref);

    template<class T> static cqJNIRef<T> global(T ref) {return cqJNIRef<T>(ref, deleteGlobalRef);}
    template<class T> static cqJNIRef<T> local (T ref) {return cqJNIRef<T>(ref, deleteLocalRef );}
};

struct cqJNIType {

    //NOTE: the std::string retained is a utf8 encoded string.
    static std::string string(JNIEnv *env, jstring src);
    static cqJNIRef<jstring> jniStringAuto(JNIEnv *env, const char *src);

    static std::vector<uint8_t> data(JNIEnv *env, jbyteArray src);
    static cqJNIRef<jbyteArray> jniDataAuto(JNIEnv *env, const std::vector<uint8_t> &src);

    static void *voidPtr(JNIEnv *env, jobject ptr);
    static cqJNIRef<jobject> jniPtrAuto(JNIEnv *env, const void *ptr);

    template<class T> static T ptr(JNIEnv *env, jobject ptr) {
        return (T)voidPtr(env, ptr);
    }

    //these functions return local reference.
    static jstring    jniString(JNIEnv *env, const char *src);
    static jbyteArray jniData  (JNIEnv *env, const std::vector<uint8_t> &src);
    static jobject    jniPtr   (JNIEnv *env, const void *ptr);
};

struct cqJNIStaticMethod {

    cqJNIStaticMethod(jclass clazz, jmethodID *prefer, const char *name);
    ~cqJNIStaticMethod();

    cqJNIStaticMethod(const cqJNIStaticMethod &) = delete;
    void operator=   (const cqJNIStaticMethod &) = delete;
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

    void push() {
    }
    template<class A, class... B> void push(A a, B... b) {
        push(a);
        push(b...);
    }

    void        callVoid  () { return call("V", &JNIEnv::CallStaticVoidMethodA   ); }
    bool        callBool  () { return call("Z", &JNIEnv::CallStaticBooleanMethodA); }
    int8_t      callInt8  () { return call("B", &JNIEnv::CallStaticByteMethodA   ); }
    int16_t     callInt16 () { return call("S", &JNIEnv::CallStaticShortMethodA  ); }
    int32_t     callInt32 () { return call("I", &JNIEnv::CallStaticIntMethodA    ); }
    int64_t     callInt64 () { return call("J", &JNIEnv::CallStaticLongMethodA   ); }
    float       callFloat () { return call("F", &JNIEnv::CallStaticFloatMethodA  ); }
    double      callDouble() { return call("D", &JNIEnv::CallStaticDoubleMethodA ); }
    std::string callString();
    void *      callPtr   ();

    template<class T> T call() {
        return (T)callPtr(); //pointer type is default.
    }
    template<> void        call<void       >() {return callVoid  ();}
    template<> bool        call<bool       >() {return callBool  ();}
    template<> int8_t      call<int8_t     >() {return callInt8  ();}
    template<> int16_t     call<int16_t    >() {return callInt16 ();}
    template<> int32_t     call<int32_t    >() {return callInt32 ();}
    template<> int64_t     call<int64_t    >() {return callInt64 ();}
    template<> float       call<float      >() {return callFloat ();}
    template<> double      call<double     >() {return callDouble();}
    template<> std::string call<std::string>() {return callString();}

    template<class R, class... A> R fn(A... args) {
        push(args...);
        return call<R>();
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

#define CQ_JNI_CLASS(CLS, PATH)\
/**/    static jclass CLS() {\
/**/        static jclass cls = nullptr;\
/**/        if (cls == nullptr) {\
/**/            cqJNIEnv::findClass(&cls, cqJNIEnv::env(), PATH);\
/**/        }\
/**/        return cls;\
/**/    }

#define CQ_JNI_STATIC_METHOD(CLS, METHOD, NAME)\
/**/    static jmethodID __methodID = nullptr;\
/**/    cqJNIStaticMethod METHOD(CLS(), &__methodID, NAME)

_CQBASIS_END_VERSION_NS
