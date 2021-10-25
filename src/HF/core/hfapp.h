/* date = September 29th 2021 6:02 pm */

#ifndef HFAPP_H
#define HFAPP_H

#define HF_DONT_BUFFER_STDOUT

#include "../datatypes/hfvector.h"

typedef struct hf_app{
    const char* name;
    
    //for MLD
    hf_vector allocations;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // NOTE(salmoncatt): time things
    f64 cpu_freq;
    i64 time_start;
    
    
}hf_app;

void hf_app_init(hf_app* app);

void hf_app_start(hf_app* app);

void hf_app_stop(hf_app* app);

#endif //HFAPP_H
