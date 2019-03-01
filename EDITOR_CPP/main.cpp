#include "utility.hh"

static void init();
static void run();

void init() {

    string rootDirectory = "fw-mobile";
    string filePath = __FILE__;

    size_t position = filePath.find(rootDirectory);
    if (position != string::npos) {
        string rootPath = filePath.substr(0, position + rootDirectory.size());
        CQChangeDirectory(rootPath);
        continue_last.print("work path: %s", rootPath.c_str());
    } else {
        continue_last.print("FAILED to change the path");
    }
}

int main(int argc, const char *argv[]) {
    init();
    run();
}

void run() {

#define E(F) do { void F(); F(); } while (0)
    
    E(ObjcppMain);
    E(CPPMain);
    E(CodeCountMain);
}
