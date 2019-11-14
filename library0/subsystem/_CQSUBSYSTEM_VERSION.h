#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQSUBSYSTEM_VERSION
#define _CQSUBSYSTEM_VERSION 1
#endif

#ifdef __cplusplus
#define _CQSUBSYSTEM_VERSION_NS       _CQ_MACRO_SPLICE(cqsubsystem_, _CQSUBSYSTEM_VERSION)
#define _CQSUBSYSTEM_BEGIN_VERSION_NS inline namespace _CQSUBSYSTEM_VERSION_NS {
#define _CQSUBSYSTEM_END_VERSION_NS   }
#endif
