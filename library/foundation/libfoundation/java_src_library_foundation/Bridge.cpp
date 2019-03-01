#include "cqbridge.hh"

CQ_C_LINK void CQ_Logger_info(CQValue message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "info", message, CQValueNull, CQValueNull, CQValueNull);
}

CQ_C_LINK void CQ_Logger_error(CQValue message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "error", message, CQValueNull, CQValueNull, CQValueNull);
}
