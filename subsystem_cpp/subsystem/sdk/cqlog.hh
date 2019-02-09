#pragma once

#include "cqobject.hh"

void CLogI(const char *file, int line, const char *format, ...) __printflike(3, 4);
void CLogE(const char *file, int line, const char *format, ...) __printflike(3, 4);

#define ii(...) CLogI(__FILE__, __LINE__, __VA_ARGS__)
#define ee(...) CLogE(__FILE__, __LINE__, __VA_ARGS__)
