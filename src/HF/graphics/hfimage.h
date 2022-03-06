/* date = March 1st 2022 8:22 pm */

#ifndef HFIMAGE_H
#define HFIMAGE_H

typedef struct hf_image{
    
    const char* file_path;
    
    u32 width;
    u32 height;
    u32 channels;
    
    unsigned char* data;
    
}hf_image;

void hf_image_create(hf_image* image, u32 width, u32 height, u32 channels, unsigned char* data);
void hf_image_create_from_file(hf_image* image, const char* file_path);

hf_image hf_image_from_file(const char* file_path);

void hf_image_copy(hf_image* dest, hf_image* src);

void hf_image_destroy(hf_image* image);


#endif //HFIMAGE_H
