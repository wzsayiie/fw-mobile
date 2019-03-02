#include "cqbridge.hh"
#include "cqbridgejni.hh"

CQ_C_LINK void CQ_Logger_info(CQBridgeValue message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "info", message, CQBridgeValueNull, CQBridgeValueNull, CQBridgeValueNull);
}

CQ_C_LINK void CQ_Logger_error(CQBridgeValue message) {
    CQJavaCallStatic("src/library/foundation/Bridge", "error", message, CQBridgeValueNull, CQBridgeValueNull, CQBridgeValueNull);
}
