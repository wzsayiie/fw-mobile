#pragma once

#include "cqstdex.hh"

# ifdef __clang__
#   include <sys/cdefs.h>
# else
#   define __printflike(format, first_va)
# endif

struct _CONTINUE_LAST { void print(const char *format, ...) __printflike(2, 3); };
struct _START_NEWLINE { void print(const char *format, ...) __printflike(2, 3); };

extern _CONTINUE_LAST continue_last;
extern _START_NEWLINE start_newline;

_CONTINUE_LAST &space_line(int n);
