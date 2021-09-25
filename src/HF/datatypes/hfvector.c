#include "hfvector.h"
#include <stdlib.h>
#include <stdio.h>
#include "../util/hfutil.h"
#include <immintrin.h>

void hf_vector_init(hf_vector* vector) {
	vector->capacity = HF_VECTOR_INIT_CAPACITY;
	vector->size = 0;
	vector->data = hf_malloc(sizeof(void*) * vector->capacity);
}

b8 hf_vector_resize(hf_vector* vector, u64 capacity) {
	u32 status = HF_VECTOR_FAIL;
    
	if (vector) {
		void** data = realloc(vector->data, sizeof(void*) * capacity);
		assertf(data, "Vector resize realloc failed");
        
		if (data) {
			vector->data = data;
			vector->capacity = capacity;
			status = HF_VECTOR_SUCCESS;
		}
        
	}
    
	return status;
}

b8 hf_vector_push_back(hf_vector* vector, void* in) {
	u32 status = HF_VECTOR_FAIL;
    
	if (vector) {
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
			status = HF_VECTOR_SUCCESS;
		}
	}
    
	return status;
}

b8 hf_vector_set(hf_vector* vector, u64 index, void* in) {
	u32 status = HF_VECTOR_FAIL;
    
	if (vector) {
		if (index < vector->size) {
			vector->data[index] = in;
			status = HF_VECTOR_SUCCESS;
		}
	}
    
	return status;
}

void* hf_vector_get(hf_vector* vector, u64 index) {
	void* out = NULL;
    
	if (vector) {
		if (index < vector->size) {
			out = vector->data[index];
		}
	}
    
	return out;
}

b8 hf_vector_erase(hf_vector* vector, u64 index, u64 length) {
	u32 status = HF_VECTOR_FAIL;
    
	if (vector) {
		if (index < vector->size && index + length <= vector->size) {
            
			assertf(sizeof(float*) == 8, "Pointer is not 8 bytes, need to add fix for this");
            
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
				status = HF_VECTOR_SUCCESS;
		}
	}
    
	return status;
}

b8 hf_vector_free(hf_vector* vector) {
    u32 status = HF_VECTOR_FAIL;
    
	if (vector) {
		free(vector->data);
		vector->data = NULL;
		vector->size = 0;
		vector->capacity = 0;
		status = HF_VECTOR_SUCCESS;
	}
    
	return status;
}


u64 hf_vector_find(hf_vector* vector, void* pointer){
    /* 
        for(u64 i = 0; i < vector->size; i++){
            if(pointer == vector->data[i]){
                printf("%p, %p\n", pointer, vector->data[i]);
                return i;
            }
        }
     */
    
    
    __m128i* mm_data = (__m128i*)(vector->data);
    __m128i mm_pointer = _mm_loadu_si128((__m128i*)(pointer));
    u64 out = vector->size;
    
    for(u64 i = 0; i < vector->size - 4; i += 4, mm_data++){
        __m128i current = _mm_loadu_si128(mm_data);
        __m128i comparision = _mm_cmpeq_epi8(current, mm_pointer);
        u32 mask = _mm_movemask_epi8(comparision);
        
        if(mask){
            hf_print_bits(&mask, sizeof(mask));
            return (mask / 128) + (hf_ctzu32(mask) / 128);
            //break;
        }
        
    }
    
    return vector->size;
}

u64 hf_vector_find_value(hf_vector* vector, void* value){
    
}