#include "gameroot.hh"
#include "luacontrol.hh"

cq_member(GameRoot) {
};

void GameRoot::awake() {
    LuaControl::startup();
}

void GameRoot::start() {
}

void GameRoot::update() {
}
