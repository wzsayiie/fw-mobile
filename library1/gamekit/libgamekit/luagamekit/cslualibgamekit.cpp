#include "cslualibgamekit.h"
#include "csgamekitarche.h"
#include <cstdio>

template<class T> T lua_check(lua_State *state, int32_t index) {
    T obj = { cq_lua_check_int64(state, index) };
    return obj;
}

template<class T> int32_t lua_return_obj(lua_State *state, T obj) {
    return cq_lua_return_int64(state, *(int64_t *)&obj);
}

//obj:

static int32_t cs_retain(lua_State *state) {
    cs_obj obj = lua_check<cs_obj>(state, 1);
    cs_retain(obj);
    return cq_lua_return_void(state);
}

static int32_t cs_release(lua_State *state) {
    cs_obj obj = lua_check<cs_obj>(state, 1);
    cs_release(obj);
    return cq_lua_return_void(state);
}

//node:

static int32_t cs_dont_destroy_on_load(lua_State *state) {
    cs_node node = lua_check<cs_node>(state, 1);
    cs_dont_destroy_on_load(node);
    return cq_lua_return_void(state);
}

static int32_t cs_destroy(lua_State *state) {
    cs_node node = lua_check<cs_node>(state, 1);
    cs_destroy(node);
    return cq_lua_return_void(state);
}

//scene_mgr:

static int32_t cs_create_scene(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cs_scene scene = cs_create_scene(name);
    return lua_return_obj(state, scene);
}

static int32_t cs_load_scene(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cs_load_scene(name);
    return cq_lua_return_void(state);
}

static int32_t cs_active_scene(lua_State *state) {
    cs_scene scene = cs_active_scene();
    return lua_return_obj(state, scene);
}

//gobj:

static int32_t cs_create_gobj(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cs_gobj gobj = cs_create_gobj(name);
    return lua_return_obj(state, gobj);
}

static int32_t cs_set_gobj_name(lua_State *state) {
    cs_gobj     gobj = lua_check<cs_gobj> (state, 1);
    const char *name = cq_lua_check_string(state, 2);

    cs_set_gobj_name(gobj, name);

    return cq_lua_return_void(state);
}

static int32_t cs_gobj_name(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    const char *name = cs_gobj_name(gobj);
    return cq_lua_return_string(state, name);
}

//scene:

static int32_t cs_scene_name(lua_State *state) {
    cs_scene scene = lua_check<cs_scene>(state, 1);
    const char *name = cs_scene_name(scene);
    return cq_lua_return_string(state, name);
}

static int32_t cs_list_root_begin(lua_State *state) {
    cs_scene scene = lua_check<cs_scene>(state, 1);
    int32_t num = cs_list_root_begin(scene);
    return cq_lua_return_int32(state, num);
}

static int32_t cs_list_root_at(lua_State *state) {
    int32_t index = cq_lua_check_int32(state, 1);
    cs_gobj gobj = cs_list_root_at(index);
    return lua_return_obj(state, gobj);
}

static int32_t cs_list_root_end(lua_State *state) {
    cs_list_root_end();
    return cq_lua_return_void(state);
}

//comp:

static int32_t cs_comp_gobj(lua_State *state) {
    cs_comp comp = lua_check<cs_comp>(state, 1);
    cs_gobj gobj = cs_comp_gobj(comp);
    return lua_return_obj(state, gobj);
}

static int32_t cs_add_comp(lua_State *state) {
    cs_gobj     gobj = lua_check<cs_gobj> (state, 1);
    const char *cls  = cq_lua_check_string(state, 2);

    cs_comp comp = cs_add_comp(gobj, cls);
    
    return lua_return_obj(state, comp);
}

static int32_t cs_remove_comp(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_comp comp = lua_check<cs_comp>(state, 2);

    cs_remove_comp(gobj, comp);

    return cq_lua_return_void(state);
}

static int32_t cs_list_comp_begin(lua_State *state) {
    cs_node     node = lua_check<cs_node> (state, 1);
    const char *cls  = cq_lua_check_string(state, 2);
    
    int32_t num = cs_list_comp_begin(node, cls);
    
    return cq_lua_check_int32(state, num);
}

