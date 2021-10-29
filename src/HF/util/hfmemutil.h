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
    
}hf_allocation;

//extern hf_app* hf_MLD_current_app;
extern hf_vector hf_MLD_allocations;
//extern u32 called_amount;

// NOTE(salmoncatt): MLD = memory leak detector
void hf_MLD_start();
//void hf_MLD_start(hf_app* app);

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

void hf_MLD_close();
//void hf_MLD_close(hf_app* app);


#endif //HFMEMUTIL_H
