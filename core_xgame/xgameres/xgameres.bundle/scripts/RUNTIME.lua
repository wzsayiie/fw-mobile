--object.
Object = {}

--extern classes and functions.
require "LIBRARY"

--automatically require.
setmetatable(_G, {__index = function(tab, key)
    local okay, msg = pcall(require, string.lower(key))
    if okay then
        I("required: " .. key)
        return tab[key]
    else
        local stack = debug.traceback()
        E("require error: " .. msg)
        E("error stack: " .. stack)
        return nil
    end
end})

--app entry.
Entry()
