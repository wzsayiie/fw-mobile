#import "CQStandalone.h"
#import "cqstandalonearche.h"

void CQStandaloneUpdate(void) {
    cq_standalone_update();
}

void CQStandaloneLaunch(int argc, const char **argv) {
    cq_standalone_launch(argc, argv);
}
