#include "hf_font.h"
#include "hffreetype.h"

hf_font hf_font_from_file(const char* path, u32 font_size){
    hf_font font = {};
    font.size = font_size;
    //font.max_texture_width = 1024;
    font.path = path;
    font.name = hf_remove_file_path(path);
    
    FT_Face face = hf_load_face(path);
    FT_Set_Pixel_Sizes(face, 0, font.size);
    
    FT_GlyphSlot glyph = face->glyph;
    
    u32 width = 0;
    u32 height = 0;
    
    /* 
        u32 row_width = 0;
        u32 row_height = 0;
     */
    
    
    for(unsigned char c = 32; c < 128; c++){
        //super sophisticated error checking algorithm
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            //char character = (char)(i);
            
            hf_err("[HF FT] couldn't load character: [%c] for font: [%s]\n", c, font.name);
            
            continue;
        }
        
        FT_Render_Glyph(glyph, FT_RENDER_MODE_SDF);
        
        /* 
                if (row_width + glyph->bitmap.width + 1 >= font.max_texture_width) {
                    width = max(width, row_width);
                    height += row_height;
                    
                    row_width = 0;
                    row_height = 0;
                }
         */
        
        /*         
                row_width += glyph->bitmap.width + 1;
                row_height = max(height, glyph->bitmap.rows);
                 */
        
        width += glyph->bitmap.width + 1;
        height = max(height, glyph->bitmap.rows);
    }
    
    
    
    /* 
        width = max(width, row_width);
        height += row_height;
     */
    
    font.atlas_size.x = width;
    font.atlas_size.y = height;
    
    //height = 0;
    
    v2f offset = {};
    
    /* 
        for (u32 i = 0; i < (width * height); i++) {
            blank_color[i] = 0x0;
        }
     */
    
    hf_image image_data = {};
    //printf("works here\n");
    image_data.width = width;
    image_data.height = height;
    image_data.channels = 1;
    image_data.data = calloc(width * height, sizeof(char));;
    //hf_image_create(&image_data, width, height, 1, blank_color);
    
    font.atlas_texture = hf_texture_from_image(image_data);
    font.atlas_texture.byte_alignment = 1;
    font.atlas_texture.filter_mode = (v2f){GL_LINEAR, GL_LINEAR};
    font.atlas_texture.internal_format = GL_RED;
    font.atlas_texture.format = GL_RED;
    font.atlas_texture.generate_mipmap = 0;
    font.atlas_texture.wrap_mode = (v2f){GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE};
    
    hf_texture_create(&font.atlas_texture);
    
    //glPixelStorei(GL_UNPCK_ALIGNMENT, 1);
    
    for (unsigned char c = 32; c < 128; c++) {
        //super sophisticated error checking algorithm
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            //char character = (char)(i);
            
            hf_err("[HF FT] couldn't load character: [%c] for font: [%s]\n", c, font.name);
            
            continue;
        }
        //printf("%c\n", (char)(i));
        
        /* 
                if (offset.x + glyph->bitmap.width + 1 >= font.max_texture_width) {
                    offset.y += row_height;
                    row_height = 0;
                    offset.x = 0;
                }
         */
        
        //printf("%u\n", (u32)glyph->bitmap.width);
        
        hf_texture_set_sub_image(&font.atlas_texture, 0, offset, hf_v2f(glyph->bitmap.width, glyph->bitmap.rows), glyph->bitmap.buffer);
        
        font.characters[c].advance = (v2f){(f32)(glyph->advance.x >> 6), (f32)(glyph->advance.y >> 6)};
        font.characters[c].bitmap_left_top = (v2f){(f32)glyph->bitmap_left, (f32)glyph->bitmap_top};
        font.characters[c].size = (v2f){(f32)(glyph->bitmap.width), (f32)(glyph->bitmap.rows)};
        font.characters[c].texture_offset = (v2f){(f32)(offset.x / width), (f32)(offset.y / height)};
        
        //height = hf_max(height, glyph->bitmap.rows);
        offset.x += glyph->bitmap.width + 2;
    }
    
    font.vertices = hf_array_create(f32);
    font.texture_coords = hf_array_create(f32);
    
    
    font.vao = hf_generate_VAO();
    font.vbo_vert = hf_push_data_to_VBO(0, 0, 2, NULL, 5000 * 6 * 2, GL_DYNAMIC_DRAW);
    font.vbo_tex = hf_push_data_to_VBO(0, 1, 2, NULL, 5000 * 6 * 2, GL_DYNAMIC_DRAW);
    
    font.line_spacing = face->ascender >> 5;
    FT_Done_Face(face);
    
    return font;
}

void hf_font_destroy(hf_font* font){
    hf_array_free(font->vertices);
    hf_array_free(font->texture_coords);
    hf_texture_destroy(&font->atlas_texture);
}