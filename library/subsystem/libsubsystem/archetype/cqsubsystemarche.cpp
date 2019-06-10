#include "cqsubsystemarche.h"

#if CQ_ON_OSX || CQ_ON_WINDOWS
//null implementation on macOS and Windows.
void cq_subsystem_start() {}
void cq_subsystem_stop () {}
#endif
