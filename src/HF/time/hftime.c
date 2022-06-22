#include "hftime.h"


f64 hf_cpu_freq;
i64 hf_time_start;
f64 hf_fps_smoothing;

f64 hf_frame_time;
f64 hf_last_frame_time;
f64 hf_last_fps;
f64 hf_sleep_time;


void hf_time_init(f64 fps_smoothing){
    LARGE_INTEGER query; 
    
    if(!QueryPerformanceFrequency(&query))
        hf_err("QueryPerformanceFrequency failed!\n");
    
    hf_cpu_freq = (f64)((query.QuadPart) / 1000.0);
    
    QueryPerformanceCounter(&query);
    hf_time_start = query.QuadPart;
    
    hf_fps_smoothing = fps_smoothing;
    
    timeBeginPeriod(1); //this increases sleeps resolution to 1ms
}


f64 hf_get_time(){
    LARGE_INTEGER query;
    QueryPerformanceCounter(&query);
    
    return (f64)((query.QuadPart - hf_time_start) / hf_cpu_freq);
}

void hf_time_update(){
    hf_frame_time = (f64)((hf_get_time() - hf_last_frame_time) / 1000);
    hf_last_frame_time = hf_get_time();
}

f64 hf_get_delta_time(){
    return hf_frame_time;
}

u32 hf_get_fps(){
    //hf_last_fps = 1 / hf_get_delta_time();
    hf_last_fps = hf_lerp(hf_last_fps, 1 / hf_get_delta_time(), hf_fps_smoothing);
    
    return hf_last_fps;
}

void hf_limit_fps(f64 fps){
    f64 wait_time = (f64)(1000 / fps);
    hf_sleep_time = wait_time - hf_get_delta_time();
    
    if(hf_sleep_time > 0)
        hf_sleep(hf_sleep_time);
}

void hf_sleep(f64 milli){
    f64 start = hf_get_time();
    f64 end = start + milli;
    
    //hf_log("%u\n", (DWORD)milli);
    
    if(milli >= 1)
        Sleep((DWORD)milli);
    
    while(hf_get_time() < end){
        
    }
    
    return;
}