#pragma once

#include "stdlibs.hh"

//get current work directory.
string cur_dir();

//change current work directory.
bool goto_dir(const string &dir);

//determine if the file exists.
bool file_at(const string &path, bool *is_dir);

struct file_info {
    bool is_dir = false;
    string name;
};

//get sub files of the directory.
//NOTE: hidden files will be ignored.
vector<file_info> sub_files_of(const string &dir, bool *err);
