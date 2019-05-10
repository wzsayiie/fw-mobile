#pragma once

#include "cqcbasis.h"
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <set>
#include <vector>

//interface and object

struct _cqRoot {
    virtual ~_cqRoot() = default;
};

#define cq_interface(SELF, SUPER) struct SELF : _cq_interface_middle<SELF, SUPER>

template<class SELF, class SUPER> struct _cq_interface_middle : SUPER {
    
    static_assert(sizeof(SUPER) == sizeof(void *),
        "interface shouldn't extend a class that contains data member");
    
    typedef std::shared_ptr<SELF> ref;
};

cq_interface(cqInterface, _cqRoot) {
};

#define cq_member(SELF)       struct SELF##_Data
#define cq_class(SELF, SUPER) struct SELF : _cq_class_middle<SELF, cq_member(SELF), SUPER>

template<class SELF, class DATA, class SUPER> struct _cq_class_middle : SUPER {

public:
    
    typedef std::shared_ptr<SELF> ref;
    
    template<class... A> static ref create(A... a) {
        return std::make_shared<SELF>(a...);
    }
    
protected:
    
    typedef SUPER super;
    
    std::shared_ptr<DATA> self;
    
    _cq_class_middle() : self(std::make_shared<DATA>()) {
    }
};

cq_class(cqObject, _cqRoot) {
    
    cqObject();
};

//containers

template<class T> struct _cqContainer {
    
    typedef std::shared_ptr<T> ref;
    
    template<class A> static ref create(A a) {
        return std::make_shared<T>(a);
    }
};

struct cqString        : _cqContainer<const std::string> {};
struct cqMutableString : _cqContainer<      std::string> {};

template<class T> struct cqVector        : _cqContainer<const std::vector<T>> {};
template<class T> struct cqMutableVector : _cqContainer<      std::vector<T>> {};
template<class T> struct cqSet           : _cqContainer<const std::set   <T>> {};
template<class T> struct cqMutableSet    : _cqContainer<      std::set   <T>> {};

template<class K, class V> struct cqMap        : _cqContainer<const std::map<K, V>> {};
template<class K, class V> struct cqMutableMap : _cqContainer<      std::map<K, V>> {};
