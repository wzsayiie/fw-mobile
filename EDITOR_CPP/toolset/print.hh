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

struct _NEW_LINE {
    void i(_Printf_format_string_ const char *format, ...) __printflike(2, 3);
};
struct _CLOSE_TO {
    void i(_Printf_format_string_ const char *format, ...) __printflike(2, 3);
};

// example:
//
//  new_line.i(""); /* start a new line and print new text. */
//  space(N).i(""); /* interval N blank lines from the last output and print new text. */
//  close_to.i(""); /* print new text close to the last output text. */
//

extern _NEW_LINE new_line;
extern _CLOSE_TO close_to;
extern _CLOSE_TO space(int lines);

//equal to new_line.i("").
void ii(_Printf_format_string_ const char *format, ...) __printflike(1, 2);
