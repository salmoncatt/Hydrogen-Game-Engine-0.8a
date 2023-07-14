#include "hftexture.h"

u32* hf_texture_ids;


hf_texture hf_texture_from_image(hf_image image){
    hf_texture out = hf_texture_default;
    
    out.image = image;
    out.texture_id = 0;
    
    return out;
}

void hf_texture_copy(hf_texture* dest, hf_texture* src){
    
}

hf_texture hf_texture_from_file(const char* file){
    hf_texture out = hf_texture_default;
    
    out.image = hf_image_from_file(file);;
    out.texture_id = 0;
    
    return out;
}



void hf_texture_set_sub_image(hf_texture* texture, u32 level, v2f offset, v2f size, const void* pixels){
    glBindTexture(texture->texture_type, texture->texture_id);
    glTexSubImage2D(GL_TEXTURE_2D, level, offset.x, offset.y, size.x, size.y, texture->format, texture->data_type, pixels);
    glBindTexture(texture->texture_type, 0);
}



void hf_texture_create(hf_texture* texture){
    if (!texture->is_created) {
        
        glActiveTexture(GL_TEXTURE0 + texture->texture_unit);
        
        glGenTextures(1, &texture->texture_id);
        glBindTexture(texture->texture_type, texture->texture_id);
        
        hf_array_push_back(hf_texture_ids, texture->texture_id);
        
        glPixelStorei(GL_UNPACK_ALIGNMENT, texture->byte_alignment);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture->filter_mode.x);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture->filter_mode.y);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture->wrap_mode.x);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture->wrap_mode.y);
        
        /*if (image.data != NULL)
            glTexImage2D(textureType, 0, internalFormat, image.width, image.height, 0, format, dataType, image.data);
        else
            glTexImage2D(textureType, 0, internalFormat, image.width, image.height, 0, format, dataType, 0);*/
        glTexImage2D(texture->texture_type, 0, texture->internal_format, texture->image.width, texture->image.height, 0, texture->format, texture->data_type, texture->image.data);
        
        if(texture->generate_mipmap)
            glGenerateMipmap(texture->texture_type);
        
        texture->is_created = 1;
        
        glActiveTexture(GL_TEXTURE0);
        
        glBindTexture(texture->texture_type, 0);
    }
}

/* 
void hf_texture_destroy(hf_texture* texture){
    glDeleteTextures(1, &texture->texture_id);
    hf_image_destroy(&texture->image);
}
 */

/* 
void hf_texture_destroy_all(){
    glDeleteTextures(hf_array_size(hf_texture_ids), hf_texture_ids);
    
    hf_log("[HF] deleted: (textures: [%u])\n", hf_array_size(hf_gl_vbos), hf_array_size(hf_gl_vaos));
    
    hf_array_free(hf_texture_ids);
}
 */