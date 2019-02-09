#pragma once

#include "cqahead.hh"

//depends on OS

extern const bool CQOnOSX;
extern const bool CQOnWindows;

extern const char CQPathSeperator;

string CQGetWorkDirectory();
bool CQChangeDirectory(const string &path);
bool CQFileExistsAtPath(const string &path, bool *isDirectory);

//exclude hidden files and directories.
//the returned items were sorted.
vector<string> CQContentsOfDirectory(const string &path);

//portable

bool CQIsPathSeperator(char ch);

//will erase "." and ".."
vector<string> CQSplitPath(const string &path);

//only append "item" to "path"
void CQAppendPath(string *path, const string &item);

string CQBaseName(const string &path);
string CQDirectoryPath(const string &path);

enum class CQFileError {
    None         = 0,
    ParamInvaild = 1,
    OpenFailed   = 2,
};

CQFileError CQReadFile(const string &path, vector<char> *content);
CQFileError CQWriteFile(const string &path, const vector<char> &content);
