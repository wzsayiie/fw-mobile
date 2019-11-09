#include "gamelowroot.hh"
#include "cqfoundation.hh"
#include "luacontrol.hh"

cq_member(GameLowRoot) {
};

void GameLowRoot::awake() {
    LuaControl::startup();
}

void GameLowRoot::start() {
}

void GameLowRoot::update() {
}
