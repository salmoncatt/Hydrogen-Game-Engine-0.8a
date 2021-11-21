#include "hfmesh.h"
#include "../opengl/hfgl.h"

void hf_mesh_create(hf_mesh* mesh){
    
    hf_generate_VBO();
    //glGenBuffers(0, NULL);
    
    //if(!hf_vector_empty(&mesh->vertices))
    //hf_push_data_to_VBO(0, mesh->type, &mesh->vertices);
    
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