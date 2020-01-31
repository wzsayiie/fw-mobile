#pragma once

#include "stdlibs.hh"

string work_dir();
bool goto_dir(const string &dir);

bool file_at(const string &path, bool *is_dir);

struct file_info {
    bool is_dir = false;
    string name;
};

//get sub files of the directory. NOTE: hidden files will be ignored.
vector<file_info> sub_files_of(const string &dir, bool *err);
