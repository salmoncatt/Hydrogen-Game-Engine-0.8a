#include "hfguipanel.h"

hf_gui_panel* hf_current_gui_panel = NULL;

b8 hf_gui_panel_begin(hf_gui_panel* panel, char* text, u32 x, u32 y, u32 w, u32 h, u32 flags, u32 title_bar_height){
    
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
    
    if(panel->element_spacing == 0)
        panel->element_spacing = 10;
    
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
        
        hf_render_rect(panel->x, panel->y, panel->w, title_bar_height, color);
        panel->cursor_pos = (v2f){5, title_bar_height};
        hf_gui_text(panel->w, 18, 0, text, panel->font, HF_TEXT_BOTTOM | HF_TEXT_DONT_USE_SPACING);
    }
    
    hf_current_gui_panel->cursor_pos = (v2f){10, title_bar_height};
    
    return 1;
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



//----------------Buttons-----------------



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
        
        color = hf_v4f(color.r + 0.1, color.g + 0.1, color.b + 0.1, color.a); //highlight if hovered 
        
    }
    
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    //hf_gui_text(x + 10, y + h - h / 2 + 15 / 2, 100, 15, 0, text, hf_current_gui_panel->font);
    
    //clicked is only returned if hovered and clicked on
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








//-------------------Image-------------

void hf_gui_image(u32 w, u32 h, hf_texture* texture){
    // NOTE(salmoncatt): screen space (pixel) coords
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_render_rect_texture(ss_x, ss_y, w, h, texture);
    
    hf_current_gui_panel->cursor_pos.y += h;
    
}




//-------------------Rect-------------

void hf_gui_rect(u32 w, u32 h, v4f color){
    // NOTE(salmoncatt): screen space (pixel) coords
    hf_current_gui_panel->cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    u32 ss_x = hf_current_gui_panel->cursor_pos.x + hf_current_gui_panel->x;
    u32 ss_y = hf_current_gui_panel->cursor_pos.y + hf_current_gui_panel->y;
    
    hf_render_rect(ss_x, ss_y, w, h, color);
    
    hf_current_gui_panel->cursor_pos.y += h;
    
}





//------------------Text-----------------

void hf_gui_text(u32 max_w, u32 height, b8 centered, char* text, hf_font* font, u32 render_type){
    u32 length = hf_strlen(text);
    //f32 scale_ratio = (f32)(height) / (f32)(font->size);
    f32 scale_ratio = 1;
    f32 scaled_height = font->glyph_height * scale_ratio;
    //height = (u32)(scaled_height);
    
    v2f screen_pos = (v2f){hf_current_gui_panel->x + hf_current_gui_panel->cursor_pos.x, hf_current_gui_panel->y + hf_current_gui_panel->cursor_pos.y};
    v2f cursor_pos;
    
    if(render_type & HF_TEXT_CENTERED){
        cursor_pos = (v2f){screen_pos.x, screen_pos.y + height / 2};
    }else if(render_type & HF_TEXT_BOTTOM){
        cursor_pos = screen_pos;
    }
    
    
    if(!(render_type & HF_TEXT_DONT_USE_SPACING))
        cursor_pos.y += hf_current_gui_panel->element_spacing;
    
    hf_render_rect(cursor_pos.x, cursor_pos.y - height, max_w, height, (v4f){0, 0, 0, 1});
    hf_render_rect(cursor_pos.x + 5, cursor_pos.y - scaled_height, max_w, scaled_height, (v4f){0.9f, 0.7f, 0, 0.5f});
    //printf("%u\n", font->descender);
    hf_current_gui_panel->cursor_pos.y += scaled_height;
    
    for(u32 i = 0; i < length; i++){
        char current_char = text[i];
        u32 char_num = (u32)(current_char);
        
        v2f char_size = (v2f){font->characters[char_num].size.x * scale_ratio, font->characters[char_num].size.y * scale_ratio};
        
        v2f char_pos = (v2f){cursor_pos.x + font->characters[char_num].bitmap_left_top.x * scale_ratio, cursor_pos.y - font->characters[char_num].bitmap_left_top.y * scale_ratio};
        
        cursor_pos.x += font->characters[char_num].advance.x * scale_ratio;
        cursor_pos.y += font->characters[char_num].advance.y * scale_ratio;
        
        
        if(!char_size.x || !char_size.y){
            continue;
        }
        
        hf_array_push_back(font->vertices, char_pos.x); hf_array_push_back(font->vertices, char_pos.y);
        hf_array_push_back(font->vertices, char_pos.x); hf_array_push_back(font->vertices, char_pos.y + char_size.y);
        hf_array_push_back(font->vertices, char_pos.x + char_size.x); hf_array_push_back(font->vertices, char_pos.y);
        
        hf_array_push_back(font->vertices, char_pos.x + char_size.x); hf_array_push_back(font->vertices, char_pos.y);
        hf_array_push_back(font->vertices, char_pos.x); hf_array_push_back(font->vertices, char_pos.y + char_size.y);
        hf_array_push_back(font->vertices, char_pos.x + char_size.x); hf_array_push_back(font->vertices, char_pos.y + char_size.y);
        
        //printf("%f %u\n", char_pos.x, i);
        
        f32 tex_x = font->characters[char_num].texture_offset.x;
        f32 tex_y = font->characters[char_num].texture_offset.y;
        
        f32 tex_max_x = font->characters[char_num].texture_offset.x + (font->characters[char_num].size.x / font->atlas_size.x);
        f32 tex_max_y = font->characters[char_num].texture_offset.y + (font->characters[char_num].size.y / font->atlas_size.y);
        
        hf_array_push_back(font->texture_coords, tex_x); hf_array_push_back(font->texture_coords, tex_y);
        hf_array_push_back(font->texture_coords, tex_x); hf_array_push_back(font->texture_coords, tex_max_y);
        hf_array_push_back(font->texture_coords, tex_max_x); hf_array_push_back(font->texture_coords, tex_y);
        
        hf_array_push_back(font->texture_coords, tex_max_x); hf_array_push_back(font->texture_coords, tex_y);
        hf_array_push_back(font->texture_coords, tex_x); hf_array_push_back(font->texture_coords, tex_max_y);
        hf_array_push_back(font->texture_coords, tex_max_x); hf_array_push_back(font->texture_coords, tex_max_y);
        
        font->char_count += 1;
        if(font->char_count >= 5000){
            hf_render_font(font);
        }
        
    }
    
    
    
}