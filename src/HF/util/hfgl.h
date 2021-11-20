/* date = August 15th 2021 8:22 pm */

#ifndef HFGL_H
#define HFGL_H

u32 hf_generate_VAO();

u32 hf_generate_VBO();


// NOTE(salmoncatt): has to be float data
void hf_push_data_to_VBO(u32 index, u32 size, hf_vector* data);

void hf_push_data_to_IBO(u32 index, u32 size, const void* data);

void hf_opengl_cleanup();

#endif //HFGL_H
