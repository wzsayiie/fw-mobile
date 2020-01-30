#include "_sym.hh"

#if ON_POSIX()

#include <dlfcn.h>

void *find_sym(const string &name) {
    if (name.empty()) {
        return nullptr;
    }
    
    return dlsym(RTLD_DEFAULT, name.c_str());
}

#endif
