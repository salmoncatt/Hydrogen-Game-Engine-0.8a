/* date = October 16th 2021 10:22 am */

#ifndef HFMEMUTIL_H
#define HFMEMUTIL_H

typedef struct hf_allocation{
    
    const void* data;
    const char* file;
    const char* func;
    u64 line;
    
    
}hf_allocation;

void hf_mem_util_start();


extern void* __real_malloc(u64 bytes);
//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line);
extern void* __wrap_malloc(u64 bytes);

extern void __real_free(void* data);
//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line);
extern void __wrap_free(void* data);

#define hf_malloc(bytes) malloc(bytes);
#define hf_free(data) free(data);

//#define hf_malloc(bytes) hf_malloc_func(bytes, __FILE__, __FUNCTION__, __LINE__);

//extern void hf_free(void* pointer);


void hf_add_mem_allocation(hf_allocation* allocation);

void hf_remove_mem_allocation(hf_allocation* allocation);

void hf_mem_util_close();


#endif //HFMEMUTIL_H
