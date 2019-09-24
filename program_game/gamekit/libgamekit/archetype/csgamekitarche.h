#pragma once

#include "cqcbasis.h"

//obj:

struct cs_obj {
    int64_t index;
};

//NOTE: objects that returned as return values need to be cleaned by cs_release().

CQ_C_LINK void cs_retain(struct cs_obj obj);
CQ_C_LINK void cs_release(struct cs_obj obj);

//gk_obj:

struct cs_gk_obj {
    struct cs_obj obj;
};

CQ_C_LINK void cs_dont_destroy_on_load(struct cs_gk_obj gk_obj);
CQ_C_LINK void cs_destroy(struct cs_gk_obj gk_obj);

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
    struct cs_gk_obj gk_obj;
};

CQ_C_LINK struct cs_gobj cs_create_gobj(const char *name);

CQ_C_LINK void cs_set_gobj_name(struct cs_gobj gobj, const char *name);
CQ_C_LINK const char *cs_gobj_name(struct cs_gobj gobj);

CQ_C_LINK void cs_set_gobj_parent(struct cs_gobj gobj, struct cs_gobj parent);
CQ_C_LINK struct cs_gobj cs_gobj_parent(struct cs_gobj gobj);

CQ_C_LINK int32_t cs_child_num(struct cs_gobj gobj);
CQ_C_LINK struct cs_gobj cs_child_at(struct cs_gobj gobj, int32_t index);
CQ_C_LINK void cs_detach_children(struct cs_gobj gobj);

CQ_C_LINK int32_t cs_root_gobj_num(struct cs_scene scene);
CQ_C_LINK struct cs_gobj cs_root_gobj_at(struct cs_scene scene, int32_t index);

//comp:

struct cs_comp {
    struct cs_gk_obj gk_obj;
};

typedef int32_t cs_comp_id;
static const cs_comp_id cs_cid_camera   = 1;
static const cs_comp_id cs_cid_code_beh = 2;
static const cs_comp_id cs_cid_xform    = 3;

CQ_C_LINK struct cs_comp cs_add_comp(struct cs_gobj gobj, cs_comp_id cid);
CQ_C_LINK void cs_remove_comp(struct cs_gobj gobj, cs_comp_id cid);
CQ_C_LINK struct cs_comp cs_gobj_comp(struct cs_gobj gobj, cs_comp_id cid);

CQ_C_LINK struct cs_gobj cs_comp_gobj(struct cs_comp comp);
CQ_C_LINK struct cs_comp cs_comp_brother(struct cs_comp comp, cs_comp_id cid);

//camera:

struct cs_camera {
    cs_comp comp;
};

//code_beh:

struct cs_code_beh {
    cs_comp comp;
};

typedef void (*cs_cb_callback)(const char *event, cs_code_beh beh);
CQ_C_LINK void cs_set_cb_callback(cs_cb_callback callback);

//xform:

struct cs_xform {
    cs_comp comp;
};

CQ_C_LINK struct cs_xform cs_gobj_xform(struct cs_gobj gobj);
CQ_C_LINK struct cs_xform cs_comp_xform(struct cs_comp comp);

CQ_C_LINK void cs_set_xform_xy(struct cs_xform xform, float x, float y);
CQ_C_LINK float cs_xform_x(struct cs_xform xform);
CQ_C_LINK float cs_xform_y(struct cs_xform xform);

CQ_C_LINK void cs_set_xform_parent(struct cs_xform xform, struct cs_xform parent);
CQ_C_LINK struct cs_xform cs_xform_parent(struct cs_xform xform);
