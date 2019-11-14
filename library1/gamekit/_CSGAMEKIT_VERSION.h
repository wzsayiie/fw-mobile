#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CSGAMEKIT_VERSION
#define _CSGAMEKIT_VERSION 1
#endif

#ifdef __cplusplus
#define _CSGAMEKIT_VERSION_NS       _CQ_MACRO_SPLICE(csgamekit_, _CSGAMEKIT_VERSION)
#define _CSGAMEKIT_BEGIN_VERSION_NS inline namespace _CSGAMEKIT_VERSION_NS {
#define _CSGAMEKIT_END_VERSION_NS   }
#endif
