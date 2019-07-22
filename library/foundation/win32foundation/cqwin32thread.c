#include "cqwin32thread.h"

typedef struct _THREAD_PARAM {
    VOID (*fnTask)(LPVOID);
    LPVOID lpData;
} THREAD_PARAM, *LPTHREAD_PARAM;

static DWORD WINAPI CQThreadProcedure(LPTHREAD_PARAM lpParam)
{
    lpParam->fnTask(lpParam->lpData);
    free(lpParam);
    return 0;
}

VOID CQRunThread(VOID (*fnTask)(LPVOID), LPVOID lpData)
{
    if (fnTask != NULL)
    {
        LPTHREAD_PARAM lpParam = malloc(sizeof(THREAD_PARAM));
        lpParam->fnTask = fnTask;
        lpParam->lpData = lpData;
        CreateThread(NULL, 0, CQThreadProcedure, lpParam, 0, NULL);
    }
}

VOID CQThreadSleepSeconds(FLOAT fSeconds)
{
    Sleep((DWORD)(1000 * fSeconds));
}
