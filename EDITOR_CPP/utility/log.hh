#pragma once

#include "std.hh"

# ifdef _MSC_VER
#   include <sal.h>
# endif

struct _LOG {
    
    const int _wanted_endlines;
    
    _LOG(int n) : _wanted_endlines(n) {}
    
  #if defined(__clang__)
    void log(const char *f, ...) __attribute__((__format__(__printf__, 2, 3)));
  #elif defined(_MSC_VER)
    void log(_Printf_format_string_ const char *f, ...);
  #else
    #error "unknown compiler"
  #endif
};

extern _LOG closeto;
extern _LOG newline;

_LOG &medi(int spacelines);
