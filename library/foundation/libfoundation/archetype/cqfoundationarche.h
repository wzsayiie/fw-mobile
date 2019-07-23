#pragma once

#include "cqcbasis.h"

//log:

CQ_C_LINK void cq_log_info (const char *file, int32_t line, const char *message);
CQ_C_LINK void cq_log_error(const char *file, int32_t line, const char *message);

//file manager:

CQ_C_LINK const char *cq_document_directory(void);
CQ_C_LINK const char *cq_caches_directory(void);
CQ_C_LINK const char *cq_temporary_directory(void);
CQ_C_LINK bool cq_directory_exists(const char *path);
CQ_C_LINK bool cq_file_exists(const char *path);
CQ_C_LINK bool cq_create_directory(const char *path, bool intermediate);
CQ_C_LINK void cq_remove_path(const char *path);

//thread:

CQ_C_LINK void cq_thread_run(void (*task)(void *), void *data);
CQ_C_LINK void cq_thread_sleep(float seconds);

//http(s):

typedef int32_t (*cq_http_body_reader)(void *buffer, int32_t length);
typedef int32_t (*cq_http_body_writer)(void *buffer, int32_t length);

CQ_C_LINK void cq_http(const char *method);
CQ_C_LINK void cq_http_set_field(const char *field, const char *value);
CQ_C_LINK void cq_http_set_body_reader(cq_http_body_reader *reader);
CQ_C_LINK void cq_http_set_body_writer(cq_http_body_writer *writer);
CQ_C_LINK bool cq_http_resume(float timeoutSeconds);

CQ_C_LINK int32_t cq_http_response_code(void);
CQ_C_LINK const char **cq_http_responded_fields(void);
CQ_C_LINK const char **cq_http_responded_values(void);
