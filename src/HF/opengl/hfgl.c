#include "hfgl.h"


// NOTE(salmoncatt): give definitions to opengl extenion functions
#define HF_GLE(type, name, ...) name##proc* gl##name;
HF_GL_FUNC_LIST
#undef HF_GLE


b8 hf_gl_init(){
    b8 result = 0;
    hf_log("[HF GL] initializing...\n");
    result = hf_gl_load_extensions();
    hf_log("[HF GL] initialized\n\n");
    return result;
}

b8 hf_gl_load_extensions(){
    hf_log("[HF GL] loading opengl32.dll\n");
    HINSTANCE gl_dll = LoadLibraryA("opengl32.dll");
    typedef PROC WINAPI wglGetProcAddressproc(LPCSTR lpszProc);
    if(gl_dll){
        hf_log("[HF GL] loaded opengl32.dll\n");
    }else{
        hf_err("[HF GL] couldn't load opengl32.dll\n");
        return 0;
    }
    
    wglGetProcAddressproc* wglGetProcAddress = (wglGetProcAddressproc*)GetProcAddress(gl_dll, "wglGetProcAddress");
    
    hf_log("[HF GL] loading extensions...\n");
    if(!wglGetCurrentContext()){
        hf_err("[HF GL] opengl context is null, please create a context before calling hf_gl_init()\n");
        return 0;
    }
    
    u32 i = 0;
    
    // NOTE(salmoncatt): load the function of the opengl extension
#define HF_GLE(type, name, ...)\
gl##name = (name##proc*)wglGetProcAddress("gl" #name);\
i += 1;\
if(!gl##name){\
hf_err("[HF GL] couldn't load fuction: gl" #name " from opengl lib\n");\
return 0;\
}\
    
    HF_GL_FUNC_LIST
        
#undef HF_GLE
    
    hf_log("[HF GL] loaded %u extensions\n", i);
    return 1;
}

u32 hf_generate_VAO(){
    u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    return vao;
}

u32 hf_generate_VBO(){
    u32 vbo = 0;
    glGenBuffers(1, &vbo);
    // TODO(salmoncatt): add vbo to list
    return vbo;
    
}

void hf_push_data_to_VBO(u32 index, u32 size, hf_vector* data){
    
    u32 vbo = hf_generate_VBO();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, data->size * sizeof(float), &data->data[0], GL_STATIC_DRAW);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, sizeof(float) * size, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

void hf_gl_close(){
    
}


