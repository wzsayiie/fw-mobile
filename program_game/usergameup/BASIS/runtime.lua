--LUA R"R(

-- require
setmetatable(_G, {__index = function(tab, key)
    if pcall(require, string.lower(key)) then
        return tab[key]
    else
        return nil
    end
end})

-- object

_runtime_object = {}

function _runtime_object:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function _runtime_object:init()
end

function extends(super, this)
    setmetatable(this, {__index = super})
    this.super = super
    return this
end;

-- app entry
entry()

--)R"