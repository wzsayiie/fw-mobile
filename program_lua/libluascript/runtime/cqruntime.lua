--/cqruntime.lua/

-- require

setmetatable(_G, {__index = function(tab, key)
    local succeed = cq_require(key)
    if succeed then
        return tab[key]
    else
        return nil
    end
end})

-- object

CQObject = {}

function CQObject:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function CQObject:init()
end
    
function cq_extends(super, this)
    setmetatable(this, {__index = super})
    this.super = super
    return this
end;

-- user need to implement this function
entry()
