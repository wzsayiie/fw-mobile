CQViewController = extends(CQObject, {
    view = nil,
})

function CQViewController:init()
    CQViewController.super.init(self)
end

function CQViewController:viewDidLoad()
end

function CQViewController:viewDidAppear()
end

function CQViewController:viewDidDisappear()
end

function CQViewController:view()
    if self.view == nil then
        self:loadView()
    end
    return self.view
end

function CQViewController:loadView()
    self.view = CQView:new()
end
