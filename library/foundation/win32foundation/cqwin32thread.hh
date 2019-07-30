#pragma once

#include "cqwin32base.hh"

#include "CQWIN32FOUNDATION_NS.hh"
_CQWIN32FOUNDATION_BEGIN_NS

VOID CQRunThread(CQFUNC<VOID ()> fnTask);
VOID CQThreadSleepSeconds(FLOAT fSeconds);

_CQWIN32FOUNDATION_END_NS
