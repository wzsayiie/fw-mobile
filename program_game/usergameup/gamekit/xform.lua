--LUA R"R(

xform = class("xform", comp, {
})

function xform:set_xy(x, y)
    cs_set_xform_xy(self.native, x, y)
end

function xform:x()
    return cs_xform_x(self.native)
end

function xform:y()
    return cs_xform_y(self.native)
end

function xform:set_parent(parent)
    cs_set_xform_parent(self.native, parent.native)
end

function xform:parent()
    local native = cs_xform_parent(self.native)
    return xform:new_with(native)
end

--)R"