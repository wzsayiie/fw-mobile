#ifdef __APPLE__

#include "_sym.hh"
#include <dlfcn.h>

void *findsym(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    
    return dlsym(RTLD_DEFAULT, name.c_str());
}

#endif
