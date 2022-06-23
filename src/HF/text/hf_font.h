/* date = June 16th 2022 4:37 pm */

#ifndef HF_FONT_H
#define HF_FONT_H

typedef struct hf_font_character{
    
    v2f size; //size
    v2f texture_offset; //offset in texture coordinates for a glyph
    v2f advance; //amount to offset glyph in rendering
    v2f bitmap_left_top; //the top and left of the bitmap
    
}hf_font_character;

typedef struct hf_font{
    u32 size;
    u32 line_spacing;
    v2f atlas_size;
    v3f color;
    
    hf_texture atlas_texture;
    
    //u32 max_texture_width; //default 1024 if left 0, glyph moves to next row in atlas after this
    
    //b8 log_status;
    
    hf_font_character characters[128];
    
    const char* path;
    const char* name;
    
    f32* vertices;
    u32 vbo_vert;
    f32* texture_coords;
    u32 vbo_tex;
    u32 vao;
    b8 created;
    
    u32 char_count;
    
}hf_font;

hf_font hf_font_from_file(const char* path, u32 font_size);
void hf_font_destroy(hf_font* font);

#endif //HF_FONT_H
