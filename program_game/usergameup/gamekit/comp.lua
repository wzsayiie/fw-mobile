--LUA R"R(

comp = class("comp", gk_obj, {
})

function comp:gobj()
    local native = cs_comp_gobj(self.native)
    return gobj:new_with(native)
end

function comp:get_comp(cls)
    if cls ~= nil and cls:is_kind_of(code_beh) then
        local native = cs_comp_brother(self.native, cls.clsname)
        return cls:new_with(native)
    else
        return nil
    end
end

function comp:xfrom()
    local native = cs_comp_xform(self.native)
    return xform:new_with(native)
end

--)R"