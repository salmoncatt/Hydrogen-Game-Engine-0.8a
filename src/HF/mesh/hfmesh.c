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
    u32* indices = hf_array_create(u32);
    
    float* texture_coords = hf_array_create(f32);
    float* texture_coords_buffer = hf_array_create(f32);
    
    float* normals = hf_array_create(f32);
    float* normals_buffer = hf_array_create(f32);
    
    
    u32 face_index_type = 0;
    u32 line_number = 0;
    
    while(fgets(line, 512, file) != NULL){
        char header = line[0];
        
        f32 data[3];
        
        if(header != '#' && header != 'p' && header != 'f' && header != '\n'){
            char* pointer;
            
            data[0] = strtof(line + 2, &pointer);
            data[1] = strtof(pointer, &pointer);
            data[2] = strtof(++pointer, &pointer);
            
        }
        
        if(header == 'v'){
            switch(line[1]){
                case ' ': //v vertices
                hf_array_push_back(vertices, data[0]);
                hf_array_push_back(vertices, data[1]);
                hf_array_push_back(vertices, data[2]);
                break;
                case 't': //vt texture coords
                hf_array_push_back(texture_coords_buffer, data[0]);
                hf_array_push_back(texture_coords_buffer, data[1]);
                hf_array_push_back(texture_coords_buffer, data[2]);
                break;
                case 'n': //vn (normals)
                hf_array_push_back(normals_buffer, data[0]);
                hf_array_push_back(normals_buffer, data[1]);
                hf_array_push_back(normals_buffer, data[2]);
                break;
            }
        }else if(header == 'f'){
            u32 vertexIndex[3], uvIndex[3], normalIndex[3];
            u32 matches = 0;
            
            switch (face_index_type) {
                
                
                
				case(0):
                //vertices, uvs, normals
                matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                
                if (matches != 9) {
                    //vertices uvs
                    matches = sscanf(line, "f %d/%d %d/%d %d/%d", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                    
                    if (matches != 6) {
                        //vertices normals
                        matches = sscanf(line, "f %d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                        
                        if (matches != 6) {
                            hf_err("[HF] mesh: %s has incorrect formatting, please check line: %u", file_name, line_number);
                            return mesh;
                        }
                        else
                            face_index_type = 2;
                    }
                    else
                        face_index_type = 1;
                }
                
                break;
                
				case(1):
                //vertices uvs
                matches = sscanf(line, "f %d/%d %d/%d %d/%d", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                
                if (matches != 6) {
                    //vertices, uvs, normals
                    matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                    
                    if (matches != 9) {
                        //vertices normals
                        matches = sscanf(line, "f %d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                        
                        if (matches != 6) {
                            hf_err("[HF] mesh: %s has incorrect formatting, please check line: %u", file_name, line_number);
                            return mesh;
                        }
                        else
                            face_index_type = 2;
                    }
                    else
                        face_index_type = 0;
                }
                
                break;
                
				case(2):
                //vertices normals
                matches = sscanf(line, "f %d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
                
                if (matches != 6) {
                    //vertices, uvs, normals
                    matches = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
                    
                    if (matches != 9) {
                        //vertices uvs
                        matches = sscanf(line, "f %d/%d %d/%d %d/%d", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
                        
                        if (matches != 6) {
                            hf_err("[HF] mesh: %s has incorrect formatting, please check line: %u", file_name, line_number);
                            return mesh;
                        }
                        else
                            face_index_type = 1;
                    }
                    else
                        face_index_type = 0;
                }
                
                break;
            }
            
            
            switch (face_index_type) {
                
				case(0):
                for(u32 i = 0; i < 3; i++){
                    //vertex data
                    u32 indice = vertexIndex[i] - 1;
                    printf("%u\n", indice);
                    hf_array_push_back(indices, indice);
                    //hf_array_push_back(indices, indice + 1);
                    //hf_array_push_back(indices, indice + 2);
                    //texture coords
                    u32 uv = uvIndex[i] - 1;
                    hf_array_push_back(texture_coords, texture_coords_buffer[uv]);
                    hf_array_push_back(texture_coords, texture_coords_buffer[uv + 1]);
                    //normals
                    u32 normal = normalIndex[i] - 1;
                    hf_array_push_back(normals, normals_buffer[normal]);
                    hf_array_push_back(normals, normals_buffer[normal + 1]);
                    hf_array_push_back(normals, normals_buffer[normal + 2]);
                }
                break;
                
				case(1):
                for(u32 i = 0; i < 3; i++){
                    //vertex data
                    u32 indice = vertexIndex[i] - 1;
                    hf_array_push_back(indices, indice);
                    hf_array_push_back(indices, indice + 1);
                    hf_array_push_back(indices, indice + 2);
                    //texture coords
                    u32 uv = uvIndex[i] - 1;
                    hf_array_push_back(texture_coords, texture_coords_buffer[uv]);
                    hf_array_push_back(texture_coords, texture_coords_buffer[uv + 1]);
                }
                break;
                
				case(2):
                for(u32 i = 0; i < 3; i++){
                    //vertex data
                    u32 indice = vertexIndex[i] - 1;
                    hf_array_push_back(indices, indice);
                    hf_array_push_back(indices, indice + 1);
                    hf_array_push_back(indices, indice + 2);
                    //normals
                    u32 normal = normalIndex[i] - 1;
                    hf_array_push_back(normals, normals_buffer[normal]);
                    hf_array_push_back(normals, normals_buffer[normal + 1]);
                    hf_array_push_back(normals, normals_buffer[normal + 2]);
                }
                break;
                
                
            }
            
            
            
        }
        
        
        line_number += 1;
        //printf("works here\n");
        //hf_free(header);
    }
    
    //printf("%f\n", vertices[0]);
    
    //hf_array_free(vertices_buffer);
    hf_array_free(texture_coords_buffer);
    hf_array_free(normals_buffer);
    //hf_array_free(indices);
    
    mesh.vertices = vertices;
    //mesh.normals = normals;
    mesh.texture_coords = texture_coords;
    mesh.indices = indices;
    
    hf_mesh_create(&mesh);
    
    hf_log("[HF] loaded obj model: [%s]\n\n", file_name);
    
    return mesh;
}