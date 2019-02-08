#include "clog.h"

#define IMPL(TAG)\
/**/    va_list args;\
/**/    va_start(args, format);\
/**/    \
/**/    const size_t size = 1024;\
/**/    char buffer[size];\
/**/    vsnprintf(buffer, size, format, args);\
/**/    printf("%s%s\n", TAG, buffer);\
/**/    \
/**/    va_end(args);\

void I(const char *format, ...) { IMPL(""       ) }
void W(const char *format, ...) { IMPL("ERROR: ") }
