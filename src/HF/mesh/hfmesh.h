/* date = August 26th 2021 8:23 pm */

#ifndef MESH_H
#define MESH_H

//#include "../datatypes/hfvector.h"

typedef struct hf_mesh{
    
    // TODO(salmoncatt): normals
    
    /* 
        hf_vector vertices;
        hf_vector texture_coords;
        hf_vector indices;
     */
    float* vertices;
    float vertices_amount;
    // TODO(salmoncatt): normals
    
    u32 vao;
    u32 ibo;
    
    // NOTE(salmoncatt): 2d = 2, 3d = 3
    u32 type;
    
    b8 created;
}hf_mesh;

void hf_mesh_create(hf_mesh* mesh);

void hf_mesh_destroy(hf_mesh* mesh);

#endif //MESH_H
