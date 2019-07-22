//this file is used to produce the opposite character(wide or narrow) version.

# ifdef UNICODE
#   undef  UNICODE
#   undef _UNICODE
# else
#   define  UNICODE 1
#   define _UNICODE 1
# endif

#include "cqwin32file.c"
#include "cqwin32log.c"
