--LUA R"R(

if not cs_retain then

    -- obj:
    function cs_retain(obj) end
    function cs_release(obj) end

    -- gk_obj:
    function cs_dont_destroy_on_load(gk_obj) end
    function cs_destroy(gk_obj) end

    -- scene_mgr:
    function cs_create_scene(name) end
    function cs_scene_name(scene) end
    function cs_load_scene(name) end
    function cs_active_scene() end

    -- gobj:
    function cs_create_gobj(name) end
    function cs_set_gobj_name(gobj, name) end
    function cs_gobj_name(gobj) end

    function cs_set_gobj_parent(gobj, parent) end
    function cs_gobj_parent(gobj) end

    function cs_child_num(gobj) end
    function cs_child_at(gobj, index) end
    function cs_detach_children(gobj) end

    function cs_add_comp(gobj, name) end
    function cs_remove_comp(gobj, name) end
    function cs_gobj_comp(gobj, name) end

    function cs_gobj_xform(gobj) end

    -- scene:
    function cs_root_gobj_num(scene) end
    function cs_root_gobj_at(scene, index) end

    -- comp:
    function cs_comp_gobj(comp) end
    function cs_comp_brother(comp, name) end
    function cs_comp_xform(comp) end

    -- xform:
    function cs_set_xform_xy(xform, x, y) end
    function cs_xform_x(xform) end
    function cs_xform_y(xform) end

    function cs_set_xform_parent(xform, parent) end
    function cs_xform_parent(xform) end

end

--)R"