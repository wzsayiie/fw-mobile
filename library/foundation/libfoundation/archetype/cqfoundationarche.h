#pragma once

#include "cqcbasis.h"

//log:

CQ_C_LINK void cq_log_info (const char *file, int32_t line, const char *message);
CQ_C_LINK void cq_log_error(const char *file, int32_t line, const char *message);

//file access:

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

typedef int32_t (*cq_http_body_reader)(void *user, void *buffer, int32_t length);
typedef int32_t (*cq_http_body_writer)(void *user, const void *data, int32_t length);

struct cq_http;

CQ_C_LINK struct cq_http *cq_http_create(void);
CQ_C_LINK void cq_http_destroy(struct cq_http *http);

CQ_C_LINK void cq_http_method(struct cq_http *http, const char *method);
CQ_C_LINK void cq_http_url(struct cq_http *http, const char *url);
CQ_C_LINK void cq_http_query(struct cq_http *http, const char *field, const char *value);
CQ_C_LINK void cq_http_header(struct cq_http *http, const char *field, const char *value);
CQ_C_LINK void cq_http_body(struct cq_http *http, void *user, cq_http_body_reader *reader);

CQ_C_LINK void cq_http_sync(float timeoutSeconds);

CQ_C_LINK int32_t cq_http_resp_code(struct cq_http *http);
CQ_C_LINK const char **cq_http_resp_header(struct cq_http *http);
CQ_C_LINK void cq_http_resp_body(struct cq_http *http, void *user, cq_http_body_writer *writer);

CQ_C_LINK void cq_http_timeout(struct cq_http *http, float seconds);
