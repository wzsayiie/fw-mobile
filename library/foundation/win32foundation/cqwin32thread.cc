#include "cqwin32thread.hh"

static DWORD WINAPI CQThreadProcedure(LPVOID lpVoid)
{
    auto lpTask = (CQFUNC<VOID ()> *)lpVoid;
    (*lpTask)();
    delete lpTask;

    return 0;
}

VOID CQRunThread(CQFUNC<VOID ()> fnTask)
{
    if (fnTask != NULL)
    {
        CQFUNC<VOID ()> *lpTaskCopy = new CQFUNC<VOID ()>(fnTask);
        CreateThread(NULL, 0, CQThreadProcedure, lpTaskCopy, 0, NULL);
    }
}

VOID CQThreadSleepSeconds(FLOAT fSeconds)
{
    Sleep((DWORD)(1000 * fSeconds));
}
