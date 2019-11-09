--LUA R"R(

-- automatically require:
require "log"

setmetatable(_G, {__index = function(tab, key)
    local okay, msg = pcall(require, key)
    if okay then
        log:i("required: " .. key)
        return tab[key]
    else
        local stack = debug.traceback()
        log:e("require error: " .. msg)
        log:e("error stack: " .. stack)
        return nil
    end
end})

-- app entry:
entry()

--)R"