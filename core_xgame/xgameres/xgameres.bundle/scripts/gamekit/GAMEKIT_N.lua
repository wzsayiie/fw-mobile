--LUA R"R(

if not cs_retain then

    -- obj:
    function cs_retain(obj) end
    function cs_release(obj) end

    -- node:
    function cs_dont_destroy_on_load(node) end
    function cs_destroy(node) end

    -- scene_mgr:
    function cs_create_scene(name) end
    function cs_load_scene(name) end
    function cs_active_scene() end

    -- gobj:
    function cs_create_gobj(name) end

    function cs_set_gobj_name(gobj, name) end
    function cs_gobj_name(gobj) end

    -- scene:
    function cs_scene_name(scene) end

    function cs_list_root_begin(scene) end
    function cs_list_root_at(index) end
    function cs_list_root_end() end

    -- comp:
    function cs_comp_gobj(comp) end

    function cs_add_comp(gobj, cls) end
    function cs_remove_comp(gobj, comp) end

    function cs_list_comp_begin(node, cls) end
    function cs_list_comp_at(index) end
    function cs_list_comp_end() end

    function cs_get_comp(node, cls) end

    -- xform:
    function cs_get_xform(node) end

    function cs_set_xform_pos(xform, x, y) end
    function cs_xform_x(xform) end
    function cs_xform_y(xform) end

    function cs_set_xform_parent(xform, parent) end
    function cs_xform_parent(xform) end

    function cs_list_child_begin(xform) end
    function cs_list_child_at(index) end
    function cs_list_child_end() end

    function cs_detach_children(xform) end

end

--)R"