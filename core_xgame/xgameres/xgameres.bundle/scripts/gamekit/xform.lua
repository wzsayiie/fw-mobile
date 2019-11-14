--LUA R"R(

xform = class("xform", comp, {
})

function xform:set_pos(x, y)
    cs_set_xform_pos(self.native, x, y)
end

function xform:x()
    return cs_xform_x(self.native)
end

function xform:y()
    return cs_xform_y(self.native)
end

function xform:set_parent(parent)
    if parent ~= nil then
        cs_set_xform_parent(self.native, parent.native)
    else
        cs_set_xform_parent(self.native, nil)
    end
end

function xform:parent()
    local native = cs_xform_parent(self.native)
    return xform:new_with(native)
end

function xform:children()
    local set = {}

    local num = cs_list_child_begin(self.native)
    for it = 0, num - 1 do
        local native = cs_list_child_at(it)
        table.insert(set, xform:new_with(native))
    end
    cs_list_child_end()

    return set
end

function xform:detach_children()
    cs_detach_children(self.native)
end

--)R"