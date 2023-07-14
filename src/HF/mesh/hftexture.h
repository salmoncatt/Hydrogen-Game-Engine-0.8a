/* date = March 1st 2022 8:11 pm */

#ifndef HFTEXTURE_H
#define HFTEXTURE_H

#include "../graphics/hfimage.h"
#include "../math/hfmath.h"


typedef struct hf_texture{
    
    hf_image image; // 0 
    
    u32 texture_id; // 0
    b8 is_created; // 0
    
    
    v2f wrap_mode; // {GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE}
    v2f filter_mode; // {GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST}
    
    u32 byte_alignment; // 4
    u32 texture_type; // GL_TEXTURE_2D
    f32 internal_format; // GL_RGBA8
    u32 format; // GL_RGBA
    f32 data_type; // GL_UNSIGNED_BYTE
    b8 generate_mipmap; // 1
    u32 texture_unit; // 0
    
}hf_texture;

#define hf_texture_default {{}, 0, 0, {GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE}, {GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST}, 4, GL_TEXTURE_2D, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, 1, 0}


extern u32* hf_texture_ids;


hf_texture hf_texture_from_image(hf_image image);
void hf_texture_copy(hf_texture* dest, hf_texture* src);
hf_texture hf_texture_from_file(const char* file);

void hf_texture_set_sub_image(hf_texture* texture, u32 level, v2f offset, v2f size, const void* pixels);

void hf_texture_create(hf_texture* texture);
//void hf_texture_destroy(hf_texture* texture);

//void hf_texture_init();
//void hf_texture_destroy_all();


#endif //HFTEXTURE_H
