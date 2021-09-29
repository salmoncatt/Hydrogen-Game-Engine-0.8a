#include "hftime.h"

/* 
f64 hf_cpu_freq;
i64 hf_time_start;
 */

void hf_time_init(hf_app* app){
    LARGE_INTEGER query; 
    
    if(!QueryPerformanceFrequency(&query))
        hf_err("QueryPerformanceFrequency failed!\n");
    
    app->cpu_freq = (f64)((query.QuadPart) / 1000.0);
    
    QueryPerformanceCounter(&query);
    app->time_start = query.QuadPart;
}


f64 hf_get_time(hf_app* app){
    LARGE_INTEGER query;
    QueryPerformanceCounter(&query);
    
    return (f64)((query.QuadPart - app->time_start) / app->cpu_freq);
}

void hf_time_update(hf_app* app){
    
}

f64 hf_get_delta_time(hf_app* app){
    
}