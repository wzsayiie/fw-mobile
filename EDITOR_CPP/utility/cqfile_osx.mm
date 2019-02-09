#import <Foundation/Foundation.h>
#import "cqfile.hh"
#import "unistd.h"

const bool CQOnOSX = true;
const bool CQOnWindows = false;

const char CQPathSeperator = '/';

string CQGetWorkDirectory() {
    const size_t size = 1024;
    char buffer[size];
    return getcwd(buffer, size);
}

bool CQChangeDirectory(const string &path) {
    return chdir(path.c_str()) == 0;
}

bool CQFileExistsAtPath(const string &path, bool *isDirectory) {
    NSFileManager *manager = NSFileManager.defaultManager;
    NSString *target = @(path.c_str());
    return [manager fileExistsAtPath:target isDirectory:(BOOL *)isDirectory];
}

vector<string> CQContentsOfDirectory(const string &path) {
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
