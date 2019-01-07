#pragma once

#include "types.h"

extern const char path_separator;

vector<string> split_path(const string &path);

string base_name(const string &path);

string dir_path(const string &path);

string get_work_dir();

bool change_dir(const string &path);

bool exist_path(const string &path, bool *is_dir);

//exclude hidden files and directories.
//the returned items were sorted.
vector<string> contents_of_dir(const string &path);
