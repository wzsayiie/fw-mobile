#include "print.hh"
#include <cstdarg>

static int _left_n = 0;

static void print(int wanted_n, const char *format, va_list args) {
    //add wanted space lines.
    if (_left_n < wanted_n) {
        for (int it = _left_n; it < wanted_n; ++it) {
            printf("\n");
        }
        _left_n = wanted_n;
    }
    
    //print.
    if (format != nullptr) {
        vsnprintf(BYTE_BUF, BYTE_BUF_SIZE, format, args);
        printf("%s", BYTE_BUF);
    } else {
        BYTE_BUF[0] = '\0';
    }
    
    //count '\n' of this output.
    int len = (int)strlen(BYTE_BUF);
    int count = 0;
    for (const char *it = BYTE_BUF + len - 1; it >= BYTE_BUF; --it) {
        if (*it == '\n') {
            count += 1;
        } else {
            break;
        }
    }
    if (count == len) {
        //all chars are '\n'.
        _left_n += count;
    } else {
        _left_n = count;
    }
}

void _NEW_LINE::i(_Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    print(1, format, args);
    va_end(args);
}

void _CLOSE_TO::i(_Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    print(0, format, args);
    va_end(args);
}

void ii(_Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    print(1, format, args);
    va_end(args);
}

_NEW_LINE new_line;
_CLOSE_TO close_to;

_CLOSE_TO space(int lines) {
    print(lines + 1, nullptr, nullptr);
    return close_to;
}
