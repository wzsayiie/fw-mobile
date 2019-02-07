ApplicationDelegate = extends(CApplication.Delegate, {
    window = nil
})

function ApplicationDelegate:applicationDidFinishLaunching()
    ii("app finish launch")

    local viewController = RootViewController:new()
    self.window = CWindow:new()
    self.window:setRootViewController(viewController)
    self.window:makeKeyAndVisible()
end

function ApplicationDelegate:applicationDidBecomeActive()
    ii("app become active")
end

function ApplicationDelegate:applicationDidEnterBackground()
    ii("app enter background")
end
