#include "cscodebehaviour.hh"

cq_member(csCodeBehaviour) {
    bool waitingAwake = true;
    bool waitingStart = true;
};

bool csCodeBehaviour::external() {
    return !externalName().empty();
}

std::string csCodeBehaviour::externalName() {
    return "";
}

void csCodeBehaviour::emitUpdate() {
    //awake.
    if (dat->waitingAwake) {
        dat->waitingAwake = false;
        awake();
    }
    //start.
    if (dat->waitingStart) {
        dat->waitingStart = false;
        start();
    }
    //update.
    update();
}

void csCodeBehaviour::emitDestroy() {
    onDestroy();
}

void csCodeBehaviour::awake    () {}
void csCodeBehaviour::start    () {}
void csCodeBehaviour::update   () {}
void csCodeBehaviour::onDestroy() {}