--LUA R"R(

code_beh = class("code_beh", beh, {
})

function code_beh:awake     () end
function code_beh:start     () end
function code_beh:update    () end
function code_beh:on_destroy() end

local storage = {}

function code_beh:new_with(native)
    local obj = beh.new_with(self, native)
    if native ~= 0 then
        storage[native] = obj
    end
    return obj
end

function code_beh:new_retain(native)
    local obj = beh.new_retain(self, native)
    if native ~= 0 then
        storage[native] = obj
    end
    return obj
end

function cs_on_code_beh_awake(native)
    local obj = storage[native]

    if obj ~= nil then
        obj:awake()
    end
end

function cs_on_code_beh_start(native)
    local obj = storage[native]
    
    if obj ~= nil then
        obj:start()
    end
end

function cs_on_code_beh_update(native)
    local obj = storage[native]
    
    if obj ~= nil then
        obj:update()
    end
end

function cs_on_code_beh_on_destroy(native)
    local obj = storage[native]
    
    if obj ~= nil then
        obj:on_destroy()
        storage[native] = nil
    end
end

--)R"