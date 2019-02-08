#pragma once

#include "cahead.h"

# ifdef __clang__
#   define C_PRINTF_LIKE(F, A) __attribute((format(printf, F, A)))
# else
#   define C_PRINTF_LIKE(F, A)
# endif

void I(const char *format, ...) C_PRINTF_LIKE(1, 2);
void W(const char *format, ...) C_PRINTF_LIKE(1, 2);
