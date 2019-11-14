#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQFOUNDATION_VERSION
#define _CQFOUNDATION_VERSION 1
#endif

#ifdef __cplusplus
#define _CQFOUNDATION_VERSION_NS       _CQ_MACRO_SPLICE(cqfoundation_, _CQFOUNDATION_VERSION)
#define _CQFOUNDATION_BEGIN_VERSION_NS inline namespace _CQFOUNDATION_VERSION_NS {
#define _CQFOUNDATION_END_VERSION_NS   }
#endif
