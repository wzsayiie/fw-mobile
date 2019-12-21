#ifdef _WIN32

#include "_sym.hh"
#include <windows.h>

void *findsym(const std::string &name) {
    if (name.empty()) {
        return nullptr;
    }

    HMODULE hExecutable = GetModuleHandleA(NULL);
    return (void *)GetProcAddress(hExecutable, name.c_str());
}

#endif
