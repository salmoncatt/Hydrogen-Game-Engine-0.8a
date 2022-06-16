#include "hfguipanel.h"

hf_gui_panel* hf_current_gui_panel = NULL;

b8 hf_gui_panel_begin(hf_gui_panel* panel, u32 x, u32 y, u32 w, u32 h, u32 flags, u32 title_bar_height){
    
    if(flags & HF_MOVEABLE){
        if(!panel->selected){
            panel->selected = ((u32)hf_input_cursor_pos.x > panel->x && (u32)hf_input_cursor_pos.y > panel->y && (u32)hf_input_cursor_pos.x < panel->x + panel->w && (u32)hf_input_cursor_pos.y < panel->y + title_bar_height) && hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
        }else{
            panel->selected = !hf_input_get_mouse_button_up(HF_MOUSE_BUTTON_LEFT);
        }
        
        if(panel->selected){
            panel->x += hf_input_get_mouse_movement().x;
            panel->y += hf_input_get_mouse_movement().y;
        }
    }
    
    //if values have not been initialized, do so (only do this when we can move the panel
    if((panel->x == 0 && panel->y == 0 && panel->w == 0 && panel->h == 0) || !(flags & HF_MOVEABLE)){
        panel->x = x;
        panel->y = y;
        panel->w = w;
        panel->h = h;
    }
    
    hf_render_rect(panel->x, panel->y, panel->w, panel->h, panel->color);
    
    if(flags & HF_TITLE_BAR){
        hf_render_rect(panel->x, panel->y, panel->w, title_bar_height, hf_v4f(panel->color.r - 0.1, panel->color.g - 0.1, panel->color.b - 0.1, panel->color.a));
    }
    
    
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
        clicked = hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
    }
    
    /* 
        if(hf_input_get_mouse_button(HF_MOUSE_BUTTON_LEFT))
            color = hf_v4f(color.r - 0.1, color.g - 0.1, color.b - 0.1, color.a);
     */
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    
    
    //clicked is only returned if hovered and clicked on
    return clicked;
}

void hf_gui_image(u32 x, u32 y, u32 w, u32 h, hf_texture* texture){
    // NOTE(salmoncatt): screen space (pixel) coords
    u32 ss_x = x + hf_current_gui_panel->x;
    u32 ss_y = y + hf_current_gui_panel->y;
    
    hf_render_rect_texture(ss_x, ss_y, w, h, texture);
}