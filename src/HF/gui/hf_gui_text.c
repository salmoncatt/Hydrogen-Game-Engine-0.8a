#include "hfguipanel.h"

void hf_gui_title_text(char* text, hf_font* font, i32 x, i32 y){
    u32 length = hf_strlen(text);
    //f32 scale_ratio = (f32)(height) / (f32)(font->size);
    f32 scale_ratio = 1;
    f32 scaled_height = font->glyph_height;
    //height = (u32)(scaled_height);
    
    v2f screen_pos = (v2f){(u32)(hf_current_gui_panel->x + x), (u32)(hf_current_gui_panel->y + y)};
    v2f cursor_pos;
    
    /* 
        if(render_type & HF_TEXT_CENTERED){
            cursor_pos = (v2f){screen_pos.x, screen_pos.y + height / 2};
        }else if(render_type & HF_TEXT_BOTTOM){
            cursor_pos = screen_pos;
        }
     */
    
    cursor_pos = screen_pos;
    
    /* 
        if(!(render_type & HF_TEXT_DONT_USE_SPACING))
            cursor_pos.y += hf_current_gui_panel->element_spacing;
     */
    
    //hf_render_rect(panel->x - 5, panel->y + (f32)title_bar_height / 2 - (f32)panel->font->glyph_height / 2, 200, panel->font->glyph_height, (v4f){0, 0, 1, 1});
    
    //hf_render_rect(cursor_pos.x, cursor_pos.y - 13, 200, 13, (v4f){0, 0, 0, 1});
    //hf_render_rect(cursor_pos.x + 5, cursor_pos.y - font->glyph_height, 200, scaled_height, (v4f){0.9f, 0.7f, 0, 0.5f});
    //printf("%u\n", font->descender);
    //hf_current_gui_panel->cursor_pos.y += scaled_height;
    //cursor_pos.y += hf_current_gui_panel->element_spacing;
    
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

void hf_gui_text(char* text, hf_font* font, u32 flags){
    u32 length = hf_strlen(text);
    //f32 scale_ratio = (f32)(height) / (f32)(font->size);
    f32 scale_ratio = 1;
    //f32 scaled_height = font->glyph_height;
    //height = (u32)(scaled_height);
    
    v2f screen_pos = (v2f){(u32)(hf_current_gui_panel->x + hf_current_gui_panel->cursor_pos.x), (u32)(hf_current_gui_panel->y + hf_current_gui_panel->cursor_pos.y + font->glyph_height)};
    v2f cursor_pos = screen_pos;
    cursor_pos.y += hf_current_gui_panel->element_spacing;
    hf_current_gui_panel->cursor_pos.y += font->glyph_height + hf_current_gui_panel->element_spacing;
    
    /* 
        if(render_type & HF_TEXT_CENTERED){
            cursor_pos = (v2f){screen_pos.x, screen_pos.y + height / 2};
        }else if(render_type & HF_TEXT_BOTTOM){
            cursor_pos = screen_pos;
        }
     */
    
    
    /* 
        if(!(render_type & HF_TEXT_DONT_USE_SPACING))
     */
    
    //hf_render_rect(panel->x - 5, panel->y + (f32)title_bar_height / 2 - (f32)panel->font->glyph_height / 2, 200, panel->font->glyph_height, (v4f){0, 0, 1, 1});
    
    //hf_render_rect(cursor_pos.x, cursor_pos.y - 13, 200, 13, (v4f){0, 0, 0, 1});
    //hf_render_rect(cursor_pos.x + 5, cursor_pos.y - font->glyph_height, 200, scaled_height, (v4f){0.9f, 0.7f, 0, 0.5f});
    //printf("%u\n", font->descender);
    //hf_current_gui_panel->cursor_pos.y += scaled_height;
    //cursor_pos.y += hf_current_gui_panel->element_spacing;
    
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

/* 
void hf_gui_text_advanced(u32 max_w, u32 height, b8 centered, char* text, hf_font* font, u32 render_type){
    u32 length = hf_strlen(text);
    //f32 scale_ratio = (f32)(height) / (f32)(font->size);
    f32 scale_ratio = 1;
    f32 scaled_height = font->glyph_height;
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
    
    //hf_render_rect(cursor_pos.x, cursor_pos.y - height, max_w, height, (v4f){0, 0, 0, 1});
    //hf_render_rect(cursor_pos.x + 5, cursor_pos.y - scaled_height, max_w, scaled_height, (v4f){0.9f, 0.7f, 0, 0.5f});
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
 */