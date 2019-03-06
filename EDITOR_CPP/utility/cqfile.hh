#pragma once

#include "cqstdex.hh"

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

bool CQReadFile(const string &path, vector<char> *content);
bool CQWriteFile(const string &path, const vector<char> &content);

void CQTraverse(const string &path, struct CQTraverserDelegate *delegate);

struct CQTraverserDelegate : object {
    
    virtual void traverserGetDirectory(const string &name, int indent) = 0;
    virtual void traverserGetFile     (const string &name, int indent) = 0;
};
