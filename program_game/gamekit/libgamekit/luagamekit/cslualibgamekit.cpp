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

//gk_obj:

static int32_t cs_dont_destroy_on_load(lua_State *state) {
    cs_gk_obj gk_obj = lua_check<cs_gk_obj>(state, 1);
    cs_dont_destroy_on_load(gk_obj);
    return cq_lua_return_void(state);
}

static int32_t cs_destroy(lua_State *state) {
    cs_gk_obj gk_obj = lua_check<cs_gk_obj>(state, 1);
    cs_destroy(gk_obj);
    return cq_lua_return_void(state);
}

//scene:

static int32_t cs_create_scene(lua_State *state) {
    const char *name = cq_lua_check_string(state, 1);
    cs_scene scene = cs_create_scene(name);
    return lua_return_obj(state, scene);
}

static int32_t cs_scene_name(lua_State *state) {
    cs_scene scene = lua_check<cs_scene>(state, 1);
    const char *name = cs_scene_name(scene);
    return cq_lua_return_string(state, name);
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
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    const char *name = cq_lua_check_string(state, 2);
    
    cs_set_gobj_name(gobj, name);
    
    return cq_lua_return_void(state);
}

static int32_t cs_gobj_name(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    const char *name = cs_gobj_name(gobj);
    return cq_lua_return_string(state, name);
}

static int32_t cs_set_gobj_parent(lua_State *state) {
    cs_gobj gobj   = lua_check<cs_gobj>(state, 1);
    cs_gobj parent = lua_check<cs_gobj>(state, 2);
    
    cs_set_gobj_parent(gobj, parent);
    
    return cq_lua_return_void(state);
}

static int32_t cs_gobj_parent(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_gobj parent = cs_gobj_parent(gobj);
    return lua_return_obj(state, parent);
}

static int32_t cs_child_num(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    int32_t num = cs_child_num(gobj);
    return cq_lua_return_int32(state, num);
}

static int32_t cs_child_at(lua_State *state) {
    cs_gobj gobj  = lua_check<cs_gobj>(state, 1);
    int32_t index = cq_lua_check_int32(state, 2);
    
    cs_gobj child = cs_child_at(gobj, index);
    
    return lua_return_obj(state, child);
}

static int32_t cs_detach_children(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_detach_children(gobj);
    return cq_lua_return_void(state);
}

static int32_t cs_root_gobj_num(lua_State *state) {
    cs_scene scene = lua_check<cs_scene>(state, 1);
    int32_t num = cs_root_gobj_num(scene);
    return cq_lua_return_int32(state, num);
}

static int32_t cs_root_gobj_at(lua_State *state) {
    cs_scene scene = lua_check<cs_scene>(state, 1);
    int32_t index = cq_lua_check_int32(state, 2);
    
    cs_gobj gobj = cs_root_gobj_at(scene, index);
    
    return lua_return_obj(state, gobj);
}

//comp:

static int32_t cs_add_comp(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_cid cid = (cs_cid)cq_lua_check_int32(state, 2);
    
    cs_comp comp = cs_add_comp(gobj, cid);
    
    return lua_return_obj(state, comp);
}

static int32_t cs_remove_comp(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_cid cid = (cs_cid)cq_lua_check_int32(state, 2);
    
    cs_remove_comp(gobj, cid);
    
    return cq_lua_return_void(state);
}

static int32_t cs_gobj_comp(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_cid cid = (cs_cid)cq_lua_check_int32(state, 2);
    
    cs_comp comp = cs_gobj_comp(gobj, cid);
    
    return lua_return_obj(state, comp);
}

static int32_t cs_comp_gobj(lua_State *state) {
    cs_comp comp = lua_check<cs_comp>(state, 1);
    cs_gobj gobj = cs_comp_gobj(comp);
    return lua_return_obj(state, gobj);
}

static int32_t cs_comp_brother(lua_State *state) {
    cs_comp comp = lua_check<cs_comp>(state, 1);
    cs_cid cid = (cs_cid)cq_lua_check_int32(state, 2);
    
    cs_comp brother = cs_comp_brother(comp, cid);
    
    return lua_return_obj(state, brother);
}

//xform:

static int32_t cs_gobj_xform(lua_State *state) {
    cs_gobj gobj = lua_check<cs_gobj>(state, 1);
    cs_xform xform = cs_gobj_xform(gobj);
    return lua_return_obj(state, xform);
}

static int32_t cs_comp_xform(lua_State *state) {
    cs_comp comp = lua_check<cs_comp>(state, 1);
    cs_xform xform = cs_comp_xform(comp);
    return lua_return_obj(state, xform);
}

static int32_t cs_set_xform_xy(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    float x = cq_lua_check_float(state, 2);
    float y = cq_lua_check_float(state, 3);
    
    cs_set_xform_xy(xform, x, y);
    
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
    cs_xform xform = lua_check<cs_xform>(state, 1);
    cs_xform parent = lua_check<cs_xform>(state, 2);
    
    cs_set_xform_parent(xform, parent);
    
    return cq_lua_return_void(state);
}

static int32_t cs_xform_parent(lua_State *state) {
    cs_xform xform = lua_check<cs_xform>(state, 1);
    cs_xform parent = cs_xform_parent(xform);
    return lua_return_obj(state, parent);
}

static void on_event(const char *express, cs_code_beh beh) {
    char buffer[64];
    sprintf(buffer, express, *(int64_t *)&beh);
    cq_lua_do_string(buffer);
}

static void awake     (cs_code_beh b) { on_event("cs_on_code_beh_awake(%ld)"     , b); }
static void start     (cs_code_beh b) { on_event("cs_on_code_beh_start(%ld)"     , b); }
static void update    (cs_code_beh b) { on_event("cs_on_code_beh_update(%ld)"    , b); }
static void on_destroy(cs_code_beh b) { on_event("cs_on_code_beh_on_destroy(%ld)", b); }

static void set_code_beh_callback() {
    
    cs_code_beh_event event = {0}; {
        
        event.awake      = awake     ;
        event.start      = start     ;
        event.update     = update    ;
        event.on_destroy = on_destroy;
    }
    cs_set_code_beh_callback(&event);
}

void cs_lua_load_lib_gamekit() {
    
    set_code_beh_callback();

#define register_func(name) cq_lua_register_func(#name, name)

    //obj:
    register_func(cs_retain );
    register_func(cs_release);

    //gk_obj:
    register_func(cs_dont_destroy_on_load);
    register_func(cs_destroy);

    //scene:
    register_func(cs_create_scene);
    register_func(cs_scene_name  );
    register_func(cs_load_scene  );
    register_func(cs_active_scene);

    //gobj:
    register_func(cs_create_gobj);

    register_func(cs_set_gobj_name);
    register_func(cs_gobj_name    );

    register_func(cs_set_gobj_parent);
    register_func(cs_gobj_parent    );

    register_func(cs_child_num      );
    register_func(cs_child_at       );
    register_func(cs_detach_children);

    register_func(cs_root_gobj_num);
    register_func(cs_root_gobj_at );

    //comp:
    register_func(cs_add_comp   );
    register_func(cs_remove_comp);
    register_func(cs_gobj_comp  );

    register_func(cs_comp_gobj   );
    register_func(cs_comp_brother);

    //xform:
    register_func(cs_gobj_xform);
    register_func(cs_comp_xform);

    register_func(cs_set_xform_xy);
    register_func(cs_xform_x     );
    register_func(cs_xform_y     );

    register_func(cs_set_xform_parent);
    register_func(cs_xform_parent    );
}
