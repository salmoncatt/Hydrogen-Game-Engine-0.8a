/* date = March 7th 2022 11:48 am */

#ifndef HFARRAY_H
#define HFARRAY_H

#define HF_ARRAY_INIT_CAPACITY 10

typedef struct hf_array{
	void* data;
    u64 size;
    u64 capacity;
    u64 init_capacity;
    u32 data_size;
    const char* type_name;
    
    
} hf_array;


//bro doesn't even know how to use his own data structure lol
/*example:
((f32*)test_array.data)[0] = 69420;
    hf_log("%f\n", ((f32*)test_array.data)[0]);
*/

void hf_internal_array_init(hf_array* array, u32 data_size, const char* name);
#define hf_array_init(array, type) hf_internal_array_init(array, sizeof(type), #type)


b8 hf_array_resize(hf_array* array, u64 capacity);

//b8 hf_array_push_back(hf_array* array, void* in);

b8 hf_array_free(hf_array* array);

#endif //HFARRAY_H
