--LUA R"R(

scene = class("scene", obj, {
})

function scene:name()
    return cs_scene_name(scene.native)
end

function scene:root_gobj_num()
    return cs_root_gobj_num(self.native)
end

function scene:root_gobj_at(index)
    local native = cs_root_gobj_at(self.native, index)
    return gobj:new_retain(native)
end

--)R"