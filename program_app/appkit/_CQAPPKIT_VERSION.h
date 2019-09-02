#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQAPPKIT_VERSION
#define _CQAPPKIT_VERSION 1
#endif

#ifdef __cplusplus
#define _CQAPPKIT_VERSION_NS       _CQ_MACRO_SPLICE(cqappkit_, _CQAPPKIT_VERSION)
#define _CQAPPKIT_BEGIN_VERSION_NS inline namespace _CQAPPKIT_VERSION_NS {
#define _CQAPPKIT_END_VERSION_NS   }
#endif
