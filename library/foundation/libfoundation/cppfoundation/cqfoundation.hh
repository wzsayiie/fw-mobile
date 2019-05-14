#pragma once

#include "cqcppbasis.hh"

void cqLogInfo (const char *file, int line, const char *format, ...);
void cqLogError(const char *file, int line, const char *format, ...);

#define I(...) cqLogInfo (__FILE__, __LINE__, __VA_ARGS__)
#define E(...) cqLogError(__FILE__, __LINE__, __VA_ARGS__)
