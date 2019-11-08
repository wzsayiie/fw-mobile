--LUA R"R(

script = class("script", behaviour, {
})

function script:awake     () end
function script:start     () end
function script:update    () end
function script:on_destroy() end

local storage = {}

function script:new_with(native)
    local obj = behaviour.new_with(self, native)
    if native ~= 0 then
        storage[native] = obj
    end
    return obj
end

function cs_on_script_callback(name, native)
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