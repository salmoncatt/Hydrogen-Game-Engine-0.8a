#include "hfshader.h"

void hf_shader_create(hf_shader* shader, const char* vertex_path, const char* fragment_path){
    shader->program_id = glCreateProgram();
    shader->vertex_id = glCreateShader(GL_VERTEX_SHADER);
    shader->fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    
    shader->vertex_shader = hf_load_file_as_string(vertex_path);
    shader->fragment_shader = hf_load_file_as_string(fragment_path);
    
    // TODO(salmoncatt): retrieve shader file names from filepath
    shader->vertex_name = hf_remove_file_path(vertex_path);
    shader->fragment_name = hf_remove_file_path(fragment_path);
    
    hf_gl_compile_shader(shader->vertex_id, shader->vertex_shader, shader->vertex_name, shader->verbose_compiling);
    hf_gl_compile_shader(shader->fragment_id, shader->fragment_shader, shader->fragment_name, shader->verbose_compiling);
    
    glAttachShader(shader->program_id, shader->vertex_id);
    glAttachShader(shader->program_id, shader->fragment_id);
    
    hf_gl_link_and_validate_shader(shader->program_id);
    
    
    hf_log("[HF] compiled shader: [(%s), vertex: (%s), fragment: (%s)]\n", shader->name, shader->vertex_name, shader->fragment_name);
}

void hf_shader_bind(hf_shader* shader){
    glUseProgram(shader->program_id);
}

void hf_shader_unbind(){
    glUseProgram(0);
}

u32 hf_shader_get_uniform_location(hf_shader* shader, const char* name){
    return glGetUniformLocation(shader->program_id, name);
}

u32 hf_shader_get_attribute_location(hf_shader* shader, const char* name){
    return glGetAttribLocation(shader->program_id, name);
}

void hf_shader_destroy(hf_shader* shader){
    glDetachShader(shader->program_id, shader->vertex_id);
    glDetachShader(shader->program_id, shader->fragment_id);
    glDeleteShader(shader->vertex_id);
    glDeleteShader(shader->fragment_id);
    glDeleteShader(shader->program_id);
    
    hf_free(shader->vertex_shader);
    hf_free(shader->fragment_shader);
    hf_free(shader->vertex_name);
    hf_free(shader->fragment_name);
}

void hf_shader_set_uniform_u32(hf_shader* shader, const char* name, u32 data){
    glUniform1f(hf_shader_get_uniform_location(shader, name), data);
}

void hf_shader_set_uniform_b8(hf_shader* shader, const char* name, b8 data){
    glUniform1f(hf_shader_get_uniform_location(shader, name), data ? (GLfloat)1 : (GLfloat)0);
}

void hf_shader_set_uniform_f32(hf_shader* shader, const char* name, f32 data){
    glUniform1f(hf_shader_get_uniform_location(shader, name), data);
}

void hf_shader_set_uniform_v2f(hf_shader* shader, const char* name, v2f* data){
    glUniform2f(hf_shader_get_uniform_location(shader, name), data->x, data->y);
    
}

void hf_shader_set_uniform_v3f(hf_shader* shader, const char* name, v3f* data){
    glUniform3f(hf_shader_get_uniform_location(shader, name), data->x, data->y, data->z);
    
}

void hf_shader_set_uniform_v4f(hf_shader* shader, const char* name, v4f* data){
    glUniform4f(hf_shader_get_uniform_location(shader, name), data->x, data->y, data->z, data->w);
    
}

void hf_shader_set_uniform_m4f(hf_shader* shader, const char* name, m4f* data){
    hf_f32_buf buffer = {};
    hf_f32_buf_init(&buffer, 16);
    
    hf_f32_buf_store_m4f(&buffer, data);
    glUniformMatrix4fv(hf_shader_get_uniform_location(shader, name), 1, 0, buffer.data);
    
    hf_f32_buf_destroy(&buffer);
    
}

