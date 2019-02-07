CHost = extends(CObject, {
    theListeners = {},
})

CHost.Event = {
    AppCreate   = 1,
    UILoad      = 2,
    UIAppear    = 3,
    UIDisappear = 4,
}

CHost.Listener = extends(CObject, {
    onEvent = function(event) end,
})

function CHost:addListener(event, listener)
    if listener == nil then
        return
    end

    local list = CHost.theListeners[event]
    if list == nil then
        list = {}
        CHost.theListeners[event] = list
    end

    table.insert(list, listener)
end

function CHost:onEvent(event)
    local list = CHost.theListeners[event]
    if list == nil then
        return
    end

    for key, val in pairs(list) do
        val(event)
    end
end
