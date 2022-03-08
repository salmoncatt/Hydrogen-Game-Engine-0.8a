/* date = September 29th 2021 6:02 pm */

#ifndef HFAPP_H
#define HFAPP_H

#define HF_DONT_BUFFER_STDOUT

#include "../datatypes/hfvector.h"
#include "../io/hfwindow.h"
#include "../ecs/hfecs.h"

#define HF_APP_CREATE_WINDOW 0x01
#define HF_APP_USE_OPENGL 0x02
#define HF_APP_USE_ECS 0x04

typedef struct hf_app{
    const char* name;
    
    hf_window window;
    
    //for MLD
    hf_vector allocations;
    
    u32 parameters;
    
    hf_ecs ecs;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    // NOTE(salmoncatt): time things
    f64 cpu_freq;
    i64 time_start;
    
    
}hf_app;

void hf_app_init(hf_app* app);

void hf_app_start(hf_app* app);

void hf_app_update(hf_app* app);

b8 hf_app_should_update(hf_app* app);

void hf_app_stop(hf_app* app);

#endif //HFAPP_H
