#pragma once

#define _CQBASIS_VERSION 0x010000

# ifdef __cplusplus
#   define _CQBASIS_BEGIN_VERSION_NS      _CQBASIS_BEGIN_VERSION_NS_1(_CQBASIS_VERSION)
#   define _CQBASIS_BEGIN_VERSION_NS_1(X) _CQBASIS_BEGIN_VERSION_NS_2(X)
#   define _CQBASIS_BEGIN_VERSION_NS_2(X) inline namespace cq_basis_##X {
#   define _CQBASIS_END_VERSION_NS        }
# endif
