#include "hfmemutil.h"
//#include "../datatypes/hfvector.h"
//#include <malloc.h>
#ifdef _WIN32
#include <dbghelp.h>
#endif

//hf_app* hf_MLD_current_app;
//u32 called_amount;
hf_vector hf_MLD_allocations = {};
u64 hf_mem_util_bytes_allocated = 0;
u64 hf_mem_util_bytes_leftover = 0;
u64 hf_mem_util_num_allocated = 0;

void hf_MLD_start(){
    //hf_log("starting MLD for app: %s\n", app->name);
    printf("[HF] (DEBUG) starting MLD\n");
    
#ifndef HF_DEBUG
    printf("$hfcc{red}[$hfcc{yellow}HF$hfcc{red}] ($hfcc{yellow}ERROR$hfcc{red}) $hfcc{yellow}please compile with $hfcc{aqua}HF_DEBUG $hfcc{yellow}enabled\n");
#endif
    
    //hf_MLD_allocations = {};
    
    //hf_MLD_current_app = app;
    //hf_vector_init(&app->allocations);
    //hf_vector_init(&hf_MLD_allocations);
    
    if(hf_MLD_allocations.capacity == 0){
        printf("created mld bruh what\n");
        hf_MLD_allocations.capacity = 100;
        hf_MLD_allocations.size = 0;
        hf_MLD_allocations.data = __real_malloc(sizeof(void*) * hf_MLD_allocations.capacity);
    }
}

//extern void* __wrap_malloc(u64 bytes, const char* file, const char* function, u64 line){
extern void* __wrap_malloc(u64  bytes){
    void* out = __real_malloc(bytes);
    
    if(out){
#if defined(HF_DEBUG) && defined(_WIN32)
        //printf("malloc: 0x%pS\n", out);
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
        
        hf_mem_util_bytes_allocated += bytes;
        hf_mem_util_bytes_leftover += bytes;
        
        hf_allocation* allocation = (hf_allocation*)__real_malloc(sizeof(hf_allocation));
        allocation->data = out; 
        allocation->bytes = bytes;
        allocation->num_of_back_traces = frames;
        allocation->allocation_num = hf_mem_util_num_allocated;
        
        hf_mem_util_num_allocated += 1;
        
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
    
#if defined(HF_DEBUG) && defined(_WIN32)
    //printf("freed: 0x%pS\n", pointer);
    
    if(hf_MLD_allocations.capacity > 0){
        //printf("logged freed: 0x%pS\n", pointer);
        hf_remove_mem_allocation(pointer);
    }
    
    //printf("remove: 0x%pS - 0x%pS\n", hf_MLD_allocations.data[i], pointer)
    /* 
        if(hf_MLD_current_app != NULL)
            printf("freed good\n\n");
     */
    
#endif
    if(pointer != NULL)
        __real_free(pointer);
    pointer = NULL;
}


void hf_add_mem_allocation(hf_allocation* allocation){
    // TODO(salmoncatt): add realloc bc it changes the pointer and MLD will lose track of it
    
    if(hf_MLD_allocations.capacity == 0){
        //printf("created mld bruh what\n");
        hf_MLD_allocations.capacity = 100;
        hf_MLD_allocations.size = 0;
        hf_MLD_allocations.data = __real_malloc(sizeof(void*) * hf_MLD_allocations.capacity);
    }
    
    //hf_vector_push_back(&hf_MLD_current_app->allocations, allocation);
    //printf("test: %u\n", called_amount);
    if(hf_MLD_allocations.capacity > 0){
        //printf("logged malloc: 0x%pS\n", allocation->data);
        //printf("good\n");
        
        //if(hf_MLD_allocations.capacity > 0)
        //printf("MLD current app is good\n");
        
        
        //hf_vector gooberm  = {};
        //hf_vector_push_back(&gooberm, allocation);
        hf_vector_push_back(&hf_MLD_allocations, allocation);
        /* 
                for(u32 i = 0; i < hf_MLD_allocations.size; ++i){
                    printf("allocations: 0x%pS\n", ((hf_allocation*)hf_MLD_allocations.data[i])->data);
                }
                
                printf("\n\n");
         */
        
        /* 
                        printf("allocation stack: \n");
                        
                        
                        for(u32 i = 0; i < allocation->num_of_back_traces; ++i){
                            printf("allocation: %s, %s, %i with bytes: %lu\n", allocation->files[i], allocation->funcs[i], allocation->lines[i], allocation->bytes);
                        }
                 */
        
    }
    //called_amount += 1;
    //__real_free(allocation);
}

void hf_remove_mem_allocation(void* pointer){
    // NOTE(salmoncatt): so freaking slow
    for(u32 i = 0; i < hf_MLD_allocations.size; ++i){
        //printf("remove: 0x%pS - 0x%pS\n", hf_MLD_allocations.data[i], pointer);
        if(((hf_allocation*)hf_MLD_allocations.data[i])->data == pointer){
            hf_mem_util_bytes_leftover -= ((hf_allocation*)hf_MLD_allocations.data[i])->bytes;
            //printf("i: %u\n", i);
            //printf("removed\n");
            hf_vector_erase(&hf_MLD_allocations, i, 1);
        }
    }
    //printf("\n");
    //hf_vector_erase(&hf_MLD_allocations, hf_vector_find(&hf_MLD_allocations, allocation), 1);
}

void hf_MLD_stop(){
    //printf("closing mld\n");
    //hf_log("closing MLD for app: %s\n", app->name);
    printf("\n\nclosing MLD\n");
    printf("MLD stats:\n");
    printf("    MLD allocations leftover: %u\n", hf_MLD_allocations.size);
    printf("    MLD total bytes allocated: %lu\n", hf_mem_util_bytes_allocated);
    printf("    MLD total bytes leftover: %lu\n\n", hf_mem_util_bytes_leftover);
    printf("MLD printing leftover mallocs:\n (some may be blank because they were called by the system or something))\n");
    
    for(u32 i = 0; i < hf_MLD_allocations.size; ++i){
        
        if(hf_MLD_allocations.data[i] != NULL){
            hf_allocation* allocation = (hf_allocation*)hf_MLD_allocations.data[i];
            
            printf("(0x%pS): allocation number: [%u] \n printing stack:\n", allocation->data, allocation->allocation_num);
            for(u32 j = 1; j < allocation->num_of_back_traces - 4; ++j){
                printf("allocation: (file) [%s], (function) [%s], (line) [%i], (bytes) [%lu]\n", allocation->files[j], allocation->funcs[j], allocation->lines[j], allocation->bytes);
            }
            printf("\n");
        }
    }
    
    //hf_vector_free(&app->allocations);
    hf_vector_free(&hf_MLD_allocations);
}