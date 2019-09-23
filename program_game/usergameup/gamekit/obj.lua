--LUA R"R(

obj = class("obj", object, {
    handle = 0
})

local function gc(obj)
    if obj.handle ~= 0 then
        cs_release(obj.handle)
    end
end

function obj:new_with(handle)
    if handle == 0 then
        return nil
    end

    local obj = object:new()
    getmetatable(obj).__gc = gc
    obj.handle = handle
    return obj
end

function obj:new_retain(handle)
    if handle ~= 0 then
        cs_retain(handle)
        return obj:new_with(handle)
    else
        return nil
    end
end

--)R"