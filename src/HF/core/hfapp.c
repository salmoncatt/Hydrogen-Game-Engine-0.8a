#include "hfapp.h"
#include "../time/hftime.h"

void hf_app_init(hf_app* app){
    app->cpu_freq = 0;
    app->time_start = 0;
    
#ifdef HF_DONT_BUFFER_STDOUT
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    hf_time_init(app);
    //app->window = {0};
    
    
    hf_window_init(&app->window);
    
    //hf_gl_init();
}

void hf_app_start(hf_app* app){
    hf_app_init(app);
    //hf_MLD_start(app);
}

void hf_app_update(hf_app* app){
    hf_input_update();
}

b8 hf_app_should_update(hf_app* app){
    hf_app_update(app);
    return hf_should_window_update(&app->window);
}

void hf_app_stop(hf_app* app){
    hf_destroy_window(&app->window);
    hf_gl_close();
    //hf_MLD_close(app);
}