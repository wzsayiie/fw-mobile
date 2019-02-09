CQObject = {}

function CQObject:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function CQObject:init()
end
