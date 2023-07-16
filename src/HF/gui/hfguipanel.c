#include "hfguipanel.h"

hf_gui_panel* hf_current_gui_panel = NULL;

b8 hf_gui_panel_begin(hf_gui_panel* panel, char* text, u32 flags){
    
    panel->title_bar_height = panel->font->glyph_height + 4;//padding TODO
    
    if(flags & HF_MOVEABLE){
        
        //moving
        
        if(!panel->selected){
            panel->selected = ((u32)hf_input_cursor_pos.x > panel->x && (u32)hf_input_cursor_pos.y > panel->y && (u32)hf_input_cursor_pos.x < panel->x + panel->w && (u32)hf_input_cursor_pos.y < panel->y + panel->title_bar_height) && hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
            //panel->select_x = panel->x - (u32)hf_input_cursor_pos.x;
            //panel->select_y = panel->y - (u32)hf_input_cursor_pos.y;
        }else{
            panel->selected = !hf_input_get_mouse_button_up(HF_MOUSE_BUTTON_LEFT);
        }
        
        if(panel->selected){
            //panel->x = (u32)hf_input_cursor_pos.x + panel->select_x;
            //panel->y = (u32)hf_input_cursor_pos.y + panel->select_y;
            
            panel->x += hf_input_get_mouse_movement().x;
            panel->y += hf_input_get_mouse_movement().y;
            
        }
        
        if(!panel->sizing){
            u32 min_x = panel->x + panel->w - 10;
            u32 min_y = panel->y + panel->h - 10;
            u32 max_x = panel->x + panel->w;
            u32 max_y = panel->y + panel->h;
            
            panel->sizing = ((u32)hf_input_cursor_pos.x > min_x && (u32)hf_input_cursor_pos.y > min_y && (u32)hf_input_cursor_pos.x < max_x && (u32)hf_input_cursor_pos.y < max_y) && hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_LEFT);
            
        }else{
            panel->sizing = !hf_input_get_mouse_button_up(HF_MOUSE_BUTTON_LEFT);
        }
        
        if(panel->sizing){
            //panel->x = (u32)hf_input_cursor_pos.x + panel->select_x;
            //panel->y = (u32)hf_input_cursor_pos.y + panel->select_y;
            
            panel->w += hf_input_get_mouse_movement().x;
            panel->h += hf_input_get_mouse_movement().y;
            
        }
        
        
        
    }
    
    
    //if values have not been initialized, do so (only do this when we can move the panel
    /* 
        if((panel->x == 0 && panel->y == 0 && panel->w == 0 && panel->h == 0) || !(flags & HF_MOVEABLE)){
            panel->x = x;
            panel->y = y;
            panel->w = w;
            panel->h = h;
        }
     */
    
    if(panel->x < 0){
        panel->x = 0;
    }
    if(panel->y < 0){
        panel->y = 0;
    }
    
    if(panel->element_spacing == 0)
        panel->element_spacing = 4;
    
    hf_render_rect(panel->x, panel->y, panel->w, panel->h, panel->color);
    
    panel->cursor_pos = (v2f){0, 0};
    hf_current_gui_panel = panel;
    
    if(flags & HF_TITLE_BAR){
        v4f color = {};
        if(panel->title_bar_color.r == 0 && panel->title_bar_color.g == 0 && panel->title_bar_color.b == 0 && panel->title_bar_color.a == 0){
            color = hf_v4f(panel->color.r - 0.1, panel->color.g - 0.1, panel->color.b - 0.1, panel->color.a);
        }else{
            color = panel->title_bar_color;
        }
        
        //hf_render_rect(panel->x - 5, panel->y + (f32)title_bar_height / 2 - (f32)panel->font->glyph_height / 2, 200, panel->font->glyph_height, (v4f){0, 0, 1, 1});
        //panel->cursor_pos = (v2f){5, (f32)title_bar_height / 2 + panel->font->glyph_height / 2};
        hf_render_rect(panel->x, panel->y, panel->w, panel->title_bar_height, color);
        hf_gui_title_text(text, panel->font, 5, ((f32)panel->title_bar_height / 2) + ((f32)panel->font->glyph_height / 2));
        //hf_gui_text(panel->w, 13, 0, text, panel->font, HF_TEXT_CENTERED | HF_TEXT_DONT_USE_SPACING);
        
        
        //sizing indicator
        if(flags & HF_MOVEABLE){
            u32 sizing_size = 10;
            hf_render_rect(panel->x + panel->w - sizing_size, panel->y + panel->h - sizing_size, sizing_size, sizing_size, color);
        }
    }
    
    hf_current_gui_panel->cursor_pos = (v2f){10, panel->title_bar_height};
    
    return 1;
}

hf_gui_panel hf_gui_panel_defaults(){
    hf_gui_panel out = {};
    
    out.color = hf_v4f(0.3, 0.3, 0.3, 1);
    out.title_bar_color = hf_v4f(0.9, 0.5, 0, 1);
    out.element_spacing = 4;
    //out.title_bar_height = 16; //might want to not auto set this tbh
    out.font = &hf_main_font;
    
    return out;
}


b8 hf_gui_panel_end(){
    hf_current_gui_panel = NULL;
    
    return 1;
}

v2f hf_gui_get_cursor_pos(){
    return hf_current_gui_panel->cursor_pos;
}

void hf_gui_set_cursor_pos(v2f in){
    hf_current_gui_panel->cursor_pos = in;
}
