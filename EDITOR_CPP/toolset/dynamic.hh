#pragma once

#include "stdlibs.hh"

# ifdef _WIN32
#   define __findable_sym extern "C" __declspec(dllexport)
# else
#   define __findable_sym extern "C" __attribute((visibility("default")))
# endif

//looking for the symbol in the current executable.
void *findsym(const std::string &name);
