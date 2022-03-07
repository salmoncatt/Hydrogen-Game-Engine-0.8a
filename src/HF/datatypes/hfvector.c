#include "hfvector.h"
//#include "hfpch.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include "../util/hfutil.h"
//#include <immintrin.h>

void hf_vector_init(hf_vector* vector) {
    if(vector->capacity == 0){
        if(vector->data == NULL){
            if(vector->init_capacity == 0)
                vector->capacity = HF_VECTOR_INIT_CAPACITY;
            else
                vector->capacity = vector->init_capacity;
            
            vector->data = hf_malloc(sizeof(void*) * vector->capacity);
            vector->size = 0;
        }
    }
}

b8 hf_vector_resize(hf_vector* vector, u64 capacity) {
	u32 status = HF_FAIL;
    
	if (vector) {
        if(vector->data != NULL){
            void** data = realloc(vector->data, sizeof(void*) * capacity);
            hf_assertf(data, "Vector resize realloc failed");
            
            if (data) {
                vector->data = data;
                vector->capacity = capacity;
                status = HF_SUCCESS;
            }
        }
	}
    
	return status;
}

b8 hf_vector_push_back(hf_vector* vector, void* in) {
	u32 status = HF_FAIL;
    
	if (vector) {
		if(vector->data != NULL){
            if (vector->size >= vector->capacity) {
                status = hf_vector_resize(vector, vector->capacity * 2);
                if (status) {
                    vector->data[vector->size] = in;
                    vector->size += 1;
                }
            }
            else {
                vector->data[vector->size] = in;
                vector->size += 1;
                status = HF_SUCCESS;
            }
        }
	}
    
	return status;
}

b8 hf_vector_set(hf_vector* vector, u64 index, void* in) {
	u32 status = HF_FAIL;
    
	if (vector) {
		if(vector->data != NULL){
            if (index < vector->capacity) {
                vector->data[index] = in;
                status = HF_SUCCESS;
            }else{
                //printf("vector size: %u\n", vector->capacity);
                status = hf_vector_resize(vector, vector->capacity * 2);
                if (status) {
                    vector->data[index] = in;
                }
                status = HF_SUCCESS;
            }
            
            if(index >= vector->size)
                vector->size += 1;
            
            /* 
                        if(index < vector->size){
                            if (index < vector->capacity) {
                                vector->data[index] = in;
                                status = HF_VECTOR_SUCCESS;
                            }else{
                                status = hf_vector_resize(vector, vector->capacity * 2);
                                if (status) {
                                    vector->data[index] = in;
                                }
                                status = HF_VECTOR_SUCCESS;
                            }
                        }else{
                            if (index < vector->capacity) {
                                vector->data[index] = in;
                                status = HF_VECTOR_SUCCESS;
                                vector->size += 1;
                            }else{
                                status = hf_vector_resize(vector, vector->capacity * 2);
                                if (status) {
                                    vector->data[index] = in;
                                    vector->size += 1;
                                }
                                status = HF_VECTOR_SUCCESS;
                            }
                        }
             */
            
        }
	}
    
	return status;
}

void* hf_vector_get(hf_vector* vector, u64 index) {
	void* out = NULL;
    
	if (vector) {
        if(vector->data != NULL){
            if (index < vector->size) {
                out = vector->data[index];
            }
        }
		
	}
    
	return out;
}

b8 hf_vector_erase(hf_vector* vector, u64 index, u64 length) {
	u32 status = HF_FAIL;
    
	if (vector) {
        if(vector->data != NULL){
            if (index < vector->size && index + length <= vector->size) {
                
                hf_assertf(sizeof(float*) == 8, "Pointer is not 8 bytes, need to add fix for this");
                
                //NOTE: k so basically i was working on this for like 3 days and if you dont use & in load and store for memory addresses it doesnt like that and just kinda breaks
                while (index + 4 + length < vector->size) {
                    
                    __m256i data = _mm256_loadu_si256((const __m256i*) &vector->data[index + length]);
                    _mm256_storeu_si256((__m256i*)&vector->data[index], data);
                    
                    index += 4;
                }
                
                while (index + length < vector->size) {
                    vector->data[index] = vector->data[index + length];
                    vector->data[index + length] = NULL;
                    index += 1;
                }
                
                vector->size -= length;
                
                if (vector->size > 0 && vector->size <= vector->capacity / 4) {
                    status = hf_vector_resize(vector, vector->capacity / 2);
                }
                else
                    status = HF_SUCCESS;
            }
        }
		
	}
    
	return status;
}

b8 hf_vector_free(hf_vector* vector) {
    u32 status = HF_FAIL;
    
	if (vector) {
        if(vector->data != NULL){
            for(u64 i = 0; i < vector->size; i++){
                /* 
                                if(i == 9997)
                                    printf("0x%pS\n", vector->data[i]);
                 */
                free(vector->data[i]);
            }
            free(vector->data);
            vector->data = NULL;
            vector->size = 0;
            vector->capacity = 0;
            status = HF_SUCCESS;
        }
	}
    
	return status;
}

b8 hf_vector_free_double_vector(hf_vector* vector){
    u32 status = HF_FAIL;
    
	if (vector) {
        if(vector->data != NULL){
            for(u64 i = 0; i < vector->size; i++){
                hf_vector_free((hf_vector*)vector->data[i]);
            }
            free(vector->data);
            vector->data = NULL;
            vector->size = 0;
            vector->capacity = 0;
            status = HF_SUCCESS;
        }
	}
    
	return status;
}


u64 hf_vector_find(hf_vector* vector, void* pointer){
    
    for(u64 i = 0; i < vector->size; i++){
        if(pointer == vector->data[i]){
            //printf("%p, %p\n", pointer, vector->data[i]);
            return i;
        }
    }
    
    
    
    /* 
        __m128i* mm_data = (__m128i*)(vector->data);
        __m128i mm_pointer = _mm_set_epi64x((u64)(pointer), (u64)(pointer));
        //__m128i mm_pointer = _mm_loadu_si128((__m128i*)(pointer));
        u64 out = vector->size;
        
        for(u64 i = 0; i < vector->size - 2; i += 2, mm_data++){
            __m128i current = _mm_loadu_si128(mm_data);
            __m128i comparision = _mm_cmpeq_epi64(current, mm_pointer);
            u32 mask = _mm_movemask_epi8(comparision);
            
            if(mask){
                return i + (hf_ctzu32(mask) / 8);
            }
            
        }
     */
    
    return vector->size;
}

b8 hf_vector_empty(hf_vector* vector){
    return (vector->size == 0);
}

u64 hf_vector_find_value(hf_vector* vector, void* value){
    
}