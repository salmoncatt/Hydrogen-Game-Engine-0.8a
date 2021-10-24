#include "hfmemutil.h"
#include <malloc.h>
#include <dbghelp.h>

void hf_mem_util_start(){
    
}

//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line){
extern void* __wrap_malloc(u64  bytes){
    void* out = __real_malloc(bytes);
    
    if(out){
#ifdef HF_DEBUG
        HANDLE process;
        u16 frames;
        SYMBOL_INFO* symbol;
        void* stack[100];
        
        
        process = GetCurrentProcess();
        SymInitialize(process, NULL, 1);
        
        frames = CaptureStackBackTrace(0, 100, stack, NULL);
        symbol = (SYMBOL_INFO*) calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        
        for(u16 i = 0; i < frames; ++i){
            SymFromAddr(process, (DWORD64)(stack[i]), 0, symbol);
            
            printf( "%i: %s - 0x%0X\n", frames - i - 1, symbol->Name, symbol->Address );
        }
        
        
        //printf("allocated memory\n");
#endif
        /* 
                                        hf_allocation allocation = {};
                                        allocation.file = file;
                                        allocation.func = function;
                                        allocation.line = line;
                                        
                                        hf_add_mem_allocation(&allocation);
                                 */
        
        return out;
    }
    else{
        hf_err("hf_malloc failed to allocate: %I64U bytes", bytes);
        return NULL;
    }
    
}

extern void __wrap_free(void* pointer){
    
#ifdef HF_DEBUG
    
    printf("freed memory\n");
    
#endif
    
    __real_free(pointer);
}


void hf_add_mem_allocation(hf_allocation* allocation){
    printf("allocation: %s, %s, %i\n", allocation->file, allocation->func, allocation->line);
    printf ("Caller name: %pS\n", __builtin_return_address(0));
}

void hf_remove_mem_allocation(hf_allocation* allocation){
    
}

void hf_mem_util_close(){
    
}