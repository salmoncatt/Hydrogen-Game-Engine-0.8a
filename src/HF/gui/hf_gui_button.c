#include "hfguipanel.h"

b8 hf_gui_button(u32 w, u32 h, v4f color){
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    // NOTE(salmoncatt): screen space (pixel) coords
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_current_gui_panel->cursor_pos.y += h;
    
    b8 clicked = 0;
    
    if((u32)hf_input_cursor_pos.x > ss_x && (u32)hf_input_cursor_pos.y > ss_y && (u32)hf_input_cursor_pos.x < ss_x + w && (u32)hf_input_cursor_pos.y < ss_y + h){
        //color = hf_v4f(1, 1, 1, 1);
        clicked = hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
        hf_current_gui_panel->clicked_last_frame = (clicked || hf_current_gui_panel->clicked_last_frame);
        
        if(hf_current_gui_panel->clicked_last_frame)
            color = hf_v4f(color.r - 0.1, color.g - 0.1, color.b - 0.1, color.a);
        else
            color = hf_v4f(color.r + 0.1, color.g + 0.1, color.b + 0.1, color.a); //highlight if hovered 
        
    }
    
    if(hf_input_get_mouse_button_up(HF_MOUSE_BUTTON_LEFT))
        hf_current_gui_panel->clicked_last_frame = 0;
    
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    //hf_gui_text(x + 10, y + h - h / 2 + 15 / 2, 100, 15, 0, text, hf_current_gui_panel->font);
    
    //clicked is only returned if hovered and clicked on
    return clicked;
}

b8 hf_gui_button_text(u32 w, u32 h, v4f color, char* text){
    b8 clicked = hf_gui_button(w, h, color);
    
    hf_gui_title_text(text, hf_current_gui_panel->font, hf_current_gui_panel->cursor_pos.x + w / 2 - hf_font_get_bitmap_length(hf_current_gui_panel->font, text) / 2, hf_current_gui_panel->cursor_pos.y - h / 2 + ((f32)hf_current_gui_panel->font->glyph_height / 2));
    
    return clicked;
}



/* 
b8 hf_gui_button_smart(u32 w, u32 h, v4f color, char* text, b8* pressed_last){
    
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    b8 clicked = 0;
    
    if((u32)hf_input_cursor_pos.x > ss_x && (u32)hf_input_cursor_pos.y > ss_y && (u32)hf_input_cursor_pos.x < ss_x + w && (u32)hf_input_cursor_pos.y < ss_y + h){
        //color = hf_v4f(1, 1, 1, 1);
        clicked = hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
        
        color = hf_v4f(color.r + 0.1, color.g + 0.1, color.b + 0.1, color.a); //highlight if hovered 
        
    }
    
    hf_current_gui_panel->cursor_pos.y += h + hf_current_gui_panel->element_spacing;
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    //hf_gui_text(x + 10, y + h - h / 2 + 15 / 2, 100, 15, 0, text, hf_current_gui_panel->font);
    
    //clicked is only returned if hovered and clicked on
    return clicked;
}

b8 hf_gui_button_text_simple(u32 w, u32 h, v4f color, char* text){
    
}

b8 hf_gui_button_text_advanced(u32 w, u32 h, v4f color, char* normal, char* hovered, char* pressed){
    
}
 */