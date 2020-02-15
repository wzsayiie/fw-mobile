#include "csscript.hh"

static std::set<csScriptRef> theScripts;

void csScript::updateAll() {
    
    //NOTE: copy theScripts. it's possible to modify theScripts in handleUpdate().
    std::set<csScriptRef> scripts(theScripts);
    
    for (csScriptRef it : scripts) {
        it->handleUpdate();
    }
}

cq_member(csScript) {
    bool waitingAwake = true;
    bool waitingStart = true;
};

bool csScript::external() {
    return !externalName().empty();
}

std::string csScript::externalName() {
    return clazz()->name;
}

void csScript::handleCreate() {
    super::handleCreate();
    
    theScripts.insert(strongRef());
}

void csScript::handleDestroy() {
    super::handleDestroy();
    
    onDestroy();
    theScripts.erase(strongRef());
}

void csScript::handleUpdate() {
    //awake.
    if (dat->waitingAwake) {
        dat->waitingAwake = false;
        onAwake();
    }
    //start.
    if (dat->waitingStart) {
        dat->waitingStart = false;
        onStart();
    }
    //update.
    onUpdate();
}

void csScript::onAwake  () {}
void csScript::onStart  () {}
void csScript::onUpdate () {}
void csScript::onDestroy() {}
