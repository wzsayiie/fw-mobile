#ifdef __APPLE__

#include "dynamic.hh"
#include <dlfcn.h>

void *findsym(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    
    return dlsym(RTLD_DEFAULT, name.c_str());
}

#endif
