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

cq_struct(cq_http);

CQ_C_LINK cq_http *cq_http_create(void);

static inline cq_http *cq_http_retain(cq_http *http) {
    return (cq_http *)cq_obj_retain(http);
}
static inline void cq_http_release(cq_http *http) {
    cq_obj_release(http);
}

CQ_C_LINK void cq_http_timeout    (cq_http *http, float seconds);
CQ_C_LINK void cq_http_send_method(cq_http *http, const char *method);
CQ_C_LINK void cq_http_send_url   (cq_http *http, const char *url);
CQ_C_LINK void cq_http_send_query (cq_http *http, const char *field, const char *value);
CQ_C_LINK void cq_http_send_header(cq_http *http, const char *field, const char *value);

cq_enum(int32_t, cq_http_event) {

    //block parameters:
    //  "buffer"  , a cq_bytes_out: request body buffer.
    //  "capacity", a cq_int32_in : max byte count can be written to "body" this time.
    //  "stop"    , a cq_bool_out : if assign true, means the request body transfer completed.
    //
    cq_http_e_send_body = 1,

    //block parameters:
    //  "body", a cq_bytes_in: part or all of the response body.
    //  "stop", a cq_bool_out: if assign true, then the stop transfer.
    //
    cq_http_e_recv_body = 2,
};
static inline void cq_http_listen_event(cq_http *http, cq_http_event event, cq_block func, void *data) {
    cq_obj_listen_event(http, event, func, data);
}
static inline void cq_http_emit_event(cq_http *http, cq_http_event event) {
    cq_obj_emit_event(http, event);
}

CQ_C_LINK void cq_http_sync(cq_http *http);

CQ_C_LINK const char *cq_http_error      (cq_http *http);
CQ_C_LINK int32_t     cq_http_recv_code  (cq_http *http);
CQ_C_LINK void        cq_http_recv_header(cq_http *http, cq_ss_map_out out);
