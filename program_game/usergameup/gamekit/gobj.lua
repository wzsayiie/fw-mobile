--LUA R"R(
    
gobj = class("gobj", gk_obj, {
})

function gobj:create(name)
    local native = cs_create_gobj(name)
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
    return gobj:new_with(native)
end

function gobj:child_num()
    return cs_child_num(self.native)
end

function gobj:child_at(index)
    local native = cs_child_at(self.native, index)
    return gobj:new_with(native)
end

function gobj:detach_children()
    cs_detach_children(self.native)
end

function gobj:add_comp(cls)
    if cls ~= nil and cls:is_kind_of(code_beh) then
        local native = cs_add_comp(self.native, cls.clsname)
        return cls:new_with(native)
    else
        return nil
    end
end

function gobj:remove_comp(cls)
    if cls ~= nil and cls:is_kind_of(code_beh) then
        cs_remove_comp(self.native, cls.clsname)
    end
end

function gobj:get_comp(cls)
    if cls ~= nil and cls:is_kind_of(code_beh) then
        local native = cs_gobj_comp(self.native, cls.clsname)
        return cls:new_with(native)
    else
        return nil
    end
end

function gobj:xfrom()
    local native = cs_gobj_xform(self.native)
    return xform:new_with(native)
end

--)R"