#pragma once

#define _CQCTOOL_VERSION 0x100000

# ifdef __cplusplus
#   define _CQCTOOL_BEGIN_VERSION_NS      _CQCTOOL_BEGIN_VERSION_NS_1(_CQCTOOL_VERSION)
#   define _CQCTOOL_BEGIN_VERSION_NS_1(X) _CQCTOOL_BEGIN_VERSION_NS_2(X)
#   define _CQCTOOL_BEGIN_VERSION_NS_2(X) inline namespace cq_ctool_##X {
#   define _CQCTOOL_END_VERSION_NS        }
# endif
