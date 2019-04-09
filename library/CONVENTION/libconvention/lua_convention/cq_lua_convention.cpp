#include "cq_lua_convention.h"

static const char *source = R"lua(
------------------------------------------------------------
setmetatable(_G, {__index = function(tab, key)
    local success, error = pcall(require, string.lower(key))
    if success then
        return tab[key]
    else
        return nil
    end
end})

CQObject = {}

function CQObject:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function CQObject:init()
end

function cq_extends(super, this)
    setmetatable(this, {__index = super})
    this.super = super
    return this
end;
------------------------------------------------------------
)lua";

void cq_lua_convention_open(void *lua_state, void (*execute)(const char *)) {
    if (execute != nullptr) {
        execute(source);
    }
}
