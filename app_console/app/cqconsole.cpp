#include "cqconsole.hh"

int main(int argc, const char *argv[]) {

    cqDispatch::setUserControlEnabled(true);

    launch(argc, argv);

    while (true) {
        while (!cqDispatch::mainQueueEmpty()) {
            cqDispatch::updateMain();
        }
        cqThread::sleep(0.1f);
    }
}
