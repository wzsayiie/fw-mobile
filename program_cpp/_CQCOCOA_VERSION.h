#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQCOCOA_VERSION
#define _CQCOCOA_VERSION 1
#endif

#ifdef __cplusplus
#define _CQCOCOA_VERSION_NS       _CQ_MACRO_SPLICE(cqcocoa_, _CQCOCOA_VERSION)
#define _CQCOCOA_BEGIN_VERSION_NS inline namespace _CQCOCOA_VERSION_NS {
#define _CQCOCOA_END_VERSION_NS   }
#endif
