#include "hfmesh.h"

void hf_mesh_create(hf_mesh* mesh){
    
    if(!hf_vector_empty(&mesh->vertices))
        hf_push_data_to_VBO(0, mesh->type, &mesh->vertices);
    
    if(!hf_vector_empty(&mesh->texture_coords))
        hf_push_data_to_VBO(0, 2, &mesh->texture_coords);
    
    // TODO(salmoncatt): normals
    
    /* 
        if(!hf_vector_empty(&mesh->indices))
            hf_push_data_to_IBO(&mesh->indices, );
     */
    
}

void hf_mesh_destroy(hf_mesh* mesh){
    
}