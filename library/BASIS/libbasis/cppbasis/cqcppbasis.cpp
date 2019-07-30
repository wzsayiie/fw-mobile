#include "cqcppbasis.hh"

//std extension:

std::string cqString::make(const char *value) {
    return value ? value : "";
}

bool cqString::empty(const char *value) {
    return value == nullptr || *value == '\0';
}

//class:

cqClass *_cqObjectRoot::getSuperclass() {
    return nullptr;
}

cqClass *_cqObjectRoot::getClass() {
    return nullptr;
}

cqClass *_cqObjectRoot::superclass() {
    return nullptr;
}

cqClass *_cqObjectRoot::clazz() {
    return nullptr;
}

_cqObjectRoot::~_cqObjectRoot() {
}

cq_member(cqObject) {
};

bool cqObject::isKindOfClass(cqClass *cls) {
    if (cls == nullptr) {
        return false;
    }
    for (auto it = clazz(); it; it = it->superclass) {
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
    return clazz() == cls;
}
