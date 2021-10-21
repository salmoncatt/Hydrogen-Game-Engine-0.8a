#include "hfmemutil.h"
#include <malloc.h>


void hf_mem_util_start(){
    
}

void hf_add_mem_allocation(hf_allocation* allocation){
    printf("allocation: %s, %s, %i\n", allocation->file, allocation->func, allocation->line);
    printf ("Caller name: %pS\n", __builtin_return_address(0));
}

void hf_remove_mem_allocation(hf_allocation* allocation){
    
}

void hf_mem_util_close(){
    
}