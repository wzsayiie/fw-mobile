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

function cs_on_cb_event(name, native)
    local obj = storage[native]
    if obj == nil then
        return
    end

    if     name == "awake"      then obj:awake()
    elseif name == "start"      then obj:start()
    elseif name == "update"     then obj:update()
    elseif name == "on_destroy" then obj:on_destroy()
    end

    if name == "on_destroy" then
        storage[native] = nil
    end
end

--)R"