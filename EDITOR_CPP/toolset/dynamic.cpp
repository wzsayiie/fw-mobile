#import "dynamic.hh"

# ifdef _WIN32
#   include <windows.h>
# else
#   include <dlfcn.h>
# endif

void *findsym(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }
    
#ifdef _WIN32
    HMODULE hExecutable = GetModuleHandleA(NULL);
    return (void *)GetProcAddress(hExecutable, name.c_str());
#else
    return dlsym(RTLD_DEFAULT, name.c_str());
#endif
}
