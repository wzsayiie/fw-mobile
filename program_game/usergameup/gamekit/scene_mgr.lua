--LUA R"R(

scene_mgr = class("scene_mgr", obj, {
})

function scene_mgr:create_scene(name)
    local native = cs_create_scene(name)
    -- NOTE: do not retain reference count once again.
    return scene:new_with(native)
end

function scene_mgr:load_scene(name)
    cs_load_scene(name)
end

function scene_mgr:active_scene()
    local native = cs_active_scene()
    return scene:new_retain(native)
end

--)R"