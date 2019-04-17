CQHost = extends(CQObject, {
    theListeners = {},
})

CQHost.Event = {
    AppCreate   = 1,
    UILoad      = 2,
    UIAppear    = 3,
    UIDisappear = 4,
}

CQHost.Listener = extends(CQObject, {
    onEvent = function(event) end,
})

function CQHost:addListener(event, listener)
    if listener == nil then
        return
    end

    local list = CQHost.theListeners[event]
    if list == nil then
        list = {}
        CQHost.theListeners[event] = list
    end

    table.insert(list, listener)
end

function CQHost:onEvent(event)
    local list = CQHost.theListeners[event]
    if list == nil then
        return
    end

    for key, val in pairs(list) do
        val(event)
    end
end
