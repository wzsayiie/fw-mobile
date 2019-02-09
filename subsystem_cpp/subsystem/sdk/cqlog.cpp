#include "cqlog.hh"

# ifdef ANDROID
#    include <android/log.h>
# endif

void CLogI(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

#ifdef ANDROID
    __android_log_vprint(ANDROID_LOG_INFO, "zzz", format, args);
#else
    vprintf(format, args);
#endif

    va_end(args);
}

void CLogE(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

#ifdef ANDROID
    __android_log_vprint(ANDROID_LOG_ERROR, "zzz", format, args);
#else
    vprintf(format, args);
#endif

    va_end(args);
}
