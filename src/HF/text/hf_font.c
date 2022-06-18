#include "hf_font.h"
#include "hffreetype.h"

hf_font hf_font_from_file(const char* path){
    hf_font font = {};
    font.glyph_height = 48;
    font.max_texture_width = 1024;
    font.path = path;
    font.name = hf_remove_file_path(path);
    
    FT_Face face = hf_load_face(path);
    FT_Set_Pixel_Sizes(face, 0, font.glyph_height);
    FT_GlyphSlot glyph = face->glyph;
    
    u32 width = 0;
    u32 height = 0;
    
    u32 row_width = 0;
    u32 row_height = 0;
    
    
    for(u32 i = 0; i < 128; i++){
        //super sophisticated error checking algorithm
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            char character = (char)(i);
            
            hf_err("[HF FT] couldn't load character: [%c] for font: [%s]\n", character, font.name);
            
            continue;
        }
        
        if (row_width + glyph->bitmap.width + 1 >= font.max_texture_width) {
            width = max(width, row_width);
            height += row_height;
            
            row_width = 0;
            row_height = 0;
        }
        
        row_width += glyph->bitmap.width + 1;
        row_height = max(height, glyph->bitmap.rows);
    }
    
    
    
    width = max(width, row_width);
    height += row_height;
    
    font.atlas_size.x = width;
    font.atlas_size.y = height;
    
    row_height = 0;
    
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
    
    
    for (int i = 0; i < 128; ++i) {
        //super sophisticated error checking algorithm
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
            char character = (char)(i);
            
            hf_err("[HF FT] couldn't load character: [%c] for font: [%s]\n", character, font.name);
            
            continue;
        }
        //printf("%c\n", (char)(i));
        
        if (offset.x + glyph->bitmap.width + 1 >= font.max_texture_width) {
            offset.y += row_height;
            row_height = 0;
            offset.x = 0;
        }
        
        //printf("%u\n", (u32)glyph->bitmap.width);
        
        hf_texture_set_sub_image(&font.atlas_texture, 0, offset, hf_v2f(glyph->bitmap.width, glyph->bitmap.rows), glyph->bitmap.buffer);
        
        font.characters[i].advance = hf_v2f((float)(glyph->advance.x >> 6), (float)(glyph->advance.y >> 6));
        font.characters[i].bitmap_left_top = hf_v2f((float)glyph->bitmap_left, (float)glyph->bitmap_top);
        font.characters[i].size = hf_v2f((float)(glyph->bitmap.width), (float)(glyph->bitmap.rows));
        font.characters[i].texture_offset = hf_v2f((float)(offset.x / width), (float)(offset.y / height));
        
        row_height = hf_max(row_height, glyph->bitmap.rows);
        offset.x += glyph->bitmap.width + 2;
    }
    
    //free(blank_color);
    
    /* 
        if (font.log_status) {
            Debug::systemSuccess("Loaded font: " + Util::removePathFromFilePathAndName(path), DebugColor::Blue);
            Debug::systemSuccess(Util::removePathFromFilePathAndName(path) + " atlas size is " + std::to_string(width) + " x " + std::to_string(height) + " pixels and is " + std::to_string(width * height / 1024) + " kb", DebugColor::Blue);
        }
     */
    
    FT_Done_Face(face);
    
    return font;
}