#include "hfapp.h"
#include "../rendering/hfrenderer.h"
#include "../rendering/hfrenderer2d.h"

void hf_app_init(hf_app* app){
    hf_log("[HF] initializing HF app...\n");
    app->cpu_freq = 0;
    app->time_start = 0;
    
#ifdef HF_DONT_BUFFER_STDOUT
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    hf_time_init(app);
    hf_renderer_init(app);
    hf_renderer_init_2d(app);  
    //app->window = {0};
    
    
    hf_window_init(&app->window);
    
    //hf_gl_init();
    hf_log("[HF] initialized HF app\n\n");
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