#pragma once

#define _CQUIKIT_VERSION 0x010000

# ifdef __cplusplus
#   define _CQUIKIT_BEGIN_VERSION_NS      _CQUIKIT_BEGIN_VERSION_NS_1(_CQUIKIT_VERSION)
#   define _CQUIKIT_BEGIN_VERSION_NS_1(X) _CQUIKIT_BEGIN_VERSION_NS_2(X)
#   define _CQUIKIT_BEGIN_VERSION_NS_2(X) inline namespace cq_uikit_##X {
#   define _CQUIKIT_END_VERSION_NS        }
# endif
