#pragma once

#include "types.h"

//app arguments ->

void set_args(int argc, const char *argv[], int begin);

vector<string> get_args();

//app entry ->

typedef void (*app_entry)();

struct entry_setter {
    entry_setter(app_entry entry, const string &name, const string &shortened);
};

#define ENTR(F, N) void F(); static entry_setter _e_##F(F, #F, N);

app_entry get_entry(const string &name);
