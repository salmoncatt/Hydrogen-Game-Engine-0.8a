/* date = February 26th 2022 10:53 am */

#ifndef HFRENDERER2D_H
#define HFRENDERER2D_H

#include "../core/hfapp.h"
#include "../mesh/hfmesh.h"
#include "../math/hfmath.h"
#include "hfshader.h"

void hf_renderer_init_2d(hf_app* app);

void hf_render_mesh_2d(hf_mesh* mesh, hf_shader* shader, hf_transform* transform);

void hf_renderer_destroy_2d(hf_app* app);

#endif //HFRENDERER2D_H
