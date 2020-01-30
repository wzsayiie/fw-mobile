#pragma once

#include "macro.hh"
#include "stdlibs.hh"

# if ON_WIN32()
#   define __findable_sym extern "C" __declspec(dllexport)
# else
#   define __findable_sym extern "C" __attribute((visibility("default")))
# endif

//looking for the symbol in the current executable.
void *find_sym(const string &name);
