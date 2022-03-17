/* date = November 14th 2021 5:30 pm */

#ifndef HFRENDERER_H
#define HFRENDERER_H

#include "../core/hfapp.h"
#include "../mesh/hfmesh.h"
#include "../math/hfmath.h"
#include "hfshader.h"

void hf_renderer_init(hf_app* app);

void hf_render_mesh(hf_mesh* mesh, hf_shader* shader, hf_transform* transform);

void hf_renderer_destroy(hf_app* app);

#endif //HFRENDERER_H
