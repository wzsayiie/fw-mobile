#pragma once

#include "cqcbasis.h"

//log:

CQ_C_LINK void cq_log_info (const char *file, int32_t line, const char *message);
CQ_C_LINK void cq_log_error(const char *file, int32_t line, const char *message);

//app bundle resource:

CQ_C_LINK const char *cq_ios_bundle_path(void);

//get ios app bundle resource or android app assets resourse.
//NOTE: return value need to release by free().
CQ_C_LINK uint8_t *cq_ios_bundle_res(int32_t *len, const char *type, const char *name);
CQ_C_LINK uint8_t *cq_andr_asset(int32_t *len, const char *name);

CQ_C_LINK bool cq_andr_copy_asset(const char *from_path, const char *to_path);

//file access:

CQ_C_LINK const char *cq_document_directory(void);
CQ_C_LINK const char *cq_caches_directory(void);
CQ_C_LINK const char *cq_temporary_directory(void);
CQ_C_LINK bool cq_directory_exists(const char *path);
CQ_C_LINK bool cq_file_exists(const char *path);
CQ_C_LINK bool cq_create_directory(const char *path, bool intermediate);
CQ_C_LINK void cq_remove_path(const char *path);

CQ_C_LINK bool cq_open_dir(const char *path);
CQ_C_LINK const char *cq_read_dir(void);
CQ_C_LINK void cq_close_dir(void);

//thread:

CQ_C_LINK void cq_thread_run(void (*task)(void *), void *data);
CQ_C_LINK void cq_thread_sleep(float seconds);

//http(s):

typedef int32_t (*cq_http_body_reader  )(void *user, void *buffer, int32_t length);
typedef void    (*cq_http_code_writer  )(void *user, int32_t code);
typedef void    (*cq_http_header_writer)(void *user, const char *field, const char *value);
typedef bool    (*cq_http_body_writer  )(void *user, const void *bytes, int32_t length);

struct cq_http;

CQ_C_LINK struct cq_http *cq_http_create(void);
CQ_C_LINK void cq_http_destroy(struct cq_http *http);

CQ_C_LINK void cq_http_timeout    (struct cq_http *http, float seconds);
CQ_C_LINK void cq_http_send_method(struct cq_http *http, const char *method);
CQ_C_LINK void cq_http_send_url   (struct cq_http *http, const char *url);
CQ_C_LINK void cq_http_send_query (struct cq_http *http, const char *field, const char *value);
CQ_C_LINK void cq_http_send_header(struct cq_http *http, const char *field, const char *value);

CQ_C_LINK void cq_http_send_body_from(struct cq_http *http, cq_http_body_reader   reader);
CQ_C_LINK void cq_http_recv_code_to  (struct cq_http *http, cq_http_code_writer   writer);
CQ_C_LINK void cq_http_recv_header_to(struct cq_http *http, cq_http_header_writer writer);
CQ_C_LINK void cq_http_recv_body_to  (struct cq_http *http, cq_http_body_writer   writer);

CQ_C_LINK void cq_http_sync(struct cq_http *http, void *user);
CQ_C_LINK const char *cq_http_error(struct cq_http *http);
