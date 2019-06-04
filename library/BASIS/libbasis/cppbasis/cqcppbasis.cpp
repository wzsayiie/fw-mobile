#include "cqcppbasis.hh"

//std extension:

std::string cqMakeString(const char *value) {
    return value ? value : "";
}

//class:

cqClassInfo *_cqObjectRoot::dynamicSuperclass() {
    return nullptr;
}

cqClassInfo *_cqObjectRoot::dynamicClass() {
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
    for (auto it = dynamicClass(); it; it = it->superclass) {
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
    return dynamicClass() == info;
}
