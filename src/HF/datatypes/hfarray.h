/* date = March 7th 2022 11:48 am */

#ifndef HFARRAY_H
#define HFARRAY_H

#define HF_ARRAY_INIT_CAPACITY 10

typedef struct hf_array{
	void* data;
    u64 size;
    u64 capacity;
    u32 data_size;
    
} hf_array;


void hf_array_init(hf_array* array);

b8 hf_array_resize(hf_array* array, u64 capacity, u32 data_size);

b8 hf_array_push_back(hf_array* array, void* in);

b8 hf_array_free(hf_array* array);

#endif //HFARRAY_H
