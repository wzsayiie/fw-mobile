--LUA R"R(

comp = class("comp", gk_obj, {
})

function comp:gobj()
    local native = cs_comp_gobj(self.native)
    return gobj:new_retain(native)
end

function comp:get_comp(cls)
    local id = cid:form_cls(cls)
    local native = cs_comp_brother(self.native, id)
    return comp:new_retain(native)
end

function comp:xfrom()
    local native = cs_comp_xform(self.native)
    return xform:new_retain(native)
end

--)R"