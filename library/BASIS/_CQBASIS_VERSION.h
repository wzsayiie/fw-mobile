#pragma once

#define _CQ_MACRO_SPLICE(  A, B) _CQ_MACRO_SPLICE_1(A, B)
#define _CQ_MACRO_SPLICE_1(A, B) _CQ_MACRO_SPLICE_2(A, B)
#define _CQ_MACRO_SPLICE_2(A, B) A##B

//can define the version number by command line argument
#ifndef _CQBASIS_VERSION
#define _CQBASIS_VERSION 1
#endif

#ifdef __cplusplus
#define _CQBASIS_VERSION_NS       _CQ_MACRO_SPLICE(cqbasis_, _CQBASIS_VERSION)
#define _CQBASIS_BEGIN_VERSION_NS inline namespace _CQBASIS_VERSION_NS {
#define _CQBASIS_END_VERSION_NS   }
#endif
