#include "hfapp.h"
#include "../rendering/hfrenderer.h"
#include "../rendering/hfrenderer2d.h"

void hf_app_init(hf_app* app){
    hf_log("[HF APP] initializing HF app: [%s]...\n", app->name);
    app->cpu_freq = 0;
    app->time_start = 0;
    
    hf_time_init(app);
    
#ifdef HF_DONT_BUFFER_STDOUT
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    if(app->parameters){
        //hf_log("[HF APP] app: [%s] is using parameters: [");
        if(app->parameters & HF_APP_CREATE_WINDOW){
            //hf_log("CREATE_WINDOW");
            hf_window_init(&app->window);
        }
        
        if(app->parameters & HF_APP_USE_OPENGL){
            hf_renderer_init(app);
            hf_renderer_init_2d(app);  
        }
        
        if(app->parameters & HF_APP_USE_ECS){
            hf_ecs_init(&app->ecs);
        }
        
    }else
        hf_err("[HF APP] app: [%s] doesn't have any parameters set, please set some\n", app->name);
    
    //app->window = {0};
    
    
    
    //hf_gl_init();
    hf_log("[HF APP] initialized HF app: [%s]\n\n", app->name);
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
    
    if(app->parameters & HF_APP_CREATE_WINDOW){
        //hf_log("CREATE_WINDOW");
        hf_destroy_window(&app->window);
    }
    
    if(app->parameters & HF_APP_USE_ECS){
        hf_ecs_destroy(&app->ecs);
    }
    
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_renderer_destroy(app);
        hf_renderer_destroy_2d(app); 
        hf_gl_close();
    }
    
    //hf_MLD_close(app);
}