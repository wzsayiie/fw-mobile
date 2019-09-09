#pragma once

#include "csgamekitbase.hh"

_CSGAMEKIT_BEGIN_VERSION_NS

cq_class(csScene, cqObject) {
    
    virtual void setName(const std::string &name);
    virtual std::string name();
};

_CSGAMEKIT_END_VERSION_NS
