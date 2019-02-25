#pragma once

#include "cqobject.hh"

void _CQLogInfo (const char *file, int line, const char *format, ...) __printflike(3, 4);
void _CQLogError(const char *file, int line, const char *format, ...) __printflike(3, 4);

#define I(...) _CQLogInfo (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) _CQLogError(__FILE__, __LINE__, __VA_ARGS__)
