#include "utility.hh"

void initialize() {

    string rootDirectory = "fw-mobile";
    string filePath = __FILE__;

    size_t position = filePath.find(rootDirectory);
    if (position != string::npos) {
        string rootPath = filePath.substr(0, position + rootDirectory.size());
        cqChangeDirectory(rootPath);
        continue_last.print("work path: %s", rootPath.c_str());
    } else {
        continue_last.print("FAILED to change the path");
    }
}

static void execute();

int main(int argc, char *argv[]) {
    initialize();
    execute();
    space_line(1);
}

void execute() {
    
    extern bool ccMainEnabled;
    extern bool xxMainEnabled;
    extern bool mmMainEnabled;
    void ccMain();
    void xxMain();
    void mmMain();
    
    if (ccMainEnabled) { ccMain(); }
    if (xxMainEnabled) { xxMain(); }
    if (mmMainEnabled) { mmMain(); }
}
