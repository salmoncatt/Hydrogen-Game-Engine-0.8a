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

void hf_renderer_init(hf_app* app);

void hf_renderer_update(hf_app* app);

void hf_render_mesh(hf_mesh* mesh, hf_shader* shader, hf_transform* transform);

void hf_renderer_destroy(hf_app* app);

void hf_renderer_toggle_wireframe();
void hf_renderer_set_wireframe_mode(b8 mode);

#endif //HFRENDERER_H
