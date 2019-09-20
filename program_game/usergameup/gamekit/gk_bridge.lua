--LUA R"R(

gk_bridge = class("gk_bridge", object, {
    handle = 0
})

local function gc(obj)
    if obj.handle ~= 0 then
        cs_release(obj.handle)
    end
end

function gk_bridge:new_with(handle)
    if handle == 0 then
        return nil
    end

    local obj = object:new()
    getmetatable(obj).__gc = gc
    obj.handle = handle
    return obj
end

function gk_bridge:new_retain(handle)
    if handle ~= 0 then
        cs_retain(handle)
        return gk_bridge:new_with(handle)
    else
        return nil
    end
end

--)R"