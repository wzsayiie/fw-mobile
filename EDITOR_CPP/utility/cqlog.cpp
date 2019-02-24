#include "cqlog.hh"

static int sNCountAtLast = 0;

static void output(int nCountRequired, const char *text) {
    
    //1 add required line-ending
    if (sNCountAtLast < nCountRequired) {
        for (int it = sNCountAtLast; it < nCountRequired; ++it) {
            printf("\n");
        }
        sNCountAtLast = nCountRequired;
    }
    
    if (*text != '\0') {
        printf("%s", text);
    } else {
        return;
    }
    
    //2 count '\n' of this output
    int length = (int)strlen(text);
    int nCount = 0;
    for (const char *it = text + length - 1; it >= text; --it) {
        if (*it == '\n') {
            ++nCount;
        } else {
            break;
        }
    }
    
    //3 record
    if (nCount == length) {
        //all chars are '\n'
        sNCountAtLast += nCount;
    } else {
        sNCountAtLast = nCount;
    }
}

static void output(int nCountRequired, const char *format, va_list args) {
    char buffer[256];
    vsnprintf(buffer, 256, format, args);
    output(nCountRequired, buffer);
}

_CONTINUE_LAST continue_last;
_START_NEWLINE start_newline;

void _CONTINUE_LAST::print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    output(0, format, args);
    va_end(args);
}

void _START_NEWLINE::print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    output(1, format, args);
    va_end(args);
}

_CONTINUE_LAST &space_line(int n) {
    output(n + 1, "");
    return continue_last;
}
