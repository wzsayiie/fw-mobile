#import <Foundation/Foundation.h>
#import "filesystem.h"
#import "unistd.h"

const bool ON_OSX = true;
const bool ON_WINDOWS = false;
const char PATH_SEP = '/';

string get_work_dir() {
    const size_t size = 1024;
    char buffer[size];
    return getcwd(buffer, size);
}

bool change_dir(const string &path) {
    return chdir(path.c_str()) == 0;
}

bool exist_path(const string &path, bool *is_dir) {
    NSFileManager *manager = NSFileManager.defaultManager;
    NSString *target = @(path.c_str());
    return [manager fileExistsAtPath:target isDirectory:(BOOL *)is_dir];
}

vector<string> contents_of_dir(const string &path) {
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
