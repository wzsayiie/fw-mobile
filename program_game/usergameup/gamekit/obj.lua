--LUA R"R(

obj = class("obj", object, {
    native = 0
})

local function gc(obj)
    if obj.native ~= 0 then
        cs_release(obj.native)
    end
end

function obj:new_with(native)
    if native == 0 then
        return nil
    end

    local obj = object:new()
    getmetatable(obj).__gc = gc
    obj.native = native
    return obj
end

function obj:new_retain(native)
    if native ~= 0 then
        cs_retain(native)
        return obj:new_with(native)
    else
        return nil
    end
end

--)R"