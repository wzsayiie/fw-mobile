#pragma once

#include "cqstdex.hh"

# ifdef __clang__
#   include <sys/cdefs.h>
# else
#   define __printflike(format, first_va)
# endif

# ifdef _MSC_VER
#   include <sal.h>
# else
#   define _Printf_format_string_
# endif

void I(_Printf_format_string_ const char *format, ...) __printflike(1, 2);
void E(_Printf_format_string_ const char *format, ...) __printflike(1, 2);
