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

//succeeded then return 0, else return non-zero.
CQ_C_LINK int32_t cq_http_get(const char *url, float timeout);

//data of last get request.
CQ_C_LINK const void *cq_http_get_bytes(void);
CQ_C_LINK int32_t cq_http_get_size(void);

CQ_C_LINK int64_t cq_tcp_connect(const char *host, int16_t port);
CQ_C_LINK void cq_tcp_disconnect(int64_t handle);

//if return false, the tcp was disconnected.
CQ_C_LINK bool cq_tcp_send_bytes(int64_t handle, const void *bytes, int32_t size);

//if return value
//  > 0 : received data;
//  = 0 : there was not received data currently;
//  < 0 : the tcp disconnected.
CQ_C_LINK int32_t cq_tcp_received_size(int64_t handle);
CQ_C_LINK const void *cq_tcp_received_bytes(int64_t handle);
