#include "bridge.h"

BRG_EXPORT void FDN_Logger_info(BRGType message) {
    BRGJavaCallStatic("src/library/foundation/Bridge", "info", message, BRGTypeNULL, BRGTypeNULL, BRGTypeNULL);
}

BRG_EXPORT void FDN_Logger_error(BRGType message) {
    BRGJavaCallStatic("src/library/foundation/Bridge", "error", message, BRGTypeNULL, BRGTypeNULL, BRGTypeNULL);
}
