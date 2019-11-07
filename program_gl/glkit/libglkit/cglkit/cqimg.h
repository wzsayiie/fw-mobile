#pragma once

#include "cqdraw2d.h"

CQ_C_LINK struct cq_tex *cq_img_from_data(const uint8_t *data);
CQ_C_LINK struct cq_tex *cq_img_from_file(const char *path);
