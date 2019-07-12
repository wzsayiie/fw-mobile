#include "cqstandalonearche.h"
#include "cqctool.hh"
#include "cqfoundation.hh"

CQ_IF_ON_WINDOWS(int main(int c, const char **v) {return cq_standalone_main(c, v);})
CQ_IF_ON_OSX    (int main(int c, const char **v) {return cq_standalone_main(c, v);})

int cq_standalone_main(int argc, const char **argv) {
    return 0;
}
