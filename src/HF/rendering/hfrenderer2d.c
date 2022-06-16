#include "hfrenderer2d.h"

hf_mesh hf_renderer_quad = {};
hf_shader hf_gui_rect_shader = {};


void hf_renderer_init_2d(hf_app* app) {
    f32 hf_quad_vertices[] = {0, 1, 0, 0, 1, 1, 1, 0};
    
    hf_renderer_quad.type = 2; //2d
    hf_renderer_quad.vertices = hf_array_create_from_data(&hf_quad_vertices, f32, 8);
    hf_mesh_create(&hf_renderer_quad);
    
    hf_gui_rect_shader.name = "gui rect shader";
    hf_shader_create(&hf_gui_rect_shader, "../res/shaders/gui_rect_vertex.glsl", "../res/shaders/gui_rect_fragment.glsl");
    
    hf_log("[HF] initialized HF Renderer 2D\n\n");
}

void hf_renderer_destroy_2d(hf_app* app) {
    hf_mesh_destroy(&hf_renderer_quad);
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

void hf_render_rect(u32 x, u32 y, u32 w, u32 h, v4f color){
    if(w == 0 || h == 0){
        return; //dont waste a draw call on an empty rectangle
    }
    
    glBindVertexArray(hf_renderer_quad.vao);
    glEnableVertexAttribArray(0);
    
    hf_shader_bind(&hf_gui_rect_shader);
    
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);//very important
    
    /* 
        if(mesh->texture.image.data != NULL){
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, mesh->texture.texture_id);
        }
     */
    
    m4f transformation = hf_transformation_m4f_2d(hf_v2f(x, y), 0, hf_v2f(w, h));
    m4f model_proj = hf_mul_m4f(hf_renderer_pixel_ortho, transformation);
    hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &model_proj);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "transform", &transformation);
    hf_shader_set_uniform_v4f(&hf_gui_rect_shader, "color", &color);
    //hf_shader_set_uniform_m4f(&hf_gui_rect_shader, "proj", &hf_renderer_pixel_ortho);
    //position
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (u32)(hf_array_size(hf_renderer_quad.vertices)) / 2);
    
    
    hf_shader_unbind(&hf_renderer_quad);
    
    glEnable(GL_CULL_FACE);//very important
    glEnable(GL_DEPTH_TEST);
    
    
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

/* 
void hf_render_rect_ss(hf_button* button){
    
}
 */