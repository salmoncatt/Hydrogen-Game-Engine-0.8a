#include "hfmesh.h"
#include "../opengl/hfgl.h"

void hf_mesh_create(hf_mesh* mesh){
    
    mesh->vao = hf_generate_VAO();
    //glGenBuffers(0, NULL);
    
    if(mesh->vertices_size)
        hf_push_data_to_VBO(0, mesh->type, mesh->vertices, mesh->vertices_size);
    
    if(mesh->texture_coords_size){
        hf_push_data_to_VBO(1, 2, mesh->texture_coords, mesh->texture_coords_size);
    }
    
    if(mesh->indices_size > 0){
        mesh->ibo = hf_generate_VBO();
        hf_push_data_to_IBO(mesh->indices, mesh->indices_size, mesh->ibo);
    }
    
    
    
    //if(!hf_vector_empty(&mesh->texture_coords))
    //hf_push_data_to_VBO(0, 2, &mesh->texture_coords);
    
    // TODO(salmoncatt): normals
    
    /* 
        if(!hf_vector_empty(&mesh->indices))
            hf_push_data_to_IBO(&mesh->indices, );
     */
    
    mesh->created = 1;
}

void hf_mesh_destroy(hf_mesh* mesh){
    
}