#pragma once

#include "cqstdex.hh"

# ifdef __clang__
#   define CQ_PRINTF_LIKE(F, A) __attribute((format(printf, F, A)))
# else
#   define CQ_PRINTF_LIKE(F, A)
# endif

void I(const char *format, ...) CQ_PRINTF_LIKE(1, 2);
void E(const char *format, ...) CQ_PRINTF_LIKE(1, 2);
