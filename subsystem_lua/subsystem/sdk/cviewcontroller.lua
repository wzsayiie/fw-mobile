CViewController = extends(CObject, {
    view = nil,
})

function CViewController:init()
    CViewController.super.init(self)
end

function CViewController:viewDidLoad()
end

function CViewController:viewDidAppear()
end

function CViewController:viewDidDisappear()
end

function CViewController:view()
    if self.view == nil then
        self:loadView()
    end
    return self.view
end

function CViewController:loadView()
    self.view = CView:new()
end
