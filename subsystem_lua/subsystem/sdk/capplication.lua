CApplication = extends(CObject, {
    theObject = nil,
    delegate = nil,
})

CApplication.Delegate = extends(CObject, {
    applicationDidFinishLaunching = function() end,
    applicationDidBecomeActive    = function() end,
    applicationDidEnterBackground = function() end,
})

function CApplication:sharedApplication()
    if CApplication.theObject == nil then
        CApplication.theObject = CApplication:new()
    end
    return CApplication.theObject
end

local function onAppCreate(self)
    if self.delegate ~= nil then
        self.delegate:applicationDidFinishLaunching()
    end
end

local function onUIAppear(self)
    if self.delegate ~= nil then
        self.delegate:applicationDidBecomeActive()
    end
end

local function onUIDisappear(self)
    if self.delegate ~= nil then
        self.delegate:applicationDidEnterBackground()
    end
end

function CApplication:init()
    CApplication.super.init(self)

    local a = self
    CHost:addListener(CHost.Event.AppCreate  , function() onAppCreate  (a) end)
    CHost:addListener(CHost.Event.UIAppear   , function() onUIAppear   (a) end)
    CHost:addListener(CHost.Event.UIDisappear, function() onUIDisappear(a) end)
end

function CApplication:setDelegate(delegate)
    self.delegate = delegate
end

function CApplication:getDelegate()
    return self.delegate
end

function CApplicationMain(delegate)
    CApplication:sharedApplication():setDelegate(delegate)
end
