#include "hfguipanel.h"

void hf_gui_image(u32 w, u32 h, hf_texture* texture){
    // NOTE(salmoncatt): screen space (pixel) coords
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_render_rect_texture(ss_x, ss_y, w, h, texture);
    
    hf_current_gui_panel->cursor_pos.y += h;
    
}