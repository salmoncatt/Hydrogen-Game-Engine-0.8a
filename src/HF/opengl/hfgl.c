#include "hfgl.h"

b8 hf_gl_created = 0;

// NOTE(salmoncatt): give definitions to opengl extenion functions
#define HF_GLE(type, name, ...) name##proc* gl##name;
#define HF_WGL(type, name, ...) name##proc* wgl##name;
HF_GL_FUNC_LIST
#undef HF_GLE
#undef HF_WGL


b8 hf_gl_init(){
    if(!hf_gl_created){
        b8 result = 0;
        hf_log("[HF GL] initializing...\n");
        result = hf_gl_load_extensions();
        
        u32 major, minor;
        hf_gl_get_version(&major, &minor);
        hf_log("[HF GL] version: [%u.%u]\n", major, minor);
        
        
        hf_log("[HF GL] initialized\n\n");
        
        hf_gl_created = result;
        
        return result;
    }
    else
        return 1;
}

void hf_gl_get_version(u32* major, u32* minor){
    // for all versions
    char* ver = (char*)glGetString(GL_VERSION); // ver = "3.2.0"
    
    *major = ver[0] - '0';
    if( *major >= 3)
    {
        // for GL 3.x
        glGetIntegerv(GL_MAJOR_VERSION, major); // major = 3
        glGetIntegerv(GL_MINOR_VERSION, minor); // minor = 2
    }
    else
    {
        *minor = ver[2] - '0';
    }
    
    // GLSL
    ver = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION); // ver = "1.50 NVIDIA via Cg compiler"
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
    
#define HF_WGL(type, name, ...)\
wgl##name = (name##proc*)wglGetProcAddress("wgl" #name);\
i += 1;\
if(!wgl##name){\
hf_err("[HF GL] couldn't load fuction: wgl" #name " from opengl lib\n");\
return 0;\
}\
    
    HF_GL_FUNC_LIST
        
#undef HF_GLE
#undef HF_WGL
    
    hf_log("[HF GL] loaded %u extensions\n", i);
    return 1;
}

u32 hf_generate_VAO(){
    u32 vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    // TODO(salmoncatt): add vao to list
    return vao;
}

u32 hf_generate_VBO(){
    u32 vbo = 0;
    glGenBuffers(1, &vbo);
    // TODO(salmoncatt): add vbo to list
    return vbo;
    
}

void hf_push_data_to_VBO(u32 index, u32 type, float* data, u32 length){
    
    u32 vbo = hf_generate_VBO();
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    glBufferData(GL_ARRAY_BUFFER, length * sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(index, type, GL_FLOAT, GL_FALSE, sizeof(float) * type, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
}

void hf_push_data_to_IBO(u32 index, u32 size, const void* data, u32 IBO){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(unsigned int), data, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void hf_gl_compile_shader(u32 id, const char* shader_code, const char* shader_name){
    glShaderSource(id, 1, &shader_code, NULL);
    glCompileShader(id);
    
    int compile_code = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &compile_code);
    if (compile_code != GL_TRUE) {
        char error_msg[1024];
        glGetShaderInfoLog(id, 1024, NULL, error_msg);
        
        hf_log("$hfcc{yellow}[$hfcc{red}HF$hfcc{yellow}] $hfcc{red} compiling shader: %s has failed with error: %s\n", shader_name, error_msg);
        return;
    }
    
    hf_log("[HF] compiled shader code: %s\n", shader_name);
}

void hf_gl_link_and_validate_shader(u32 program_id){
    glLinkProgram(program_id);
    u32 compile_code = 0;
    
    glGetProgramiv(program_id, GL_LINK_STATUS, &compile_code);
    if(compile_code != GL_TRUE){
        char error_msg[1024];
        glGetProgramInfoLog(program_id, 1024, NULL, error_msg);
        
        hf_log("$hfcc{yellow}[$hfcc{red}HF$hfcc{yellow}] $hfcc{red} linking shader failed with error:$hfcc{yellow} %s \n", error_msg);
    }
    
    glValidateProgram(program_id);
    
    glGetProgramiv(program_id, GL_LINK_STATUS, &compile_code);
    if(compile_code != GL_TRUE){
        char error_msg[1024];
        glGetProgramInfoLog(program_id, 1024, NULL, error_msg);
        
        hf_log("$hfcc{yellow}[$hfcc{red}HF$hfcc{yellow}] $hfcc{red} validating shader failed with error:$hfcc{yellow} %s \n", error_msg);
    }
}

void hf_gl_close(){
    
}


