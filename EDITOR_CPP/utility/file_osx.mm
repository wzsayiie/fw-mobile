#import <Foundation/Foundation.h>
#import "file.hh"

string getcwd() {
    char buffer[1024];
    getcwd(buffer, sizeof(buffer));
    return buffer;
}

bool chdir(const string &dir) {
    return chdir(dir.c_str()) == 0;
}

bool fexists(const string &path, bool *isdir) {
    NSFileManager *manager = NSFileManager.defaultManager;
    BOOL isDirectory = NO;
    BOOL exists = [manager fileExistsAtPath:@(path.c_str()) isDirectory:&isDirectory];
    
    if (isdir != nullptr) {
        *isdir = isDirectory;
    }
    return exists;
}

vector<fitem> subitems(const string &dir, bool *err) {
    //get contents
    NSFileManager *manager = NSFileManager.defaultManager;
    NSError *nsError = nil;
    auto contents = [manager contentsOfDirectoryAtPath:@(dir.c_str()) error:&nsError];
    if (err != nullptr) {
        *err = (nsError != nil);
    }
    if (nsError != nil) {
        return vector<fitem>();
    }
    
    //sort
    id comparer = ^NSComparisonResult(NSString *a, NSString *b) {
        return [a compare:b];
    };
    contents = [contents sortedArrayUsingComparator:comparer];
    
    //data convert
    vector<fitem> items;
    for (NSString *name in contents) {
        //ignore "." and ".."
        if ([name hasPrefix:@"."]) {
            continue;
        }
        bool isdir = false;
        if (fexists(name.UTF8String, &isdir)) {
            fitem it;
            it.name = name.UTF8String;
            it.isdir = isdir;
            items.push_back(it);
        }
    }
    return items;
}
