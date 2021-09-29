#include "hfapp.h"
#include "../time/hftime.h"

void hf_app_init(hf_app* app){
    app->cpu_freq = 0;
    app->time_start = 0;
    
#ifdef HF_DONT_BUFFER_STDOUT
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
}

void hf_app_start(hf_app* app){
    hf_time_init(app);
}