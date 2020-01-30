#pragma once

//only POSIX and WIN32 platforms are supported.
# ifdef _WIN32
#   define ON_POSIX() 0
#   define ON_WIN32() 1
# else
#   define ON_POSIX() 1
#   define ON_WIN32() 0
# endif

# if ON_POSIX()
#   define IF_ON_POSIX(x) x
#   define IF_ON_WIN32(x)
# else
#   define IF_ON_POSIX(x)
#   define IF_ON_WIN32(x) x
# endif

//use these macro,
//prevent adding keyword "static" for each internal function.
#define BEGIN_INTERNAL_NS namespace {
#define END_INTERNAL_NS   }
