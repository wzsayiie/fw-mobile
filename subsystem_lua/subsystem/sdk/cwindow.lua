CWindow = extends(CView, {
    rootViewController = nil,
})

function CWindow:init()
    CWindow.super.init(self)
end

function CWindow:setRootViewController(controller)
    self.rootViewController = controller
end

function CWindow:getRootViewController()
    return self.rootViewController
end

function CWindow:makeKeyAndVisible()
    local a = self
    CHost:addListener(CHost.Event.UILoad     , function() onUILoad     (a) end)
    CHost:addListener(CHost.Event.UIAppear   , function() onUIAppear   (a) end)
    CHost:addListener(CHost.Event.UIDisappear, function() onUIDisappear(a) end)
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
