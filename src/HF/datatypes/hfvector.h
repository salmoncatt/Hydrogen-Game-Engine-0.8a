/* date = August 28th 2021 9:30 am */

#ifndef HFVECTOR_H
#define HFVECTOR_H

#include "hfdatatypes.h"

#define HF_VECTOR_INIT_CAPACITY 10
#define HF_VECTOR_SUCCESS 1
#define HF_VECTOR_FAIL 0

typedef struct hf_vector{
	void** data;
    u64 size;
    u64 capacity;
    b8 should_free_on_delete;
    
} hf_vector;


void hfVectorInit(hf_vector* vector);

u32 hfVectorResize(hf_vector* vector, u64 capacity);

u32 hfVectorPushBack(hf_vector* vector, void* in);

u32 hfVectorSet(hf_vector* vector, u64 index, void* in);

void* hfVectorGet(hf_vector* vector, u64 index);

u32 hfVectorErase(hf_vector* vector, u64 index, u64 length);

u32 hfVectorFree(hf_vector* vector);

#endif //HFVECTOR_H
