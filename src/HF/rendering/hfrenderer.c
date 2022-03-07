#include "hfrenderer.h"

void hf_renderer_init(hf_app* app) {
    hf_log("[HF] initialized HF Renderer\n");
}

void hf_renderer_destroy(hf_app* app) {
    hf_log("[HF] destroyed HF Renderer\n");
}

void hf_render_mesh(hf_mesh* mesh, hf_transform transform){
    glBindVertexArray(mesh->vao);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, (int)(mesh->vertices_size / mesh->type));
    
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}

