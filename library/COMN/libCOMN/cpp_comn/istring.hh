#pragma once

#include "icomponent.hh"
#include <string>

struct iString : iComponent {
    
    static const coGUID GUID = coGUIDMake(i,s,t,r,i,n,g,_,_,_,_,_,_);
    
    virtual void setUTF8(int64_t data, int32_t length);
    virtual int64_t utf8Data();
    virtual int32_t utf8Length();
    
    //native method
    void setString(const std::string &string);
    std::string string();
};

struct iStringCallee : iComponentCallee {
    int64_t called(coGUID method, iComponentCalleeParams params) override;
    iString *component();
};
