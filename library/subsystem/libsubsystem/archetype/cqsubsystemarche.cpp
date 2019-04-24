#include "cqsubsystemarche.h"

#if CQ_ON_OSX || CQ_ON_WINDOWS
//null implementation on macOS and Windows.
bool cq_subsystem_start(const char *name) {return false;}
void cq_subsystem_stop (const char *name) {}
#endif
