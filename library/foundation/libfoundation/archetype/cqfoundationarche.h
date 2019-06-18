#pragma once

#include "cqcbasis.h"

//log:

CQ_C_LINK void cq_log_info (const char *file, int32_t line, const char *message);
CQ_C_LINK void cq_log_error(const char *file, int32_t line, const char *message);

//file manager:

CQ_C_LINK const char *cq_document_directory(void);
CQ_C_LINK const char *cq_caches_directory(void);
CQ_C_LINK const char *cq_temporary_directory(void);
CQ_C_LINK const char *cq_append_path(const char *parent, const char *child);
CQ_C_LINK bool cq_directory_exists(const char *path);
CQ_C_LINK bool cq_file_exists(const char *path);
CQ_C_LINK bool cq_create_directory(const char *path, bool intermediate);
CQ_C_LINK void cq_remove_path(const char *path);

//thread:

CQ_C_LINK void cq_thread_run(void (*task)(void *), void *data);
CQ_C_LINK void cq_thread_sleep(float seconds);

//network:

//suceeded then return 0, else return non-zero.
CQ_C_LINK int32_t cq_http_get(const char *url, float timeout);

//data of last get request
CQ_C_LINK const void *cq_http_get_bytes(void);
CQ_C_LINK int32_t cq_http_get_size(void);
