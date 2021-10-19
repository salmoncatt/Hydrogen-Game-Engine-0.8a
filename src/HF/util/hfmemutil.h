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

void hf_add_mem_allocation(hf_allocation* allocation);

void hf_remove_mem_allocation(hf_allocation* allocation);

void hf_mem_util_close();


#endif //HFMEMUTIL_H
