#include "_sym.hh"

#if ON_WIN32()

#include <windows.h>

void *find_sym(const string &name) {
    if (name.empty()) {
        return nullptr;
    }

    HMODULE hExecutable = GetModuleHandleA(NULL);
    return (void *)GetProcAddress(hExecutable, name.c_str());
}

#endif
