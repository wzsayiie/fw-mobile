#pragma once

#include "cahead.h"

//depends on OS

extern const bool COnOSX;
extern const bool COnWindows;

extern const char CPathSeperator;

string CGetWorkDirectory();
bool CChangeDirectory(const string &path);
bool CFileExistsAtPath(const string &path, bool *isDirectory);

//exclude hidden files and directories.
//the returned items were sorted.
vector<string> CContentsOfDirectory(const string &path);

//portable

bool CIsPathSeperator(char ch);

//will erase "." and ".."
vector<string> CSplitPath(const string &path);

//only append "item" to "path"
void CAppendPath(string *path, const string &item);

string CBaseName(const string &path);
string CDirectoryPath(const string &path);

enum class CFileError {
    None         = 0,
    ParamInvaild = 1,
    OpenFailed   = 2,
};

CFileError CReadFile(const string &path, vector<char> *content);
CFileError CWriteFile(const string &path, const vector<char> &content);
