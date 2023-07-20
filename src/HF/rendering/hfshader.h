/* date = November 14th 2021 5:31 pm */

#ifndef HFSHADER_H
#define HFSHADER_H

typedef struct hf_shader{
    
    char* vertex_shader;
    char* fragment_shader;
    char* vertex_name;
    char* fragment_name;
    
    u32 vertex_id;
    u32 fragment_id;
    u32 program_id;
    
    char* name;
    
    b8 verbose_compiling; //will print when the vertex shader is compiled along with fragment shader (takes up a lot of space so disabled by default)
    
}hf_shader;

void hf_shader_create(hf_shader* shader, const char* vertex_path, const char* fragment_path);
void hf_shader_destroy(hf_shader* shader);

void hf_shader_bind(hf_shader* shader);
void hf_shader_unbind();

u32 hf_shader_get_uniform_location(hf_shader* shader, const char* name);
u32 hf_shader_get_attribute_location(hf_shader* shader, const char* name);

void hf_shader_set_uniform_b8(hf_shader* shader, const char* name, b8 data);
void hf_shader_set_uniform_u32(hf_shader* shader, const char* name, u32 data);
void hf_shader_set_uniform_f32(hf_shader* shader, const char* name, f32 data);
void hf_shader_set_uniform_v2f(hf_shader* shader, const char* name, v2f* data);
void hf_shader_set_uniform_v3f(hf_shader* shader, const char* name, v3f* data);
void hf_shader_set_uniform_v4f(hf_shader* shader, const char* name, v4f* data);
void hf_shader_set_uniform_m4f(hf_shader* shader, const char* name, m4f* data);

#endif //HFSHADER_H
