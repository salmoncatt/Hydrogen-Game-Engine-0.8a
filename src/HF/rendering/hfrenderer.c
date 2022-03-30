#include "hfrenderer.h"

hf_debug_camera hf_renderer_cam = { .sensitivity = 0.04f, .movement_speed = 10};
m4f hf_renderer_proj_mat = {};;

void hf_renderer_init(hf_app* app) {
    hf_log("[HF] initializing HF Renderer...\n");
    
    char* cpu = hf_get_cpu_name();
    hf_log("[HF] OpenGL Vendor: [%s]\n", glGetString(GL_VENDOR));
    hf_log("[HF] OpenGL Version: [%s]\n", glGetString(GL_VERSION));
    hf_log("[HF] GPU: [%s]\n", glGetString(GL_RENDERER));
    hf_log("[HF] CPU: [%s]\n", cpu);
    hf_free(cpu);
    
    hf_renderer_proj_mat = hf_perspective_m4f(app->window.width, app->window.height, 90, 0.1f, 1000);
    
    
    hf_log("[HF] initialized HF Renderer\n\n");
}

void hf_renderer_destroy(hf_app* app) {
    hf_log("[HF] destroyed HF Renderer\n");
}

void hf_render_mesh(hf_mesh* mesh, hf_shader* shader, hf_transform* transform){
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
    m4f view = hf_view_m4f(hf_renderer_cam.transform.pos, hf_renderer_cam.transform.rot);
    hf_shader_set_uniform_m4f(shader, "transform", &transformation);
    hf_shader_set_uniform_m4f(shader, "view", &view);
    hf_shader_set_uniform_m4f(shader, "projection", &hf_renderer_proj_mat);
    //position
    
    if(mesh->indices_size)
        glDrawElements(GL_TRIANGLES, mesh->indices_size, GL_UNSIGNED_INT, 0);
    else if(mesh->vertices_size)
        glDrawArrays(GL_TRIANGLES, 0, (int)(mesh->vertices_size / mesh->type));
    
    
    hf_shader_unbind(shader);
    
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glBindVertexArray(0);
}

