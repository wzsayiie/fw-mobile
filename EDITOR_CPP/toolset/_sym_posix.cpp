#ifdef __APPLE__

#include "_sym.hh"
#include <dlfcn.h>

void *find_sym(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    
    return dlsym(RTLD_DEFAULT, name.c_str());
}

#endif
