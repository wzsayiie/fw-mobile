#pragma once

#include "cqgamekitbase.hh"

_CQGAMEKIT_BEGIN_VERSION_NS

cq_class(cqScene, cqObject) {
    
    virtual void setName(const std::string &name);
    virtual std::string name();
};

_CQGAMEKIT_END_VERSION_NS
