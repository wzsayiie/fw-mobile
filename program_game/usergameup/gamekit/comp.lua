--LUA R"R(

comp = class("comp", node, {
})

function comp:gobj()
    local native = cs_comp_gobj(self.native)
    return gobj:new_with(native)
end

function comp:list_comp(cls)
    if cls ~= nil and cls:is_kind_of(comp) then
        local set = {}

        local num = cs_list_comp_begin(self.native, cls.clsname)
        for it = 0, num - 1 do
            local native = cs_list_comp_at(it)
            table.insert(set, cls:new_with(native))
        end
        cs_list_comp_end()

        return set
    end

    return nil
end

function comp:get_comp(cls)
    if cls ~= nil and cls:is_kind_of(comp) then
        local native = cs_get_comp(self.native, cls.clsname)
        return cls:new_with(native)
    end

    return nil
end

function comp:xfrom()
    local native = cs_get_xform(self.native)
    return xform:new_with(native)
end

--)R"