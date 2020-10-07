#pragma once

#include "_CQBASIS_VERSION.h"

//can define the version number by command line argument
#ifndef _CQCTOOL_VERSION
#define _CQCTOOL_VERSION 1
#endif

#ifdef __cplusplus
#define _CQCTOOL_VERSION_NS       _CQ_MACRO_SPLICE(cqctool_, _CQCTOOL_VERSION)
#define _CQCTOOL_BEGIN_VERSION_NS inline namespace _CQCTOOL_VERSION_NS {
#define _CQCTOOL_END_VERSION_NS   }
#endif
