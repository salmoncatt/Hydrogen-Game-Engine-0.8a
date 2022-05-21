#include "hfarray.h"


void* hf_internal_array_create(u64 capacity, u64 stride){
    u64 header_size = HF_ARRAY_FIELDS_SIZE * sizeof(u64);
    u64 data_size = capacity * stride;
    u64* array = (u64*)hf_malloc(header_size + data_size);
    array[HF_ARRAY_CAPACITY] = capacity;
    array[HF_ARRAY_STRIDE] = stride;
    array[HF_ARRAY_SIZE] = 0;
    
    return (void*)(array + HF_ARRAY_FIELDS_SIZE);
}

void* hf_internal_array_create_from_data(void* data, u64 stride, u64 length){
    u64 header_size = HF_ARRAY_FIELDS_SIZE * sizeof(u64);
    u64 data_size = (length + 10) * stride;
    u64* array = (u64*)hf_malloc(header_size + data_size);
    array[HF_ARRAY_CAPACITY] = length + 10;
    array[HF_ARRAY_STRIDE] = stride;
    array[HF_ARRAY_SIZE] = length;
    
    hf_memcpy((void*)(array + HF_ARRAY_FIELDS_SIZE), data, data_size);
    
    return (void*)(array + HF_ARRAY_FIELDS_SIZE);
}

void hf_array_free(void* array){
    if(array){
        hf_free(((u64*)(array) - HF_ARRAY_FIELDS_SIZE));
        array = NULL;
    }
}

u64 hf_array_field_get(void* array, u64 field_id){
    return ((u64*)(array) - HF_ARRAY_FIELDS_SIZE)[field_id];
}

void hf_array_field_set(void* array, u64 field_id, u64 value){
    ((u64*)(array) - HF_ARRAY_FIELDS_SIZE)[field_id] = value;
}

void* hf_array_resize(void* array, u64 capacity){
    void* temp = hf_internal_array_create(capacity, hf_array_stride(array));
    hf_memcpy(temp, array, hf_array_size(array) * hf_array_stride(array));
    hf_array_field_set(temp, HF_ARRAY_SIZE, hf_array_size(array));
    hf_array_free(array);
    
    return temp;
}

void* hf_internal_array_push_back(void* array, void* value){
    if(hf_array_size(array) >= hf_array_capacity(array)){
        array = hf_array_resize(array, hf_array_size(array) * 2);
    }
    
    hf_memcpy(array + hf_array_size(array) * hf_array_stride(array), value, hf_array_stride(array));
    hf_array_field_set(array, HF_ARRAY_SIZE, hf_array_size(array) + 1);
    
    return array;
}

/* 
void hf_internal_array_init(hf_array* array, u32 data_size, const char* name){
    if(array->capacity == 0){
        if(array->data == NULL){
            array->capacity = (array->init_capacity > 0 ? array->init_capacity : HF_ARRAY_INIT_CAPACITY);
            
            array->type_name = name;
            array->data_size = data_size;
            
            array->data = hf_malloc(array->data_size * array->capacity);
            array->size = 0;
        }
    }
}

b8 hf_array_resize(hf_array* array, u64 capacity){
    u32 status = HF_FAIL;
    
	if (array) {
        if(array->data != NULL){
            void* data = realloc(array->data, array->data_size * capacity);
            hf_assertf(data, "array  resize realloc failed");
            
            if (data) {
                array->data = data;
                array->capacity = capacity;
                status = HF_SUCCESS;
            }
        }
	}
    
	return status;
}

hf_array hf_internal_array_create_from_data(void* data, u32 data_size, const char* name, u32 length){
    hf_array array = {};
    array.data_size = data_size;
    array.capacity = length;
    array.type_name = name;
    array.size = length;
    //array.data = data;
    array.data = (void*)hf_malloc(array.size * array.capacity);
    array.data = (void*)hf_memcpy(&array.data, data, (length * data_size));
    //array->data = hf_malloc(array->data_size * array->capacity);
    
    
    return array;
}
 */

/* 
b8 hf_array_push_back(hf_array* array, void* in){
    u32 status = HF_FAIL;
    
	if (array) {
		if(array->data != NULL){
            if (array->size >= array->capacity) {
                status = hf_array_resize(array, array->capacity * 2);
                if (status) {
                    array->data[array->size] = in;
                    array->size += 1;
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
 */

/* 
b8 hf_array_free(hf_array* array){
    b8 status = HF_FAIL;
    
	if (array) {
        if(array->data != NULL){
            free(array->data);
            array->data = NULL;
            array->size = 0;
            array->capacity = 0;
            status = HF_SUCCESS;
        }
	}
    
	return status;
}
 */


/* 
void hf_array_init(hf_array* array){
    if(array->data_size > 0){
        if(array->capacity == 0){
            if(array->data == NULL){
                if(array->init_capacity == 0)
                    array->capacity = HF_ARRAY_INIT_CAPACITY;
                else
                    array->capacity = array->init_capacity;
                
                array->data = hf_malloc(data_size * vector->capacity);
                array->size = 0;
            }
        }
    }else{
        hf_err("[HF] trying to create an array without a data size, set data_size in the array, data type is [%s]\n", array->data_type);
    }
}

b8 hf_array_resize(hf_array* array, u64 capacity){
    u32 status = HF_FAIL;
    
	if (array) {
        if(array->data != NULL){
            void* data = realloc(array->data, array->data_size * capacity);
            hf_assertf(data, "Vector resize realloc failed");
            
            if (data) {
                array->data = data;
                array->capacity = capacity;
                status = HF_SUCCESS;
            }
        }
	}
    
	return status;
}

b8 hf_array_push_back(hf_array* array, void* in){
    u32 status = HF_FAIL;
    
	if (array) {
		if(array->data != NULL){
            if (array->size >= array->capacity) {
                status = hf_vector_resize(array, array->capacity * 2);
                if (status) {
                    array->data[array->size] = in;
                    array->size += 1;
                }
            }
            else {
                array->data[array->size] = in;
                array->size += 1;
                status = HF_SUCCESS;
            }
        }
	}
    
	return status;
}

b8 hf_array_set(hf_array* array, u64 index, void* in){
    u32 status = HF_FAIL;
    
	if (array) {
		if(array->data != NULL){
            if (index < array->capacity) {
                array->data[index] = in;
                status = HF_SUCCESS;
            }else{
                //printf("vector size: %u\n", vector->capacity);
                status = hf_array_resize(array, array->capacity * 2);
                if (status) {
                    array->data[index] = in;
                }
                status = HF_SUCCESS;
            }
            
            if(index >= vector->size)
                array->size += 1;
            
        }
	}
    
	return status;
}

b8 hf_array_empty(hf_array* array){
    
}

void* hf_array_get(hf_array* array, u64 index){
    
}

b8 hf_array_erase(hf_array* array, u64 index, u64 length){
    
}

b8 hf_array_free(hf_array* array){
    
}

b8 hf_array_free_double_array(hf_array* array){
    
}

u64 hf_array_find(hf_array* array, void* pointer){
    
}

u64 hf_array_find_value(hf_array* array, void* {
                            
                        }
 */