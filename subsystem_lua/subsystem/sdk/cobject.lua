CObject = {}

function CObject:new(...)
    local object = setmetatable({}, {__index = self})
    object:init(...)
    return object
end

function CObject:init()
end
