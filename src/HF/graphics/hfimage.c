#include "hfimage.h"

void hf_image_create(hf_image* image, u32 width, u32 height, u32 channels, unsigned char* data){
    image->width = width;
    image->height = height;
    image->channels = channels;
    
    u64 allocation = width * height * channels;
    image->data = (unsigned char*)(hf_malloc(allocation));
    
    if(data != NULL){
        hf_memcpy(&image->data, data, allocation);
    }
}

void hf_image_create_from_file(hf_image* image, const char* file_path){
    image->width = 0;
    image->height = 0;
    image->channels = 0;
    image->data = NULL;
    image->file_path = file_path;
    
    image->data = stbi_load(file_path, &image->width, &image->height, &image->channels, STBI_rgb_alpha);
    image->channels = STBI_rgb_alpha;
    
    if(image->data == NULL){
        hf_err("[HF Image] couldn't load image from file: [%s]\n", file_path);
    }
    
}

hf_image hf_image_from_file(const char* file_path){
    hf_image image = {};
    
    image.width = 0;
    image.height = 0;
    image.channels = 0;
    image.data = NULL;
    image.file_path = file_path;
    
    image.data = stbi_load(file_path, &image.width, &image.height, &image.channels, STBI_rgb_alpha);
    image.channels = STBI_rgb_alpha;
    
    if(image.data == NULL){
        hf_err("[HF Image] couldn't load image from file: [%s]\n", file_path);
    }
    
    return image;
}

void hf_image_copy(hf_image* dest, hf_image* src){
    if(dest->data != NULL){
        hf_free(dest->data);
        dest->data = NULL;
    }
    
    if(src->data != NULL){
        u64 allocation = src->width + src->height + src->channels;
        
        dest->data = (unsigned char*)hf_malloc(allocation);
        dest->width = src->width;
        dest->height = src->height;
        dest->channels = src->channels;
        dest->file_path = src->file_path;
        
        hf_memcpy(dest->data, src->data, allocation);
    }
    
}


void hf_image_destroy(hf_image* image){
    if(image->data == NULL){
        hf_free(image->data);
    }
    
    image->data = NULL;
}

