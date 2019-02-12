#include "cqlog.hh"
#include "cqfoundation.hh"

void CQLogI(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, 1024, format, args);
    CQLogger::info(buffer, file, line);
    
    va_end(args);
}

void CQLogE(const char *file, int line, const char *format, ...) {
    va_list args;
    va_start(args, format);

    char buffer[1024];
    vsnprintf(buffer, 1024, format, args);
    CQLogger::error(buffer, file, line);
    
    va_end(args);
}
