#include "hfguipanel.h"

hf_gui_panel* hf_current_gui_panel = NULL;

b8 hf_gui_panel_begin(hf_gui_panel* panel, u32 x, u32 y, u32 w, u32 h, u32 flags){
    hf_render_rect(x, y, w, h, panel->color);
    
    if(flags && HF_TITLE_BAR){
        hf_render_rect(x, y, w, 30, hf_v4f(panel->color.r - 0.1, panel->color.g - 0.1, panel->color.b - 0.1, panel->color.a));
    }
    
    panel->x = x;
    panel->y = y;
    panel->w = w;
    panel->h = h;
    
    hf_current_gui_panel = panel;
    
    return 1;
}

b8 hf_gui_panel_end(){
    hf_current_gui_panel = NULL;
    
    return 1;
}

b8 hf_gui_button(u32 x, u32 y, u32 w, u32 h, v4f color){
    
    // NOTE(salmoncatt): screen space (pixel) coords
    u32 ss_x = x + hf_current_gui_panel->x;
    u32 ss_y = y + hf_current_gui_panel->y;
    
    b8 clicked = 0;
    
    if((u32)hf_input_cursor_pos.x > ss_x && (u32)hf_input_cursor_pos.y > ss_y && (u32)hf_input_cursor_pos.x < ss_x + w && (u32)hf_input_cursor_pos.y < ss_y + h){
        //color = hf_v4f(1, 1, 1, 1);
        color = hf_v4f(color.r + 0.1, color.g + 0.1, color.b + 0.1, color.a); //highlight if hovered
        
        //if click return 1
        clicked = hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_0);
    }
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    
    
    //clicked is only returned if hovered and clicked on
    return clicked;
}