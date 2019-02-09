ApplicationDelegate = extends(CQApplication.Delegate, {
    window = nil
})

function ApplicationDelegate:applicationDidFinishLaunching()
    ii("app finish launch")

    local controller = RootViewController:new()
    self.window = CQWindow:new()
    self.window:setRootViewController(controller)
    self.window:makeKeyAndVisible()
end

function ApplicationDelegate:applicationDidBecomeActive()
    ii("app become active")
end

function ApplicationDelegate:applicationDidEnterBackground()
    ii("app enter background")
end
