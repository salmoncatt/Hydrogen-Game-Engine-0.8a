#include "hftime.h"


#ifdef _WIN32

f64 hf_cpu_freq; //only for windows
i64 hf_time_start;

#elif defined(__linux__)

struct timeval hf_time_start;

#endif

f64 hf_fps_smoothing;

f64 hf_frame_time;
f64 hf_last_frame_time;
f64 hf_last_fps;
f64 hf_sleep_time;


void hf_time_init(f64 fps_smoothing){
    hf_fps_smoothing = fps_smoothing;
    
#ifdef _WIN32
    LARGE_INTEGER query; 
    
    if(!QueryPerformanceFrequency(&query))
        hf_err("QueryPerformanceFrequency failed!\n");
    
    hf_cpu_freq = (f64)((query.QuadPart) / 1000.0);
    
    QueryPerformanceCounter(&query);
    hf_time_start = query.QuadPart;
    
    timeBeginPeriod(1); //this increases sleeps resolution to 1ms
#elif defined(__linux__)
    
    //hf_time_start = (f64)clock();
    gettimeofday(&hf_time_start, NULL);
    hf_frame_time = 0;
    //clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &hf_time_start);
    
#endif
    
    printf("[HF TIME] intialized time functions\n");
}



//returns time elapsed in milli
f64 hf_get_time(){
#ifdef _WIN32
    LARGE_INTEGER query;
    QueryPerformanceCounter(&query);
    
    return (f64)((query.QuadPart - hf_time_start) / hf_cpu_freq);
    
#elif defined(__linux__)
    
    struct timeval current_time, elapsed_time;
    
    gettimeofday(&current_time, NULL);
    timersub(&current_time, &hf_time_start, &elapsed_time);
    
    f64 time = (((f64)elapsed_time.tv_sec) + ((f64)elapsed_time.tv_usec / 1000000.0)) * 1000.0;
    
    return time;
    //return ((f64)clock() - hf_time_start) / (f64)(CLOCKS_PER_SEC) * 1000;
    
#endif
}

void hf_time_update(){
    hf_frame_time = (f64)((hf_get_time() - hf_last_frame_time) / 1000);
    hf_last_frame_time = hf_get_time();
}

f64 hf_get_delta_time(){
    return hf_frame_time;
}

f64 hf_get_fps(){
    //hf_last_fps = 1.0 / hf_get_delta_time();
    hf_last_fps = hf_lerp(hf_last_fps, 1.0 / hf_get_delta_time(), hf_fps_smoothing);
    
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
    
#ifdef _WIN32
    if(milli >= 1)
        Sleep((DWORD)milli);
#elif defined(__linux__)
    if (milli >= 1000)
        sleep(milli / 1000);
    usleep(((i64)milli % (i64)1000) * 1000);
#endif
    
    while(hf_get_time() < end){
        
    }
    
    return;
}