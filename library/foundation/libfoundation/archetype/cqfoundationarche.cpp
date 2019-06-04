#include "cqfoundationarche.h"

//null implementation on macOS and Windows.

#if CQ_ON_OSX || CQ_ON_WINDOWS

//log:
void cq_log_info (const char *, int32_t, const char *) {}
void cq_log_error(const char *, int32_t, const char *) {}

//file manager:
const char *cq_document_directory () {return "";}
const char *cq_caches_directory   () {return "";}
const char *cq_temporary_directory() {return "";}

const char *cq_append_path(const char *, const char *) {return "";}

bool cq_directory_exists(const char *)       {return false;}
bool cq_file_exists     (const char *)       {return false;}
bool cq_create_directory(const char *, bool) {return false;}
void cq_remove_path     (const char *)       {}

#endif
