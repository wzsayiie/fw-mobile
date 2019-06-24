#include "cqcppbasis.hh"

//std extension:

std::string cqMakeString(const char *value) {
    return value ? value : "";
}

//class:

cqClassInfo *_cqObjectRoot::superclass(int) {
    return nullptr;
}

cqClassInfo *_cqObjectRoot::clazz(int) {
    return nullptr;
}

cqClassInfo *_cqObjectRoot::superclass() {
    return nullptr;
}

cqClassInfo *_cqObjectRoot::clazz() {
    return nullptr;
}

_cqObjectRoot::~_cqObjectRoot() {
}

cq_member(cqObject) {
};

cqObject::cqObject() {
}

bool cqObject::isKindOfClass(cqClassInfo *info) {
    if (info == nullptr) {
        return false;
    }
    for (auto it = clazz(); it; it = it->superclass) {
        if (it == info) {
            return true;
        }
    }
    return false;
}

bool cqObject::isMemberOfClass(cqClassInfo *info) {
    if (info == nullptr) {
        return false;
    }
    return clazz() == info;
}
