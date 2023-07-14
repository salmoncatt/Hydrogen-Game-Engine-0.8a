#include "hf_font.h"
#include "hffreetype.h"

#define FT_CEIL(X)  (((X + 63) & -64) / 64)

hf_font hf_font_from_file(const char* path, u32 font_size){
    hf_font font = {};
    font.size = font_size;
    //font.max_texture_width = 1024;
    font.path = path;
    font.name = hf_remove_file_path(path);
    
    //SetProcessDPIAware(); //true
    /* 
        HDC screen = GetDC(NULL);
        double hSize = GetDeviceCaps(screen, HORZSIZE);
        double vSize = GetDeviceCaps(screen, VERTSIZE);
        double hRes = GetDeviceCaps(screen, HORZRES);
        double vRes = GetDeviceCaps(screen, VERTRES);
        
        double aspect_ratio = vSize / hSize;
     */
    
    FT_Face face = hf_load_face(path);
    //FT_Set_Pixel_Sizes(face, 0, font.size);
    //FT_Set_Char_Size(face, 0, font.size * 96, 0, 0);
    
    
    FT_Size_RequestRec req;
    req.type = FT_SIZE_REQUEST_TYPE_NOMINAL;
    req.width = 0;
    req.height = font_size * 64;
    //req.horiResolution = (u32)(hRes);
    req.horiResolution = 96;
    //req.vertResolution = (u32)(vRes);
    req.vertResolution = 96;
    FT_Request_Size(face, &req);
    
    FT_GlyphSlot glyph = face->glyph;
    
    //https://github.com/ocornut/imgui/issues/4780
    
    //font.glyph_height = face->size->metrics.height >> 6;
    font.glyph_height = font_size * 72 / 96;
    
    u32 width = 0;
    u32 height = 0;
    
    //u32 bbox_ymax = FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale) >> 6;
    //u32 bbox_ymin = FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale) >> 6;
    //font.glyph_height= face->glyph->metrics.vertAdvance - bbox_ymin;
    
    //font.glyph_height = face->size->metrics.ascender >> 6;
    //font.glyph_height = (face->size->metrics.ascender + face->size->metrics.descender) >> 6;
    //font.glyph_height = (u32)((f32)FT_CEIL(face->size->metrics.ascender) + (f32)FT_CEIL(face->size->metrics.descender));
    //font.descender = (face->size->metrics.descender >> 6) >> 6;
    
    //printf("%u %u\n", font.size, font.glyph_height);
    /* 
        u32 row_width = 0;
        u32 row_height = 0;
     */
    
    
    for(unsigned char c = 32; c < 127; c++){
        //super sophisticated error checking algorithm
        if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
            //char character = (char)(i);
            
            hf_err("[HF FT] couldn't load character: [%c] for font: [%s]\n", c, font.name);
            
            continue;
        }
        
        //FT_Render_Glyph(glyph, FT_RENDER_MODE_SDF);
        
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
        
        width += glyph->bitmap.width;
        height = hf_max(height, glyph->bitmap.rows);
    }
    //font.glyph_height = 0;
    
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
    font.atlas_texture.wrap_mode = (v2f){GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER};
    
    hf_texture_create(&font.atlas_texture);
    
    //glPixelStorei(GL_UNPCK_ALIGNMENT, 1);
    
    for (unsigned char c = 32; c < 127; c++) {
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
        //FT_Render_Glyph(glyph, FT_RENDER_MODE_SDF);
        
        //printf("%u\n", (u32)glyph->bitmap.width);
        
        
        
        hf_texture_set_sub_image(&font.atlas_texture, 0, offset, hf_v2f(glyph->bitmap.width, glyph->bitmap.rows), glyph->bitmap.buffer);
        
        font.characters[c].advance = (v2f){(f32)(glyph->advance.x >> 6), (f32)(glyph->advance.y >> 6)};
        font.characters[c].bitmap_left_top = (v2f){(f32)glyph->bitmap_left, (f32)glyph->bitmap_top};
        //printf("[%f] [%c]\n", (f32)(c), c);
        //printf("[%f] [%c]\n", (f32)(glyph->bitmap.rows), c);
        font.characters[c].size = (v2f){(f32)(glyph->bitmap.width), (f32)(glyph->bitmap.rows)};
        font.characters[c].texture_offset = (v2f){(f32)(offset.x / width), (f32)(offset.y / height)};
        
        /* 
                if((u32)(c) == 72){
                    font.glyph_height = (u32)glyph->bitmap.rows;
                }
         */
        
        //height = hf_max(height, glyph->bitmap.rows);
        offset.x += glyph->bitmap.width;
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
    //hf_texture_destroy(&font->atlas_texture);
}

u32 hf_font_get_bitmap_length(hf_font* font, char* text){
    u32 length = hf_strlen(text);
    u32 size = 0;
    
    if(length == 0)
        return 0;
    
    for(u32 i = 0; i < length; i++){
        char c = text[i];
        size += (u32)font->characters[c].advance.x;
    }
    
    return size;
}