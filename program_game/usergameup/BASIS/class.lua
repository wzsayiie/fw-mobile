--LUA R"R(

object = {
    clsname = "object",
    super = nil,
    cls = self
}

function object:new(...)
    local obj = setmetatable({}, {
        __gc = function() end,
        __index = self
    })
    obj:init(...)
    return obj
end

function object:init()
end

function object:is_kind_of(cls)
    if cls == nil then
        return false
    end

    local own = self.cls
    while own ~= nil do
        if own == cls then
            return true
        end
        own = own.super
    end
    return false
end

function class(clsname, super, this)
    setmetatable(this, {__index = super})
    this.clsname = clsname
    this.super = super
    this.cls = this
    return this
end

--)R"