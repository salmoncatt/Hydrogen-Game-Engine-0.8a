#include "hfmemutil.h"
#include "../datatypes/hfvector.h"
#include <malloc.h>
#include <dbghelp.h>

hf_app* hf_MLD_current_app;

void hf_MLD_start(hf_app* app){
    hf_log("starting MLD for app: %s\n", app->name);
    
    hf_MLD_current_app = app;
    hf_vector_init(&app->allocations);
}

//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line){
extern void* __wrap_malloc(u64  bytes){
    void* out = __real_malloc(bytes);
    
    if(out){
#ifdef HF_DEBUG
        void* stack[ 100 ];
        u16 frames;
        SYMBOL_INFO* symbol;
        HANDLE process;
        
        process = GetCurrentProcess();
        
        SymInitialize(process, NULL, TRUE);
        
        frames = CaptureStackBackTrace(0, 100, stack, NULL);
        symbol = (SYMBOL_INFO*) calloc(sizeof(SYMBOL_INFO) + 256 * sizeof(char), 1);
        symbol->MaxNameLen = 255;
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        
        DWORD displacement;
        IMAGEHLP_LINE64 line;
        line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);
        
        
        
        hf_allocation* allocation = (hf_allocation*)__real_malloc(sizeof(hf_allocation));
        allocation->data = out; 
        allocation->bytes = bytes;
        allocation->num_of_back_traces = frames;
        
        
        allocation->files = __real_malloc(sizeof(void*) * frames);
        allocation->funcs = __real_malloc(sizeof(void*) * frames);
        allocation->lines = __real_malloc(sizeof(void*) * frames);
        
        
        for(u32 i = 0; i < frames; i++ )
        {
            
            DWORD64 address = (DWORD64)(stack[i]);
            SymFromAddr(process, address, 0, symbol);
            
            if(SymGetLineFromAddr64(process, address, &displacement, &line)){
                allocation->files[i] = __real_malloc(hf_strlen(line.FileName) + 1);
                hf_strcpy(allocation->files[i], line.FileName, 0);
                
                allocation->funcs[i] = __real_malloc(hf_strlen(symbol->Name) + 1);
                hf_strcpy(allocation->funcs[i], symbol->Name, 0);
                
                //allocation->lines[i] = (u64)__real_malloc(sizeof(u64));
                allocation->lines[i] = (u64)line.LineNumber;
                //hf_memcpy(&allocation->lines[i], &file.LineNumber, sizeof(u64));
                
                //printf("%i: %s - 0x%pS, file: %s, line: %lu\n", frames - i - 1, symbol->Name, symbol->Address, line.FileName, line.LineNumber);
            }
            
            /* 
                        else{
                            printf("%i:%s - 0x%pS\n", frames - i - 1, symbol->Name, symbol->Address);
                        }
             */
            
            
            
        }
        
        hf_add_mem_allocation(allocation);
        
        __real_free(symbol);
        //__debugbreak();
#endif
        
        return out;
    }
    else{
        hf_err("hf_malloc failed to allocate: %I64U bytes", bytes);
        return NULL;
    }
    
}

extern void __wrap_free(void* pointer){
    
#ifdef HF_DEBUG
    
    printf("freed:\n");
    if(hf_MLD_current_app != NULL)
        printf("freed good\n\n");
    
#endif
    
    __real_free(pointer);
}


void hf_add_mem_allocation(hf_allocation* allocation){
    // TODO(salmoncatt): add realloc bc it changes the pointer and MLD will lose track of it
    
    //hf_vector_push_back(&hf_MLD_current_app->allocations, allocation);
    printf("test:\n");
    if(hf_MLD_current_app != NULL){
        printf("good\n\n");
        //hf_vector_push_back(&hf_MLD_current_app->allocations, allocation);
        
        printf("allocation stack: \n");
        
        for(u32 i = 0; i < allocation->num_of_back_traces; ++i){
            printf("allocation: %s, %s, %i with bytes: %lu\n", allocation->files[i], allocation->funcs[i], allocation->lines[i], allocation->bytes);
        }
    }
    
    __real_free(allocation);
}

void hf_remove_mem_allocation(hf_allocation* allocation){
    //hf_vector_erase(&hf_MLD_current_app->allocations, hf_vector_find(&hf_MLD_current_app->allocations, allocation), 1);
}

void hf_MLD_close(hf_app* app){
    hf_log("closing MLD for app: %s\n", app->name);
    
    hf_vector_free(&app->allocations);
}