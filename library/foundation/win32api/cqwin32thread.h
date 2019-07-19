#pragma once

#include "cqwin32base.h"

CQ_C_LINK VOID CQRunThread(VOID (*fnTask)(LPVOID), LPVOID lpData);
CQ_C_LINK VOID CQThreadSleepSeconds(FLOAT fSeconds);
