#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQGLKIT_VERSION
#define _CQGLKIT_VERSION 1
#endif

#ifdef __cplusplus
#define _CQGLKIT_VERSION_NS       _CQ_MACRO_SPLICE(cqglkit_, _CQGLKIT_VERSION)
#define _CQGLKIT_BEGIN_VERSION_NS inline namespace _CQGLKIT_VERSION_NS {
#define _CQGLKIT_END_VERSION_NS   }
#endif
