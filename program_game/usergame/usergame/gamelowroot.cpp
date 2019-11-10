#include "gamelowroot.hh"
#include "cqfoundation.hh"
#include "respackage.hh"

cq_member(GameLowRoot) {
};

void GameLowRoot::awake() {
    ResPackage::load();
    ResPackage::startupLuaVM();
}

void GameLowRoot::start() {
}

void GameLowRoot::update() {
}
