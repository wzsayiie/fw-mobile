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
    return chdir(path) == 0;
}

bool CQFileExistsAtPath(const string &path, bool *isDirectory) {
    NSFileManager *manager = NSFileManager.defaultManager;
    return [manager fileExistsAtPath:path isDirectory:(BOOL *)isDirectory];
}

vector<string> CQContentsOfDirectory(const string &path) {
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
