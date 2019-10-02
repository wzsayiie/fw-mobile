#pragma once

#include "cqcbasis.h"

//obj:

struct cs_obj {
    int64_t index;
};

//NOTE: objects that returned as return values need to be cleaned by cs_release().
CQ_C_LINK void cs_retain(struct cs_obj obj);
CQ_C_LINK void cs_release(struct cs_obj obj);

//node:

struct cs_node {
    struct cs_obj obj;
};

//$node should be a cs_gobj or cs_comp.
CQ_C_LINK void cs_dont_destroy_on_load(struct cs_node node);
CQ_C_LINK void cs_destroy(struct cs_node node);

//scene:

struct cs_scene {
    struct cs_obj obj;
};

CQ_C_LINK struct cs_scene cs_create_scene(const char *name);
CQ_C_LINK const char *cs_scene_name(struct cs_scene scene);
CQ_C_LINK void cs_load_scene(const char *name);
CQ_C_LINK struct cs_scene cs_active_scene(void);

//gobj:

struct cs_gobj {
    struct cs_node node;
};

CQ_C_LINK struct cs_gobj cs_create_gobj(const char *name);

CQ_C_LINK void cs_set_gobj_name(struct cs_gobj gobj, const char *name);
CQ_C_LINK const char *cs_gobj_name(struct cs_gobj gobj);

CQ_C_LINK int32_t cs_list_root_begin(struct cs_scene scene);
CQ_C_LINK struct cs_gobj cs_list_root_at(int32_t index);
CQ_C_LINK void cs_list_root_end(void);

//comp:

struct cs_comp {
    struct cs_node node;
};

CQ_C_LINK struct cs_gobj cs_comp_gobj(struct cs_comp comp);

CQ_C_LINK struct cs_comp cs_add_comp(struct cs_gobj gobj, const char *cls);
CQ_C_LINK void cs_remove_comp(struct cs_gobj gobj, struct cs_comp comp);

//$node should be a cs_gobj or cs_comp.
CQ_C_LINK int32_t cs_list_comp_begin(struct cs_node node, const char *cls);
CQ_C_LINK struct cs_comp cs_list_comp_at(int32_t index);
CQ_C_LINK void cs_list_comp_end(void);

CQ_C_LINK struct cs_comp cs_get_comp(struct cs_node node, const char *cls);

//camera:

struct cs_camera {
    cs_comp comp;
};

//script:

struct cs_script {
    cs_comp comp;
};

typedef void (*cs_script_callback_t)(const char *event, cs_script script);
CQ_C_LINK void cs_set_script_callback(cs_script_callback_t callback);

//xform:

struct cs_xform {
    cs_comp comp;
};

//$node should be a cs_gobj or cs_comp.
CQ_C_LINK struct cs_xform cs_get_xform(struct cs_node node);

CQ_C_LINK void cs_set_xform_pos(struct cs_xform xform, float x, float y, float z);
CQ_C_LINK float cs_xform_x(struct cs_xform xform);
CQ_C_LINK float cs_xform_y(struct cs_xform xform);
CQ_C_LINK float cs_xform_z(struct cs_xform xform);

CQ_C_LINK void cs_set_xform_parent(struct cs_xform xform, struct cs_xform parent);
CQ_C_LINK struct cs_xform cs_xform_parent(struct cs_xform xform);

CQ_C_LINK int32_t cs_list_child_begin(struct cs_xform xform);
CQ_C_LINK struct cs_xform cs_list_child_at(int32_t index);
CQ_C_LINK void cs_list_child_end(void);

CQ_C_LINK void cs_detach_children(struct cs_xform);
