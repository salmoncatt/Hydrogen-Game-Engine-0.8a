#include "hfmesh.h"
#include "../opengl/hfgl.h"

void hf_mesh_create(hf_mesh* mesh){
    if(mesh->type == 0)
        mesh->type = 3; // NOTE(salmoncatt): auto default to 3d mesh
    mesh->vao = hf_generate_VAO();
    //glGenBuffers(0, NULL);
    
    if(mesh->vertices.size > 0)
        hf_push_data_to_VBO(0, mesh->type, (f32*)(mesh->vertices.data), mesh->vertices.size);
    
    if(mesh->texture_coords.size > 0){
        hf_push_data_to_VBO(1, 2, (f32*)(mesh->texture_coords.data), mesh->texture_coords.size);
    }
    
    if(mesh->indices.size > 0){
        mesh->ibo = hf_generate_VBO();
        hf_push_data_to_IBO((u32*)(mesh->indices.data), mesh->indices.size, mesh->ibo);
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
    //hf_array_free(mesh->vertices.data);
    hf_array_free(mesh->texture_coords.data);
    //hf_array_free(mesh->indices.data);
    mesh->created = 0;
    //glDeleteVertexArrays(1, &mesh->vao);
}

hf_mesh hf_mesh_load_from_file(const char* file_path){
    
}