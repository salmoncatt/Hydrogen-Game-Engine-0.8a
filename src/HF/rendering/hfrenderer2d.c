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
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ibo);
    
    hf_shader_bind(shader);
    hf_shader_set_uniform_v3f(shader, "pos", &transform->pos);
    
    if(mesh->texture.image.data != NULL){
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->texture.texture_id);
    }
    
    m4f transformation = hf_transformation_m4f(transform->pos, transform->rot, transform->scale);
    hf_shader_set_uniform_m4f(shader, "transform", &transformation);
    //position
    
    if(hf_array_size(mesh->indices) > 0)
        glDrawElements(GL_TRIANGLES, hf_array_size(mesh->indices), GL_UNSIGNED_INT, 0);
    else if(hf_array_size(mesh->vertices) > 0)
        glDrawArrays(GL_TRIANGLES, 0, (int)(hf_array_size(mesh->vertices) / mesh->type));
    
    
    hf_shader_unbind(shader);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}