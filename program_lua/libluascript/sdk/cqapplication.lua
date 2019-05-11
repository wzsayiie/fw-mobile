CQApplication = extends(CQObject, {
    theObject = nil,
    delegate = nil,
})

CQApplication.Delegate = extends(CQObject, {
    applicationDidFinishLaunching = function() end,
    applicationDidBecomeActive    = function() end,
    applicationDidEnterBackground = function() end,
})

function CQApplication:sharedApplication()
    if CQApplication.theObject == nil then
        CQApplication.theObject = CQApplication:new()
    end
    return CQApplication.theObject
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

function CQApplication:init()
    CQApplication.super.init(self)

    local a = self
    CQHost:addListener(CQHost.Event.AppCreate  , function() onAppCreate  (a) end)
    CQHost:addListener(CQHost.Event.UIAppear   , function() onUIAppear   (a) end)
    CQHost:addListener(CQHost.Event.UIDisappear, function() onUIDisappear(a) end)
end

function CQApplication:setDelegate(delegate)
    self.delegate = delegate
end

function CQApplication:getDelegate()
    return self.delegate
end

function CQApplicationMain(delegate)
    CQApplication:sharedApplication():setDelegate(delegate)
end
