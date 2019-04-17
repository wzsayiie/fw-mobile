RootViewController = extends(CQViewController, {
})

function RootViewController:init()
    RootViewController.super.init(self)
end

function RootViewController:viewDidLoad()
    RootViewController.super.viewDidLoad(self)
    I("view load")
end

function RootViewController:viewDidAppear()
    RootViewController.super.viewDidAppear(self)
    I("view appear")
end

function RootViewController:viewDidDisappear()
    RootViewController.super.viewDidDisappear(self)
    I("view disappear")
end
