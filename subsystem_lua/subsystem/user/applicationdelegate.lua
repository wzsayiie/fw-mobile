ApplicationDelegate = extends(CQApplication.Delegate, {
    window = nil
})

function ApplicationDelegate:applicationDidFinishLaunching()
    I("app finish launch")

    local controller = RootViewController:new()
    self.window = CQWindow:new()
    self.window:setRootViewController(controller)
    self.window:makeKeyAndVisible()
end

function ApplicationDelegate:applicationDidBecomeActive()
    I("app become active")
end

function ApplicationDelegate:applicationDidEnterBackground()
    I("app enter background")
end
