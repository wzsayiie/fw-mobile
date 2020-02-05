#include "cqconsole.hh"

int main(int argc, const char *argv[]) {

    launch(argc, argv);

    while (true) {
        while (!cqDispatch::mainQueueEmpty()) {
            cqDispatch::updateMain();
        }
        cqThread::sleep(0.1f);
    }
}
