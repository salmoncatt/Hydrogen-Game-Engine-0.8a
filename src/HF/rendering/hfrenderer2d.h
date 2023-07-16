/* date = February 26th 2022 10:53 am */

#ifndef HFRENDERER2D_H
#define HFRENDERER2D_H

#include "../core/hfapp.h"
#include "../mesh/hfmesh.h"
#include "../math/hfmath.h"
#include "../gui/hfgui.h"
#include "../text/hf_font.h"
#include "hfshader.h"

extern hf_mesh hf_renderer_quad;
extern hf_shader hf_gui_rect_shader;
extern hf_shader hf_gui_text_shader;

extern hf_font hf_main_font;

void hf_renderer_init_2d(hf_app* app);

void hf_renderer_update_2d();

void hf_set_alpha_blending(b8 in);
void hf_set_depth_test(b8 in);

void hf_render_mesh_2d(hf_mesh* mesh, hf_shader* shader, hf_transform* transform);

void hf_renderer_destroy_2d(hf_app* app);

// NOTE(salmoncatt): pixel coords
void hf_render_rect(u32 x, u32 y, u32 w, u32 h, v4f color);
void hf_render_rect_texture(u32 x, u32 y, u32 w, u32 h, hf_texture* texture);

void hf_render_font(hf_font* font);

#endif //HFRENDERER2D_H
