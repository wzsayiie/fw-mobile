CQWindow = extends(CQView, {
    rootViewController = nil,
})

function CQWindow:init()
    CQWindow.super.init(self)
end

function CQWindow:setRootViewController(controller)
    self.rootViewController = controller
end

function CQWindow:getRootViewController()
    return self.rootViewController
end

function CQWindow:makeKeyAndVisible()
    local a = self
    CQHost:addListener(CQHost.Event.UILoad     , function() onUILoad     (a) end)
    CQHost:addListener(CQHost.Event.UIAppear   , function() onUIAppear   (a) end)
    CQHost:addListener(CQHost.Event.UIDisappear, function() onUIDisappear(a) end)
end

function onUILoad(self)
    if self.rootViewController ~= nil then
        self.rootViewController:viewDidLoad()
    end
end

function onUIAppear(self)
    if self.rootViewController ~= nil then
        self.rootViewController:viewDidAppear()
    end
end

function onUIDisappear(self)
    if self.rootViewController ~= nil then
        self.rootViewController:viewDidDisappear()
    end
end
