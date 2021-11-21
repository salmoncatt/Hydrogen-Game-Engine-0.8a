/* date = August 15th 2021 8:22 pm */

#ifndef HFGL_H
#define HFGL_H

//#define GL_GLEXT_PROTOTYPES
//#include "../../ext/glext.h"
#include <GL/glext.h>

void hf_gl_init();

void* hf_gl_load_proc(char* name);

void hf_gl_load_extensions();


u32 hf_generate_VAO();

u32 hf_generate_VBO();


// NOTE(salmoncatt): has to be float data
void hf_push_data_to_VBO(u32 index, u32 size, hf_vector* data);

void hf_push_data_to_IBO(u32 index, u32 size, const void* data);

void hf_opengl_cleanup();

void hf_gl_close();

//PFNGLBINDBUFFERPROC glBindBuffer;
//PFNGLGENBUFFERSPROC glGenBuffers;



#endif //HFGL_H
