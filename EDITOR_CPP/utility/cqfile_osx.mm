#import "cqfile.hh"
#import "unistd.h"

const bool cqOnOSX = true;
const bool cqOnWindows = false;

const char cqPathSeperator = '/';

string cqGetWorkDirectory() {
    const size_t size = 1024;
    char buffer[size];
    return getcwd(buffer, size);
}

bool cqChangeDirectory(const string &path) {
    return chdir(path) == 0;
}

bool cqFileExistsAtPath(const string &path, bool *isDirectory) {
    NSFileManager *manager = NSFileManager.defaultManager;
    return [manager fileExistsAtPath:path isDirectory:(BOOL *)isDirectory];
}

vector<string> cqContentsOfDirectory(const string &path) {
    NSFileManager *manager = [NSFileManager defaultManager];
    
    //get
    NSArray<NSString *> *items = [manager contentsOfDirectoryAtPath:path error:nil];
    
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
