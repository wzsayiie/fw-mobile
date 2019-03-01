-- log

function I(message)
    if message ~= nil then
        print("info: " .. message)
    end
end

function E(message)
    if message ~= nil then
        print("ERROR: " .. message)
    end
end

-- auto load module

setmetatable(_G, {__index = function(tab, key)
    local success, error = pcall(require, string.lower(key))
    if success then
        return tab[key]
    else
        E("LUA RUNTIME ERROR: " .. error)
        return nil
    end
end})

-- root object

CQObject = {}

function CQObject:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function CQObject:init()
end

-- extends

function extends(super, this)
    setmetatable(this, {__index = super})
    this.super = super
    return this
end
