/* date = August 28th 2021 9:30 am */

#ifndef HFVECTOR_H
#define HFVECTOR_H

#define HF_VECTOR_INIT_CAPACITY 10
#define HF_SUCCESS 1
#define HF_FAIL 0

typedef struct hf_vector{
	void** data;
    u64 size;
    u64 capacity;
    u64 init_capacity;
    b8 should_free_on_delete;
} hf_vector;


void hf_vector_init(hf_vector* vector);

b8 hf_vector_resize(hf_vector* vector, u64 capacity);

b8 hf_vector_push_back(hf_vector* vector, void* in);

b8 hf_vector_set(hf_vector* vector, u64 index, void* in);

b8 hf_vector_empty(hf_vector* vector);

void* hf_vector_get(hf_vector* vector, u64 index);

b8 hf_vector_erase(hf_vector* vector, u64 index, u64 length);

b8 hf_vector_free(hf_vector* vector);

b8 hf_vector_free_double_vector(hf_vector* vector);

u64 hf_vector_find(hf_vector* vector, void* pointer);

u64 hf_vector_find_value(hf_vector* vector, void* value);

#endif //HFVECTOR_H
