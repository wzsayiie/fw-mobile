--extern classes and functions.
require "LIBRARY"

--automatically require.
setmetatable(_G, {__index = function(tab, key)
    local okay, msg = pcall(require, string.lower(key))
    if okay then
        i("required: " .. key)
        return tab[key]
    else
        local stack = debug.traceback()
        e("require error: " .. msg)
        e("error stack: " .. stack)
        return nil
    end
end})

--app entry.
entry()
