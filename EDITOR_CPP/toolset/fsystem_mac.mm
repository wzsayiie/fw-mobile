#import <Foundation/Foundation.h>
#import "fsystem.hh"

//directory operation:

string getcwd() {
    char buf[1024] = "\0";
    getcwd(buf, sizeof(buf));
    return buf;
}

bool chdir(const string &dir) {
    return chdir(dir.c_str()) == 0;
}

//file or directory exists:

bool fexists(const string &path, bool *isdir) {
    NSFileManager *nsManager = NSFileManager.defaultManager;
    BOOL nsIsDirectory = NO;
    BOOL nsExists = [nsManager fileExistsAtPath:@(path.c_str()) isDirectory:&nsIsDirectory];
    
    if (isdir != nullptr) {
        *isdir = nsIsDirectory;
    }
    return nsExists;
}

//subitems of directory:

vector<fitem> subitems(const string &dir, bool *err) {
    //get the subitems:
    NSFileManager *nsManager = NSFileManager.defaultManager;
    NSError *nsError = nil;
    NSArray<NSString *> *nsContents = [nsManager contentsOfDirectoryAtPath:@(dir.c_str()) error:&nsError];
    
    if (err != nullptr) {
        *err = (nsError != nil);
    }
    if (nsError != nil) {
        return vector<fitem>();
    }
    
    //NOTE: the result of NSFileManager returns is not sorted.
    id nsComparer = ^NSComparisonResult(NSString *a, NSString *b) {
        return [a compare:b];
    };
    nsContents = [nsContents sortedArrayUsingComparator:nsComparer];
    
    //convert:
    vector<fitem> items;
    for (NSString *nsItem in nsContents) {
        //ignore ".", ".." and hidden files.
        if ([nsItem hasPrefix:@"."]) {
            continue;
        }
        
        bool isdir = false;
        if (!fexists(nsItem.UTF8String, &isdir)) {
            continue;
        }
        
        fitem it;
        it.name = nsItem.UTF8String;
        it.isdir = isdir;
        items.push_back(it);
    }
    return items;
}
