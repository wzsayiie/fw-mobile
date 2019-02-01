#include "cbridge.h"

CQ_EXPORT void CQ_Logger_info(CQType message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "info", message, CQTypeNULL, CQTypeNULL, CQTypeNULL);
}

CQ_EXPORT void CQ_Logger_error(CQType message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "error", message, CQTypeNULL, CQTypeNULL, CQTypeNULL);
}
