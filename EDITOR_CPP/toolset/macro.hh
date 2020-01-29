#pragma once

//use these macro,
//prevent adding keyword "static" for each internal function.
#define BEGIN_INTERNAL_NS namespace {
#define END_INTERNAL_NS   }

//only POSIX and WIN32 platforms are supported.
# ifdef _WIN32
#   define IF_ON_POSIX(x)
#   define IF_ON_WIN32(x) x
# else
#   define IF_ON_POSIX(x) x
#   define IF_ON_WIN32(x)
#endif
