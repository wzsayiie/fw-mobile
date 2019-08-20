#include "cqstandalonearche.h"
#include "cqctool.hh"
#include "cqfoundation.hh"

void cq_standalone_update() {
    cqDispatch::updateMain();
}

CQ_IF_ON_ANDROID(void __u(int argc, const char **argv))
CQ_IF_ON_IOS    (void __u(int argc, const char **argv))
CQ_IF_ON_WINDOWS(int main(int argc, const char **argv))
CQ_IF_ON_OSX    (int main(int argc, const char **argv))
{
    cq_standalone_launch(argc, argv);
    while (true) {
        while (!cqDispatch::mainQueueEmpty()) {
            cq_standalone_update();
        }
        cqThread::sleep(0.1f);
    }
}

void cq_standalone_launch(int argc, const char **argv) {
}
