#include "cqlog.hh"

static void print(const char *tag, const char *format, va_list args) {
    const size_t size = 256;
    char buffer[size];
    vsnprintf(buffer, size, format, args);
    printf("%s%s\n", tag, buffer);
}

void I(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print("", format, args);
    va_end(args);
}

void E(const char *format, ...) {
    va_list args;
    va_start(args, format);
    print("ERROR: ", format, args);
    va_end(args);
}
