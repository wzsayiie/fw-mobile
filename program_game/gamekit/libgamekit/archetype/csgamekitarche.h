#pragma once

#include "cqcbasis.h"

//object reference count:

CQ_C_LINK void cs_retain (int64_t object);
CQ_C_LINK void cs_release(int64_t object);

//component:

CQ_C_LINK int64_t cs_comp_gobj     (int64_t comp);
CQ_C_LINK int64_t cs_comp_brother  (int64_t comp, int32_t index);
CQ_C_LINK int64_t cs_comp_transform(int64_t comp);
CQ_C_LINK void    cs_comp_destroy  (int64_t comp);

//game object:

CQ_C_LINK int64_t cs_create_gobj (const char *name);
CQ_C_LINK void    cs_gobj_keep   (int64_t gobj);
CQ_C_LINK void    cs_gobj_destroy(int64_t gobj);

CQ_C_LINK void        cs_gobj_set_name(int64_t gobj, const char *name);
CQ_C_LINK const char *cs_gobj_name    (int64_t gobj);

CQ_C_LINK void    cs_gobj_set_parent (int64_t gobj, int64_t parent);
CQ_C_LINK int64_t cs_gobj_parent     (int64_t gobj);
CQ_C_LINK int32_t cs_gobj_child_num  (int64_t gobj);
CQ_C_LINK int64_t cs_gobj_child_at   (int64_t gobj, int32_t index);
CQ_C_LINK void    cs_gobj_de_children(int64_t gobj);

static const char *const CS_COMP_IDEN_CAMERA    = "camera"   ;
static const char *const CS_COMP_IDEN_CODE_BEH  = "code_beh" ;
static const char *const CS_COMP_IDEN_TRANSFORM = "transform";

CQ_C_LINK int64_t cs_gobj_add_comp   (int64_t gobj, const char *iden);
CQ_C_LINK void    cs_gobj_remove_comp(int64_t gobj, const char *iden);
CQ_C_LINK int64_t cs_gobj_comp       (int64_t gobj, const char *iden);
CQ_C_LINK int64_t cs_gobj_transform  (int64_t gobj);

//scene:

CQ_C_LINK const char *cs_scene_name         (int64_t scene);
CQ_C_LINK int32_t     cs_scene_root_gobj_num(int64_t scene);
CQ_C_LINK int64_t     cs_scene_root_gobj_at (int64_t scene, int32_t index);

//scene manager:

CQ_C_LINK int64_t cs_create_scene(const char *name);
CQ_C_LINK void    cs_load_scene  (const char *name);
CQ_C_LINK int64_t cs_active_scene(void);

//transform:

CQ_C_LINK void  cs_transform_set_xy(int64_t transform, float x, float y);
CQ_C_LINK float cs_transform_x     (int64_t transform);
CQ_C_LINK float cs_transform_y     (int64_t transform);

CQ_C_LINK void    cs_transform_set_parent(int64_t transform, int64_t parent);
CQ_C_LINK int64_t cs_transform_parent    (int64_t transform);
