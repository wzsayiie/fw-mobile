--LUA R"R(

-- automatically require:
require "log"

setmetatable(_G, {__index = function(tab, key)
    local okay, msg = pcall(require, key)
    if okay then
        log:i("required: " .. key)
        return tab[key]
    else
        log:e("require error: " .. msg)
        return nil
    end
end})

-- app entry:
entry()

--)R"