#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

# ifdef __cplusplus
#   define CQ_C_LINK extern "C"
# else
#   define CQ_C_LINK
# endif

//storing a string on current thread,
//until call of cq_string_store_xx again on same thread.
CQ_C_LINK const char *cq_string_store_string(const char *value);
CQ_C_LINK const char *cq_string_store_bytes(const char *bytes, int32_t size);
CQ_C_LINK const char *cq_string_get_stored_bytes(void);
CQ_C_LINK int32_t cq_string_get_stored_size(void);
