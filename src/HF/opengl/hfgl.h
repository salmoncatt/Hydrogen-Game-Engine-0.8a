/* date = August 15th 2021 8:22 pm */

#ifndef HFGL_H
#define HFGL_H


//#define GL_GLEXT_PROTOTYPES
//#include "../../ext/glext.h"

#ifdef _WIN32

#define GLDECL WINAPI
#include <GL/wglext.h>

#elif defined(__linux__)

#include <dlfcn.h>
#define GLDECL

#endif //WIN32

#include <GL/glext.h>

extern b8 hf_gl_created;
extern u32* hf_gl_vbos;
extern u32* hf_gl_vaos;



//used these resources: https://github.com/ApoorvaJ/Papaya/blob/3808e39b0f45d4ca4972621c847586e4060c042a/src/libs/gl_lite.h
//http://www.rastertek.com/gl40tut03.html


// NOTE(salmoncatt): these are the opengl extension functions that are going to be loaded (add more as needed)
#define HF_GL_FUNC_LIST \
HF_GLE(void,   BindBuffer, GLenum target, GLuint buffer)\
HF_GLE(void,   GenBuffers, GLsizei n, GLuint* buffers)\
HF_GLE(void,   BufferData, GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)\
HF_GLE(void,   BufferSubData, GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)\
HF_GLE(void,   VertexAttribPointer, GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid * pointer)\
HF_GLE(void,   DeleteBuffers, GLsizei n, const GLuint *buffers)\
HF_GLE(void,   GenVertexArrays, GLsizei n, GLuint *arrays);\
HF_GLE(void,   DeleteVertexArrays, GLsizei n, GLuint *arrays);\
HF_GLE(void,   BindVertexArray, GLuint array);\
HF_GLE(void,   EnableVertexAttribArray, GLuint index);\
HF_GLE(void,   DisableVertexAttribArray, GLuint index);\
\
HF_GLE(GLuint, CreateProgram, void);\
HF_GLE(void,   LinkProgram, GLuint program);\
HF_GLE(void,   UseProgram, GLuint program);\
HF_GLE(void,   GetProgramInfoLog, GLuint program, GLsizei bufSize, GLsizei *length, char *infoLog);\
HF_GLE(void,   GetProgramiv, GLuint program, GLenum pname, GLint *params);\
HF_GLE(void,   ValidateProgram, GLuint program);\
HF_GLE(void,   CompileShader, GLuint shader);\
\
HF_GLE(GLuint, CreateShader, GLenum type);\
HF_GLE(void,   AttachShader, GLuint program, GLuint shader);\
HF_GLE(void,   DeleteShader, GLuint shader);\
HF_GLE(void,   DetachShader, GLuint program, GLuint shader);\
HF_GLE(void,   ShaderSource, GLuint shader, GLsizei count, const GLchar* const *string, const GLint *length);\
HF_GLE(void,   GetShaderInfoLog, GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);\
HF_GLE(void,   GetShaderiv, GLuint shader, GLenum pname, GLint *params);\
\
HF_GLE(GLint,  GetUniformLocation, GLuint program, const GLchar *name);\
HF_GLE(GLint,  GetAttribLocation, GLuint program, const GLchar *name) \
HF_GLE(void,   Uniform1i, GLint location, GLint v0) \
HF_GLE(void,   Uniform1f, GLint location, GLfloat v0) \
HF_GLE(void,   Uniform2f, GLint location, GLfloat v0, GLfloat v1) \
HF_GLE(void,   Uniform3f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2) \
HF_GLE(void,   Uniform4f, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) \
HF_GLE(void,   UniformMatrix4fv, GLint location, GLsizei count, GLboolean transpose, const GLfloat *value) \
\
HF_GLE(void,   GenerateMipmap, GLenum target); \



// NOTE(salmoncatt): give declarations of opengl extension functions


#ifdef _WIN32


//windows specific stuff, including fxns for wgl and for some reason glActiveTexture

#define HF_GL_WIN_FUNC_LIST \
HF_WGL(HGLRC,  CreateContextAttribsARB);\
HF_WGL(void,  SwapIntervalEXT);\
HF_WGL(BOOL,  ChoosePixelFormatARB);\
HF_GLE(void,   ActiveTexture, GLenum target); \



#define HF_GLE(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* gl##name;

#define HF_WGL(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* wgl##name;

HF_GL_WIN_FUNC_LIST





#elif defined(__linux__)


#define HF_GL_LINUX_FUNC_LIST \
HF_GLX(void,  SwapIntervalEXT);\

//linux ignores WGL fxns and the HF_GL_WIN_FUNC_LIST entirely

#define HF_GLE(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* gl##name;

#define HF_GLX(type, name, ...) typedef type GLDECL name##proc(__VA_ARGS__); extern name##proc* glX##name;

//this one has a silly proc address on linux so manual input for this one
typedef void (APIENTRYP PFNGLACTIVETEXTUREPROC) (GLenum texture);
extern PFNGLXSWAPINTERVALEXTPROC glXSwapIntervalEXT;





#endif



HF_GL_FUNC_LIST

#undef HF_GLE
#undef HF_WGL






b8 hf_gl_init();

b8 hf_gl_load_extensions();

u32 hf_generate_VAO();

u32 hf_generate_VBO();

void hf_gl_get_version(u32* major, u32* minor);

// NOTE(salmoncatt): has to be float data
u32 hf_push_data_to_VBO(u32 vbo, u32 index, u32 type, f32* data, u32 length, GLenum draw_mode);

void hf_push_data_to_IBO(const void* data, u32 size, u32 IBO, GLenum draw_mode);

//void hf_opengl_cleanup();

void hf_gl_close();

void hf_gl_compile_shader(u32 id, const char* shader_code, const char* shader_name, b8 verbose_compiling);

void hf_gl_link_and_validate_shader(u32 program_id);

#endif //HFGL_H
