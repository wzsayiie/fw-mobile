#pragma once

#include "cqstdex.hh"

//depends on OS

extern const bool cqOnOSX;
extern const bool cqOnWindows;

extern const char cqPathSeperator;

string cqGetWorkDirectory();
bool cqChangeDirectory(const string &path);
bool cqFileExistsAtPath(const string &path, bool *isDirectory);

//exclude hidden files and directories.
//the returned items were sorted.
vector<string> cqContentsOfDirectory(const string &path);

//portable

bool cqIsPathSeperator(char ch);

//will erase "." and ".."
vector<string> cqSplitPath(const string &path);

//only append "item" to "path"
void cqAppendPath(string *path, const string &item);

string cqBaseName(const string &path);
string cqDirectoryPath(const string &path);

bool cqReadFile(const string &path, vector<char> *content);
bool cqWriteFile(const string &path, const vector<char> &content);

void cqTraverse(const string &path, struct cqTraverserDelegate *delegate);

struct cqTraverserDelegate : object {
    
    virtual void traverserGetDirectory(const string &name, int indent) = 0;
    virtual void traverserGetFile     (const string &name, int indent) = 0;
};
