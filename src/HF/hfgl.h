/* date = August 15th 2021 8:22 pm */

#ifndef HFGL_H
#define HFGL_H

u32 hf_generate_VAO();

u32 hf_generate_VBO();

/* 
void hf_push_data_to_VBO(u64 index, u64 size, const void* data);

void hf_push_data_to_IBO(u64 index, u64 size, const void* data);
 */

void hf_opengl_cleanup();

#endif //HFGL_H
