#include "cqcppbasis.hh"

//std extension:

std::string cqString::make(const char *value) {
    return value ? value : "";
}

bool cqString::empty(const char *value) {
    return value == nullptr || *value == '\0';
}

//class:

cqClass *_cqBaseObject::superclass() {
    return nullptr;
}

cqClass *_cqBaseObject::clazz() {
    return nullptr;
}

cqClass *_cqBaseObject::dynamicSuperclass() {
    return nullptr;
}

cqClass *_cqBaseObject::dynamicClass() {
    return nullptr;
}

_cqBaseObject::~_cqBaseObject() {
}

cq_member(cqObject) {
};

bool cqObject::isKindOfClass(cqClass *cls) {
    if (cls == nullptr) {
        return false;
    }
    for (auto it = dynamicClass(); it; it = it->superclass) {
        if (it == cls) {
            return true;
        }
    }
    return false;
}

bool cqObject::isMemberOfClass(cqClass *cls) {
    if (cls == nullptr) {
        return false;
    }
    return dynamicClass() == cls;
}
