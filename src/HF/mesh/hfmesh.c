#include "hfmesh.h"
#include "../opengl/hfgl.h"

void hf_mesh_create(hf_mesh* mesh){
    if(mesh->type == 0)
        mesh->type = 3; // NOTE(salmoncatt): auto default to 3d mesh
    mesh->vao = hf_generate_VAO();
    //glGenBuffers(0, NULL);
    
    if(hf_array_size(mesh->vertices) > 0){
        hf_push_data_to_VBO(0, mesh->type, mesh->vertices, hf_array_size(mesh->vertices));
    }
    
    if(hf_array_size(mesh->texture_coords) > 0){
        hf_push_data_to_VBO(1, 2, mesh->texture_coords, hf_array_size(mesh->texture_coords));
    }
    
    if(hf_array_size(mesh->indices) > 0){
        mesh->ibo = hf_generate_VBO();
        hf_push_data_to_IBO(mesh->indices, hf_array_size(mesh->indices), mesh->ibo);
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
    hf_array_free(mesh->vertices);
    hf_array_free(mesh->texture_coords);
    hf_array_free(mesh->indices);
    mesh->created = 0;
    glDeleteVertexArrays(1, &mesh->vao);
}

hf_mesh hf_mesh_load_from_file(const char* file_path){
    char* file_name = hf_remove_file_path(file_path);
    FILE* file = fopen(file_path, "r");
    
    hf_mesh mesh = {};;
    
    if(file == NULL){
        hf_err("[HF] could not load obj mesh: [%s]\n", file_name);
        return mesh;
    }
    
    char line[512];
    
    
    float* vertices = hf_array_create(f32);
    float* texture_coords = hf_array_create(f32);
    float* normals = hf_array_create(f32);
    u32* indices = hf_array_create(u32);
    
    
    
    while(fgets(line, 512, file) != NULL){
        char header = line[0];
        
        f32 data[3];
        
        if(header != '#' && header != 'p' && header != 'f' && header != '\n'){
            char* pointer;
            
            data[0] = strtof(line + 2, &pointer);
            data[1] = strtof(pointer, &pointer);
            data[2] = strtof(++pointer, &pointer);
            
        }
        
        switch(header){
            case 'v':
            //vertices[0] = data[0];
            hf_array_push_back_val(vertices, 3.14156f);
            //printf("capacity post: %u\n", hf_array_capacity(vertices));
            //hf_array_push_back(vertices, data[1]);
            //hf_array_push_back(vertices, data[2]);
            //printf("%c %f %f %f \n", header, data[0], data[1], data[2]);
            break;
        }
        
        
        
        printf("%f\n", vertices[0]);
        //printf("works here\n");
        //hf_free(header);
    }
    
    
    hf_array_free(vertices);
    hf_array_free(texture_coords);
    hf_array_free(normals);
    hf_array_free(indices);
    
    
    
    hf_log("[HF] loaded obj model: [%s]\n\n", file_name);
    
    return mesh;
}