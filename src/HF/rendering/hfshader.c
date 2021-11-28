#include "hfshader.h"

void hf_shader_create(hf_shader* shader, const char* vertex_path, const char* fragment_path){
    shader->program_id = glCreateProgram();
    shader->vertex_id = glCreateShader(GL_VERTEX_SHADER);
    shader->fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    
    shader->vertex_shader = hf_load_file_as_string(vertex_path);
    shader->fragment_shader = hf_load_file_as_string(fragment_path);
    
    // TODO(salmoncatt): retrieve shader file names from filepath
    
    hf_gl_compile_shader(shader->vertex_id, shader->vertex_shader, shader->vertex_name);
    hf_gl_compile_shader(shader->fragment_id, shader->fragment_shader, shader->fragment_name);
    
    glAttachShader(shader->program_id, shader->vertex_id);
    glAttachShader(shader->program_id, shader->fragment_id);
    
    hf_gl_link_and_validate_shader(shader->program_id);
    
    
    hf_log("[HF] compiled shader: %s\n", shader->name);
}

void hf_shader_bind(hf_shader* shader){
    glUseProgram(shader->program_id);
}

void hf_shader_unbind(){
    glUseProgram(0);
}

void hf_shader_destroy(hf_shader* shader){
    glDetachShader(shader->program_id, shader->vertex_id);
    glDetachShader(shader->program_id, shader->fragment_id);
    glDeleteShader(shader->vertex_id);
    glDeleteShader(shader->fragment_id);
    glDeleteShader(shader->program_id);
    hf_free(shader->vertex_shader);
    hf_free(shader->fragment_shader);
}

void hf_shader_set_uniform_u32(hf_shader* shader, const char* name, u32 data){
    
}

void hf_shader_set_uniform_b8(hf_shader* shader, const char* name, b8 data){
    
}

void hf_shader_set_uniform_f32(hf_shader* shader, const char* name, f32 data){
    
}

