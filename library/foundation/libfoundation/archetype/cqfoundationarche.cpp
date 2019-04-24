#include "cqfoundationarche.h"

#if CQ_ON_OSX || CQ_ON_WINDOWS
//null implementation on macOS and Windows.
void cq_log_info (const char *file, int32_t line, const char *message) {}
void cq_log_error(const char *file, int32_t line, const char *message) {}
#endif
