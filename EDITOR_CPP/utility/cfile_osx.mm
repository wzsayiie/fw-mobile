#import <Foundation/Foundation.h>
#import "cfile.h"
#import "unistd.h"

const bool COnOSX = true;
const bool COnWindows = false;

const char CPathSeperator = '/';

string CGetWorkDirectory() {
    const size_t size = 1024;
    char buffer[size];
    return getcwd(buffer, size);
}

bool CChangeDirectory(const string &path) {
    return chdir(path.c_str()) == 0;
}

bool CFileExistsAtPath(const string &path, bool *isDirectory) {
    NSFileManager *manager = NSFileManager.defaultManager;
    NSString *target = @(path.c_str());
    return [manager fileExistsAtPath:target isDirectory:(BOOL *)isDirectory];
}

vector<string> CContentsOfDirectory(const string &path) {
    NSFileManager *manager = [NSFileManager defaultManager];
    NSString *target = @(path.c_str());
    
    //get
    NSArray<NSString *> *items = [manager contentsOfDirectoryAtPath:target error:nil];
    
    //sort
    id comparer = ^NSComparisonResult(NSString *a, NSString *b) {
        return [a compare:b];
    };
    items = [items sortedArrayUsingComparator:comparer];
    
    //remove hidden items
    vector<string> contents;
    for (NSString *it in items) {
        if ([it hasPrefix:@"."]) {
            continue;
        }
        contents.push_back(it.UTF8String);
    }
    return contents;
}
