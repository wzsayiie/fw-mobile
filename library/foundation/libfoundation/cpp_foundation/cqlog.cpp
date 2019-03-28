#include "cqlog.hh"
#include "cqlog_p.h"
#include <cstdarg>
#include <cstdio>

void cqLogInfo(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_info(file, line, message);
}

void cqLogError(const char *file, int line, const char *format, ...) {
    char message[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(message, sizeof(message), format, args);
        va_end(args);
    }
    cq_log_error(file, line, message);
}
