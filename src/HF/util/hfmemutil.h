/* date = October 16th 2021 10:22 am */

#ifndef HFMEMUTIL_H
#define HFMEMUTIL_H

#include "../datatypes/hfvector.h"

typedef struct hf_allocation{
    
    void* data;
    char** files;
    char** funcs;
    u64* lines;
    u64 num_of_back_traces;
    u64 bytes;
    u64 allocation_num;
    
}hf_allocation;

//extern hf_app* hf_MLD_current_app;
extern hf_vector hf_MLD_allocations;
extern u64 hf_mem_util_bytes_allocated;
extern u64 hf_mem_util_bytes_leftover;
extern u64 hf_mem_util_num_allocated;

// NOTE(salmoncatt): MLD = memory leak detector
#ifdef HF_DEBUG
void hf_MLD_start() __attribute__ ((constructor));
#else
void hf_MLD_start();
#endif
//void hf_MLD_start(hf_app* app);

extern void* __real_malloc(u64 bytes);
//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line);
extern void* __wrap_malloc(u64 bytes);

extern void __real_free(void* data);
//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line);
extern void __wrap_free(void* data);

#define hf_malloc(bytes) malloc(bytes)
#define hf_free(data) free(data)

//#define hf_malloc(bytes) hf_malloc_func(bytes, __FILE__, __FUNCTION__, __LINE__);

//extern void hf_free(void* pointer);


void hf_add_mem_allocation(hf_allocation* allocation);

void hf_remove_mem_allocation(void* pointer);

#ifdef HF_DEBUG
void hf_MLD_stop() __attribute__ ((destructor));
#else
void hf_MLD_stop();
#endif
//void hf_MLD_close(hf_app* app);


#endif //HFMEMUTIL_H
