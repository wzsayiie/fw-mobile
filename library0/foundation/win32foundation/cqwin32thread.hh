#pragma once

#include "cqwin32foundationbase.hh"

_CQFOUNDATION_BEGIN_VERSION_NS

VOID CQRunThread(CQFUNC<VOID ()> fnTask);
VOID CQThreadSleepSeconds(FLOAT fSeconds);

_CQFOUNDATION_END_VERSION_NS
