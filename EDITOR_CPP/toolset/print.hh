#pragma once

#include "stdlibs.hh"

# ifdef __GNUC__
#   define _Printf_format_string_
#   ifndef __printflike
#   define __printflike(F, A) __attribute((format(printf, F, A)))
#   endif
# else
#   include <sal.h>
#   define __printflike(F, A)
# endif

struct _NEWLINE {
    void i(_Printf_format_string_ const char *format, ...) __printflike(2, 3);
};
struct _CLOSETO {
    void i(_Printf_format_string_ const char *format, ...) __printflike(2, 3);
};

// example:
//
//  newline.i(""); /* start a new line and print new text. */
//  spac(N).i(""); /* interval N blank lines from the last output and print new text. */
//  closeto.i(""); /* print new text close to the last output text. */
//

extern _NEWLINE newline;
extern _CLOSETO closeto;
extern _CLOSETO spac(int lines);

//equal to newline.i("").
void ii(_Printf_format_string_ const char *format, ...) __printflike(1, 2);
