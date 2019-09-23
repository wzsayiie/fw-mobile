--LUA R"R(
    
gobj = class("gobj", gk_obj, {
})

function gobj:create(name)
    local native = cs_create_gobj(name)
    -- NOTE: do not retain reference count once again.
    return gobj:new_with(native)
end

function gobj:set_name(name)
    cs_set_gobj_name(self.native, name)
end

function gobj:name()
    return cs_gobj_name(self.native)
end

function gobj:set_parent(parent)
    cs_set_gobj_parent(self.native, parent.native)
end

function gobj:parent()
    local native = cs_gobj_parent(self.native)
    return gobj:new_retain(native)
end

function gobj:child_num()
    return cs_child_num(self.native)
end

function gobj:child_at(index)
    local native = cs_child_at(self.native, index)
    return gobj:new_retain(native)
end

function gobj:detach_children()
    cs_detach_children(self.native)
end

function gobj:add_comp(cls)
    local id = cid:from_cls(cls)
    local native = cs_add_comp(self.native, id)
    return cls:new_retain(native)
end

function gobj:remove_comp(cls)
    local id = cid:from_cls(cls)
    cs_remove_comp(self.native, id)
end

function gobj:get_comp(cls)
    local id = cid:from_cls(cls)
    local native = cs_gobj_comp(self.native, id)
    return cls:new_retain(native)
end

function gobj:xfrom()
    local native = cs_gobj_xform(self.native)
    return xform:new_retain(native)
end

--)R"