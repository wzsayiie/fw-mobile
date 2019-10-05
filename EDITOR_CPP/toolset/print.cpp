#include "print.hh"

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
    char text[256] = "\0";
    if (format != nullptr) {
        vsnprintf(text, sizeof(text), format, args);
        printf("%s", text);
    }
    
    //count '\n' of this output.
    int len = (int)strlen(text);
    int count = 0;
    for (const char *it = text + len - 1; it >= text; --it) {
        if (*it == '\n') {
            count += 1;
        } else {
            break;
        }
    }
    if (count == len) {
        //all chars are '\n'
        _left_n += count;
    } else {
        _left_n = count;
    }
}

void _NEWLINE::i(_Printf_format_string_ const char *format, ...) {
    va_list args;
    va_start(args, format);
    print(1, format, args);
    va_end(args);
}

void _CLOSETO::i(_Printf_format_string_ const char *format, ...) {
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

_NEWLINE newline;
_CLOSETO closeto;

_CLOSETO spac(int lines) {
    print(lines + 1, nullptr, nullptr);
    return closeto;
}
