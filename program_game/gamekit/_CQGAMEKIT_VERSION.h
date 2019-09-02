#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQGAMEKIT_VERSION
#define _CQGAMEKIT_VERSION 1
#endif

#ifdef __cplusplus
#define _CQGAMEKIT_VERSION_NS       _CQ_MACRO_SPLICE(cqgamekit_, _CQGAMEKIT_VERSION)
#define _CQGAMEKIT_BEGIN_VERSION_NS inline namespace _CQGAMEKIT_VERSION_NS {
#define _CQGAMEKIT_END_VERSION_NS   }
#endif