static int32_t cs_list_comp_at(lua_State *state) {
    int32_t index = cq_lua_check_int32(state, 1);
    cs_comp comp = cs_list_comp_at(index);
    return lua_return_obj(state, comp);
}

static int32_t cs_list_comp_end(lua_State *state) {
    cs_list_comp_end();
    return cq_lua_return_void(state);
}

static int32_t cs_get_comp(lua_State *state) {
    cs_node     node = lua_check<cs_node> (state, 1);
    const char *cls  = cq_lua_check_string(state, 2);

    cs_comp comp = cs_get_comp(node, cls);

    return lua_return_obj(state, comp);
}

//xform:

static int32_t cs_get_xform(lua_State *state) {
    cs_node node = lua_check<cs_node>(state, 1);
    cs_xform xform = cs_get_xform(node);
    return lua_return_obj(state, xform);
}

static int32_t cs_set_xform_pos(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    float x = cq_lua_check_float(state, 2);
    float y = cq_lua_check_float(state, 3);

    cs_set_xform_pos(xform, x, y);

    return cq_lua_return_void(state);
}

static int32_t cs_xform_x(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    float x = cs_xform_x(xform);
    return cq_lua_return_float(state, x);
}

static int32_t cs_xform_y(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    float y = cs_xform_y(xform);
    return cq_lua_return_float(state, y);
}

static int32_t cs_set_xform_parent(lua_State *state) {
    cs_xform xform  = lua_check<cs_xform>(state, 1);
    cs_xform parent = lua_check<cs_xform>(state, 2);

    cs_set_xform_parent(xform, parent);

    return cq_lua_return_void(state);
}

static int32_t cs_xform_parent(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    cs_xform parent = cs_xform_parent(xform);
    return lua_return_obj(state, parent);
}

static int32_t cs_list_child_begin(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    int32_t num = cs_list_child_begin(xform);
    return cq_lua_return_int32(state, num);
}

static int32_t cs_list_child_at(lua_State *state) {
    int32_t index = cq_lua_check_int32(state, 1);
    cs_xform xform = cs_list_child_at(index);
    return lua_return_obj(state, xform);
}

static int32_t cs_list_child_end(lua_State *state) {
    cs_list_child_end();
    return cq_lua_return_void(state);
}

static int32_t cs_detach_children(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    cs_detach_children(xform);
    return cq_lua_return_void(state);
}

//script callback:

static void on_script_callback(const char *event, cs_script script) {

    const char *express = "cs_on_script_callback(\"%s\", %lld)";
    int64_t index = *(int64_t *)&script;

    char buffer[64];
    sprintf(buffer, express, event, index);
    cq_lua_do_string(buffer);
}

//load lib:

void cs_lua_load_lib_gamekit() {

    cs_set_script_callback(on_script_callback);

#define register_func(name) cq_lua_register_func(#name, name)

    //obj:
    register_func(cs_retain );
    register_func(cs_release);

    //node:
    register_func(cs_dont_destroy_on_load);
    register_func(cs_destroy);

    //scene_mgr:
    register_func(cs_create_scene);
    register_func(cs_load_scene  );
    register_func(cs_active_scene);

    //gobj:
    register_func(cs_create_gobj);

    register_func(cs_set_gobj_name);
    register_func(cs_gobj_name    );

    //scene:
    register_func(cs_scene_name);
    
    register_func(cs_list_root_begin);
    register_func(cs_list_root_at   );
    register_func(cs_list_root_end  );

    //comp:
    register_func(cs_comp_gobj);
    
    register_func(cs_add_comp   );
    register_func(cs_remove_comp);
    
    register_func(cs_list_comp_begin);
    register_func(cs_list_comp_at   );
    register_func(cs_list_comp_end  );

    register_func(cs_get_comp);

    //xform:
    register_func(cs_get_xform);

    register_func(cs_set_xform_pos);
    register_func(cs_xform_x      );
    register_func(cs_xform_y      );

    register_func(cs_set_xform_parent);
    register_func(cs_xform_parent    );
    
    register_func(cs_list_child_begin);
    register_func(cs_list_child_at   );
    register_func(cs_list_child_end  );
    
    register_func(cs_detach_children);
}
