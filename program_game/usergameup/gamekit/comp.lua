--LUA R"R(

comp = class("comp", gk_obj, {
})

function comp:gobj()
    local native = cs_comp_gobj(self.native)
    return gobj:new_with(native)
end

function comp:get_comp(cls)
    local cid = comp:id_from_cls(cls)
    local native = cs_comp_brother(self.native, cid)
    return cls:new_with(native)
end

function comp:xfrom()
    local native = cs_comp_xform(self.native)
    return xform:new_with(native)
end

comp_id = {
    camera   = 1,
    code_beh = 2,
    xform    = 3,
}

function comp:id_from_cls(cls)

    if     cls:is_kind_of(camera  ) then return comp_id.camera
    elseif cls:is_kind_of(code_beh) then return comp_id.code_beh
    elseif cls:is_kind_of(xform   ) then return comp_id.xform
    
    else return 0 end
end

--)R"