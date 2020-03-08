#pragma once

#include "cqcbasis.h"

//log:

CQ_C_LINK void cq_log_info (const char *file, int32_t line, const char *message);
CQ_C_LINK void cq_log_error(const char *file, int32_t line, const char *message);

//app bundle resource:

CQ_C_LINK const char *cq_ios_bundle_path(void);
CQ_C_LINK const char *cq_ios_resource_path(const char *name, const char *type);
CQ_C_LINK void cq_ios_resource(const char *name, const char *type, cq_bytes_out out);

CQ_C_LINK void cq_android_asset(const char *name, cq_bytes_out out);
CQ_C_LINK bool cq_android_copy_asset(const char *from_path, const char *to_path);

//file access:

CQ_C_LINK const char *cq_document_directory(void);
CQ_C_LINK const char *cq_caches_directory(void);
CQ_C_LINK const char *cq_temporary_directory(void);
CQ_C_LINK bool cq_directory_exists(const char *path);
CQ_C_LINK bool cq_file_exists(const char *path);
CQ_C_LINK bool cq_create_directory(const char *path, bool intermediate);
CQ_C_LINK void cq_remove_path(const char *path);
CQ_C_LINK void cq_sub_files(const char *path, cq_str_list_out out);

//thread:

CQ_C_LINK void cq_thread_run(cq_block block, void *data);
CQ_C_LINK void cq_thread_sleep(float seconds);

//main run loop:

CQ_C_LINK void cq_main_loop_post(cq_block block, void *data);

//http(s):

typedef int32_t (*cq_http_body_reader  )(void *user, void *buffer, int32_t length);
typedef void    (*cq_http_code_writer  )(void *user, int32_t code);
typedef void    (*cq_http_header_writer)(void *user, const char *field, const char *value);
typedef bool    (*cq_http_body_writer  )(void *user, const void *bytes, int32_t length);

cq_struct(cq_http);

CQ_C_LINK cq_http *cq_http_create(void);
CQ_C_LINK void cq_http_destroy(cq_http *http);

CQ_C_LINK void cq_http_timeout    (cq_http *http, float seconds);
CQ_C_LINK void cq_http_send_method(cq_http *http, const char *method);
CQ_C_LINK void cq_http_send_url   (cq_http *http, const char *url);
CQ_C_LINK void cq_http_send_query (cq_http *http, const char *field, const char *value);
CQ_C_LINK void cq_http_send_header(cq_http *http, const char *field, const char *value);

CQ_C_LINK void cq_http_send_body_from(cq_http *http, cq_http_body_reader   reader);
CQ_C_LINK void cq_http_recv_code_to  (cq_http *http, cq_http_code_writer   writer);
CQ_C_LINK void cq_http_recv_header_to(cq_http *http, cq_http_header_writer writer);
CQ_C_LINK void cq_http_recv_body_to  (cq_http *http, cq_http_body_writer   writer);

CQ_C_LINK void cq_http_sync(cq_http *http, void *user);
CQ_C_LINK const char *cq_http_error(cq_http *http);
