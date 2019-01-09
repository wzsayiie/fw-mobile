#pragma once

#include "types.h"

//depends on os ->

extern const bool ON_OSX;
extern const bool ON_WINDOWS;
extern const char PATH_SEP;

string get_work_dir();
bool change_dir(const string &path);
bool exist_path(const string &path, bool *is_dir);

//exclude hidden files and directories.
//the returned items were sorted.
vector<string> contents_of_dir(const string &path);

//portable ->

bool is_path_sep(char ch);

//will erase "." and ".."
vector<string> split_path(const string &path);

//only append "item" to "out_path"
void append_path(string *out_path, const string &item);

string base_name(const string &path);
string dir_path(const string &path);
