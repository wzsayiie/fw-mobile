#pragma once

#include "cqobject.hh"

void CQLogI(const char *file, int line, const char *format, ...) __printflike(3, 4);
void CQLogE(const char *file, int line, const char *format, ...) __printflike(3, 4);

#define I(...) CQLogI(__FILE__, __LINE__, __VA_ARGS__)
#define E(...) CQLogE(__FILE__, __LINE__, __VA_ARGS__)
