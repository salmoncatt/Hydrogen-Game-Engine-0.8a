/* date = August 15th 2021 8:22 pm */

#ifndef HFGL_H
#define HFGL_H

#define GLDECL WINAPI

//#define GL_GLEXT_PROTOTYPES
//#include "../../ext/glext.h"
#include <GL/glext.h>
#include <GL/wglext.h>

extern b8 hf_gl_created;

//used these resources: https://github.com/ApoorvaJ/Papaya/blob/3808e39b0f45d4ca4972621c847586e4060c042a/src/libs/gl_lite.h
//http://www.rastertek.com/gl40tut03.html


// NOTE(salmoncatt): these are the opengl extension functions that are going to be loaded (add more as needed)
#define HF_GL_FUNC_LIST \
HF_WGL(HGLRC, CreateContextAttribsARB, HDC hDC, HGLRC hShareContext, const int *attribList);\
HF_GLE(void, BindBuffer, GLenum target, GLuint buffer)\
HF_GLE(void, GenBuffers, GLsizei n, GLuint* buffers)\
HF_GLE(void, BufferData, GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)\
HF_GLE(void, VertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)\
HF_GLE(void, DeleteBuffers, GLsizei n, const GLuint *buffers)\
HF_GLE(void, GenVertexArrays, GLsizei n, GLuint *arrays);\
HF_GLE(void, BindVertexArray, GLuint array);\


// NOTE(salmoncatt): give declarations of opengl extension functions
#define HF_GLE(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* gl##name;
#define HF_WGL(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* wgl##name;
HF_GL_FUNC_LIST
#undef HF_GLE
#undef HF_WGL

b8 hf_gl_init();

b8 hf_gl_load_extensions();

u32 hf_generate_VAO();

u32 hf_generate_VBO();

void hf_gl_get_version(u32* major, u32* minor);

// NOTE(salmoncatt): has to be float data
void hf_push_data_to_VBO(u32 index, u32 size, hf_vector* data);

void hf_push_data_to_IBO(u32 index, u32 size, const void* data);

//void hf_opengl_cleanup();

void hf_gl_close();

//PFNGLBINDBUFFERPROC glBindBuffer;
//PFNGLGENBUFFERSPROC glGenBuffers;



#endif //HFGL_H
