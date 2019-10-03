--LUA R"R(

gobj = class("gobj", node, {
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

function gobj:add_comp(cls)
    if cls ~= nil and cls:is_kind_of(comp) then
        local native = cs_add_comp(self.native, cls.clsname)
        return cls:new_with(native)
    end

    return nil
end

function gobj:remove_comp(obj)
    if obj ~= nil and obj:is_kind_of(comp) then
        cs_remove_comp(self.native, obj.native)
    end
end

function gobj:list_comp(cls)
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

function gobj:get_comp(cls)
    if cls ~= nil and cls:is_kind_of(comp) then
        local native = cs_get_comp(self.native, cls.clsname)
        return cls:new_with(native)
    end

    return nil
end

function gobj:xfrom()
    local native = cs_get_xform(self.native)
    return xform:new_with(native)
end

--)R"