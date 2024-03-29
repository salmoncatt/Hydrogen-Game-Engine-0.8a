/* date = November 14th 2021 5:30 pm */

#ifndef HFRENDERER_H
#define HFRENDERER_H

#include "../core/hfapp.h"
#include "../mesh/hfmesh.h"
#include "../math/hfmath.h"
#include "hfshader.h"
#include "../camera/hfdebugcamera.h"

extern hf_debug_camera hf_renderer_cam;

extern m4f hf_renderer_proj_mat;
extern m4f hf_renderer_ortho;
extern m4f hf_renderer_pixel_ortho;

extern b8 hf_renderer_wireframe_active;
extern f32 hf_aspect_ratio;
extern u32 hf_window_w;
extern u32 hf_window_h;

extern hf_shader hf_default_shader;


// NOTE(salmoncatt): i guess having these here tells amd and nvidia to select most powerful gpu for this application, needs testing tho
//DWORD NvOptimusEnablement = 1;
//int AmdPowerXpressRequestHighPerformance = 1;

void hf_renderer_init(hf_app* app);

void hf_renderer_update(hf_app* app);

void hf_render_mesh(hf_mesh* mesh, hf_shader* shader, hf_transform* transform);

void hf_renderer_destroy(hf_app* app);

void hf_renderer_toggle_wireframe();
void hf_renderer_set_wireframe_mode(b8 mode);

//v2f hf_renderer_get_window_size();

#endif //HFRENDERER_H
