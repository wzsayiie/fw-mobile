#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQUIKIT_VERSION
#define _CQUIKIT_VERSION 1
#endif

#ifdef __cplusplus
#define _CQUIKIT_VERSION_NS       _CQ_MACRO_SPLICE(cquikit_, _CQUIKIT_VERSION)
#define _CQUIKIT_BEGIN_VERSION_NS inline namespace _CQUIKIT_VERSION_NS {
#define _CQUIKIT_END_VERSION_NS   }
#endif
