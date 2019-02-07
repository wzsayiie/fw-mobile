RootViewController = extends(CViewController, {
})

function RootViewController:init()
    RootViewController.super.init(self)
end

function RootViewController:viewDidLoad()
    ii("view load")
end

function RootViewController:viewDidAppear()
    ii("view appear")
end

function RootViewController:viewDidDisappear()
    ii("view disappear")
end
