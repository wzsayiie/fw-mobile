--LUA R"R(

scene = class("scene", obj, {
})

function scene:name()
    return cs_scene_name(scene.native)
end

function scene:roots()
    local set = {}

    local num = cs_list_root_begin(self.native)
    for it = 0, num - 1 do
        local native = cs_list_root_at(it)
        table.insert(set, gobj:new_with(native))
    end
    cs_list_root_end()

    return set
end

--)R"