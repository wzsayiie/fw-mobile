#include "log.hh"

static int _left_endlines = 0;

static void print(int wanted_endlines, const char *text) {
    //add wanted space line
    if (_left_endlines < wanted_endlines) {
        for (int it = _left_endlines; it < wanted_endlines; ++it) {
            printf("\n");
        }
        _left_endlines = wanted_endlines;
    }
    
    if (text && *text) {
        printf("%s", text);
    } else {
        return;
    }
    
    //count '\n' of this output
    int length = (int)strlen(text);
    int count = 0;
    for (const char *it = text + length - 1; it >= text; --it) {
        if (*it == '\n') {
            count += 1;
        } else {
            break;
        }
    }
    if (count == length) {
        //all chars are '\n'
        _left_endlines += count;
    } else {
        _left_endlines = count;
    }
}

_LOG closeto(0);
_LOG newline(1);

void _LOG::log(const char *format, ...) {
    char buffer[256]; {
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);
    }
    print(_wanted_endlines, buffer);
}

_LOG &medi(int spacelines) {
    print(spacelines + 1, "");
    return closeto;
}
