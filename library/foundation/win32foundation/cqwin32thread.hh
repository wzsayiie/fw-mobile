#pragma once

#include "cqwin32base.hh"

VOID CQRunThread(CQFUNC<VOID ()> fnTask);
VOID CQThreadSleepSeconds(FLOAT fSeconds);
