#import "CQObjcBasis.h"
#import "cqfoundationarche.h"

void cq_http(const char *method) {
}

void cq_http_set_field(const char *field, const char *value) {
}

void cq_http_set_body_reader(cq_http_body_reader *reader) {
}

void cq_http_set_body_writer(cq_http_body_writer *writer) {
}

bool cq_http_resume(float timeoutSeconds) {
    return false;
}

int32_t cq_http_response_code(void) {
    return 0;
}

const char **cq_http_responded_fields(void) {
    return NULL;
}

const char **cq_http_responded_values(void) {
    return NULL;
}
