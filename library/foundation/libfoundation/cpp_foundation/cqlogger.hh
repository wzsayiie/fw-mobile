#pragma once

#include "cqconvention.hh"

void _I(const char *file, int line, const char *format, ...) __printflike(3, 4);
void _E(const char *file, int line, const char *format, ...) __printflike(3, 4);

#define I(...) _I(__FILE__, __LINE__, __VA_ARGS__)
#define E(...) _E(__FILE__, __LINE__, __VA_ARGS__)
