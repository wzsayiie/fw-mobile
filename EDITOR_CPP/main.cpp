#include "utility.hh"

static void GotoWorkDirectory() {

    string rootDirectory = "fw-mobile";
    string filePath = __FILE__;

    size_t position = filePath.find(rootDirectory);
    if (position != string::npos) {
        string rootPath = filePath.substr(0, position + rootDirectory.size());
        CQChangeDirectory(rootPath);
    }
}

static void Execute(void (*func)(), const int *enabled) {
    if (*enabled != 0) {
        func();
    }
}

#define E(N) extern const int N##Enabled; void N(); Execute(N, &N##Enabled);

int main(int argc, const char *argv[]) {
    GotoWorkDirectory();
    
    string currentPath = CQGetWorkDirectory();
    continue_last.print("work path: %s", currentPath.c_str());
    
    E(ObjcppMain);
    E(CPPMain);
    E(CodeCountMain);
}
