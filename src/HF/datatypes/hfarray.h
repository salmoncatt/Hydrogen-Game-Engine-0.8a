/* date = March 7th 2022 11:48 am */

#ifndef HFARRAY_H
#define HFARRAY_H

#define HF_ARRAY_INIT_CAPACITY 10
#define HF_ARRAY_FIELDS_SIZE 3

#define HF_ARRAY_CAPACITY 0
#define HF_ARRAY_STRIDE 1
#define HF_ARRAY_SIZE 2

void* hf_internal_array_create(u64 capacity, u64 stride);
void* hf_internal_array_create_from_data(void* data, u64 stride, u64 length);
#define hf_array_create(type) hf_internal_array_create(HF_ARRAY_INIT_CAPACITY, sizeof(type))
#define hf_array_create_from_data(data, type, length) hf_internal_array_create_from_data((void*)data, sizeof(type), length)

void* hf_internal_array_push_back(void* array, void* value);
//#define hf_array_push_back(array, value) array = hf_internal_array_push_back(array, &value)
//if you use a value like 100 then typeof value will not always be the same as array so just use the type of the array for this3
#define hf_array_push_back(array, value)\
do {\
typeof (array[0]) temp = value;\
array = hf_internal_array_push_back(array, &temp);\
} while(0)

void hf_array_free(void* array);

u64 hf_array_field_get(void* array, u64 field_id);
void hf_array_field_set(void* array, u64 field_id, u64 value);

void* hf_array_resize(void* array, u64 size);

#define hf_array_capacity(array) hf_array_field_get(array, HF_ARRAY_CAPACITY)
#define hf_array_size(array) hf_array_field_get(array, HF_ARRAY_SIZE)
#define hf_array_stride(array) hf_array_field_get(array, HF_ARRAY_STRIDE)

/* 
typedef struct hf_array{
	void* data;
    u64 size;
    u64 capacity;
    u64 init_capacity;
    u32 data_size;
    const char* type_name;
    
    
} hf_array;


//bro doesn't even know how to use his own data structure lol
example:
((f32*)test_array.data)[0] = 69420;
    hf_log("%f\n", ((f32*)test_array.data)[0]);


void hf_internal_array_init(hf_array* array, u32 data_size, const char* name);
//void hf_internal_array_init_from_data(hf_array* array, u32 data_size, const char* name);
hf_array hf_internal_array_create_from_data(void* data, u32 data_size, const char* name, u32 length);
#define hf_array_init(array, type) hf_internal_array_init(array, sizeof(type), #type)
//#define hf_array_init_from_data(array)
#define hf_array_create_from_data(data, type, length) hf_internal_array_create_from_data(data, sizeof(data), #type, length)


b8 hf_array_resize(hf_array* array, u64 capacity);

//b8 hf_array_push_back(hf_array* array, void* in);

b8 hf_array_free(hf_array* array);
 */

#endif //HFARRAY_H
