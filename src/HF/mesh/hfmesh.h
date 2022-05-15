/* date = August 26th 2021 8:23 pm */

#ifndef MESH_H
#define MESH_H

//#include "../datatypes/hfvector.h"

#include "hftexture.h"
#include "../datatypes/hfarray.h"

typedef struct hf_mesh{
    
    hf_texture texture;
    
    // TODO(salmoncatt): normals
    
    /* 
        hf_vector vertices;
        hf_vector texture_coords;
        hf_vector indices;
     */
    
    f32* vertices;
    //hf_array vertices; //32
    /* 
        f32* vertices;
        u32 vertices_size;
     */
    f32* texture_coords;
    //hf_array texture_coords; //32
    //u32 texture_coords_size;
    
    u32* indices;
    //hf_array indices; //u32
    //u32 indices_size;
    
    // TODO(salmoncatt): normals
    
    u32 vao;
    u32 ibo;
    
    // NOTE(salmoncatt): 2d = 2, 3d = 3
    u32 type;
    
    b8 created;
}hf_mesh;

void hf_mesh_create(hf_mesh* mesh);

void hf_mesh_destroy(hf_mesh* mesh);

hf_mesh hf_mesh_load_from_file(const char* file_path);

#endif //MESH_H
