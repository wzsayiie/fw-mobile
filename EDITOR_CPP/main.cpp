#include "utility.hh"

static void GotoWorkDirectory() {

    string rootDirectory = "fw-mobile";
    string filePath = __FILE__;

    size_t position = filePath.find(rootDirectory);
    if (position != string::npos) {
        string rootPath = filePath.substr(0, position + rootDirectory.size());
        CQChangeDirectory(rootPath);
    }
    
    string currentPath = CQGetWorkDirectory();
    I("Work Path: %s", currentPath.c_str());
}

#define ENTRY(F) do { void F(); F(); } while (0)

int main(int argc, const char *argv[]) {
    GotoWorkDirectory();

    ENTRY(ObjCPPMain);
    ENTRY(CPPMain);
    ENTRY(CodeCountMain);
}
