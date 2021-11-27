#include "hfrenderer.h"

void hf_render_mesh(hf_mesh* mesh, hf_transform transform){
    glBindVertexArray(mesh->vao);
    glEnableVertexAttribArray(0);
    
    glDrawArrays(GL_TRIANGLES, 0, (int)(mesh->vertices_amount / mesh->type));
    
    glDisableVertexAttribArray(0);
    glBindVertexArray(0);
}