RootViewController = extends(CQViewController, {
})

function RootViewController:init()
    RootViewController.super.init(self)
end

function RootViewController:viewDidLoad()
    I("view load")
end

function RootViewController:viewDidAppear()
    I("view appear")
end

function RootViewController:viewDidDisappear()
    I("view disappear")
end
