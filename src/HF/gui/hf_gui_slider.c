#include "hf_gui_slider.h"
#include "hfguipanel.h"

f32 hf_gui_slider(u32 w, u32 h, v4f color, v4f back_color, f32* value, f32 min, f32 max){
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    // NOTE(salmoncatt): screen space (pixel) coords
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_current_gui_panel->cursor_pos.y += h;
    
    
    
    u32 slider_width = w / 5;
    u32 slider_x = ss_x + 1 + ((w - slider_width - 2) * (*value - min) / (max - min));
    u32 slider_y = ss_y + 1;
    
    b8 clicked = 0;
    
    //click in slider to set number
    if((u32)hf_input_cursor_pos.x > ss_x && (u32)hf_input_cursor_pos.y > ss_y && (u32)hf_input_cursor_pos.x < ss_x + w && (u32)hf_input_cursor_pos.y < ss_y + h && hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT)){
        *value = (max - min) * (hf_input_cursor_pos.x - ss_x) / (hf_input_cursor_pos.x - ss_x + w) * 2;
    }
    
    //clicked the slider button thing
    if((u32)hf_input_cursor_pos.x > slider_x && (u32)hf_input_cursor_pos.y > slider_y && (u32)hf_input_cursor_pos.x < slider_x + slider_width && (u32)hf_input_cursor_pos.y < slider_y + h - 2){
        //color = hf_v4f(1, 1, 1, 1);
        clicked = hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
        hf_current_gui_panel->clicked_last_frame = (clicked || hf_current_gui_panel->clicked_last_frame);
        
        
        color = hf_v4f(color.r + 0.1, color.g + 0.1, color.b + 0.1, color.a); //highlight if hovered 
        
    }
    
    
    if(hf_current_gui_panel->clicked_last_frame){
        color = hf_v4f(color.r - 0.1, color.g - 0.1, color.b - 0.1, color.a); //override highlight if actually clicked
    }
    
    if(hf_current_gui_panel->clicked_last_frame){
        f32 value_change = (hf_input_get_mouse_movement().x / w) * (max - min);
        
        if((*value < max && value_change > 0) || (*value > min && value_change < 0)){
            *value += value_change;
        }
    }
    
    *value = hf_min(*value, max);
    *value = hf_max(*value, min);
    
    
    if(hf_input_get_mouse_button_up(HF_MOUSE_BUTTON_LEFT))
        hf_current_gui_panel->clicked_last_frame = 0;
    
    
    
    
    
    
    hf_render_rect(ss_x, ss_y, w, h, back_color);
    hf_render_rect(slider_x, slider_y, slider_width, h - 2, color);
    
    return *value;
}