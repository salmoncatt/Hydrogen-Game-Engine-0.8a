#include "hfrenderer.h"
#include "hfshader.h"

void hf_renderer_init_2d(hf_app* app) {
    hf_log("[HF] initialized HF Renderer 2D\n");
}

void hf_renderer_destroy_2d(hf_app* app) {
    hf_log("[HF] destroyed HF Renderer 2D\n");
}

void hf_render_mesh_2d(hf_mesh* mesh, hf_shader* shader, hf_transform* transform){
    glBindVertexArray(mesh->vao);
    glEnableVertexAttribArray(0);
    
    hf_shader_bind(shader);
    hf_shader_set_uniform_v3f(shader, "pos", &transform->pos);
    
    m4f transformation = hf_transformation_m4f(transform->pos, transform->rot, transform->scale);
    hf_shader_set_uniform_m4f(shader, "transform", &transformation);
    //position
    
    glDrawArrays(GL_TRIANGLES, 0, (int)(mesh->vertices_amount / mesh->type));
    
    
    hf_shader_unbind(shader);
    
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}