#include "hfapp.h"
#include "../text/hffreetype.h"

hf_app hf_app_defaults(){
    hf_app app = {};
    app.name = "HF app";
    //app.parameters = HF_APP_CREATE_WINDOW | HF_APP_USE_OPENGL;
    // NOTE(salmoncatt): smooths fps readings and reduces chatter
    app.fps_smoothing = 0.05f;
    
    return app;
}

void hf_app_init(hf_app* app){
    hf_log("[HF APP] initializing HF app: [%s]...\n", app->name);
    //app->cpu_freq = 0;
    //app->time_start = 0;
    
    hf_time_init(app->fps_smoothing);
    
#ifdef HF_DONT_BUFFER_STDOUT
    setvbuf(stdout, NULL, _IONBF, 0);
#endif
    
    if(app->parameters){
        //hf_log("[HF APP] app: [%s] is using parameters: [");
        if(app->parameters & HF_APP_CREATE_WINDOW){
            hf_window_defaults(&app->window);
        }
        
        if(app->parameters & HF_APP_USE_ECS){
            hf_ecs_init(&app->ecs);
        }
        
    }else
        hf_err("[HF APP] app: [%s] doesn't have any parameters, using no HF utilities\n", app->name);
    
    //app->window = {0};
    
    
    
    //hf_gl_init();
    hf_log("[HF APP] initialized HF app: [%s]\n\n", app->name);
}

void hf_app_start(hf_app* app){
#ifdef _WIN32
    //needs to be weird like this in case of testing a window without opengl
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_gl_init(); //creates an empty window to load gl extensions from
        //hf_create_window(&app->window);
    }
    
    if(app->parameters & HF_APP_CREATE_WINDOW){
        hf_create_window(&app->window);
    }
#elif defined(__linux__)
    if(app->parameters & HF_APP_CREATE_WINDOW){
        hf_create_window(&app->window);
    }
    
    //needs to be weird like this in case of testing a window without opengl
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_gl_init(); //creates an empty window to load gl extensions from
        //hf_create_window(&app->window);
    }
    
#endif
    
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_renderer_init(app);
        hf_renderer_init_2d(app);
        hf_free_type_init();
    }
}

void hf_app_update(hf_app* app){
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_renderer_update(app);
    }
    hf_time_update();
    hf_input_update(app);
}

b8 hf_app_should_update(hf_app* app){
    hf_app_update(app);
    
    return hf_should_window_update(&app->window);
}

void hf_app_stop(hf_app* app){
    hf_log("[HF APP] closing app: [%s]\n", app->name);
    
    if(app->parameters & HF_APP_USE_ECS){
        hf_ecs_destroy(&app->ecs);
    }
    if(app->parameters & HF_APP_CREATE_WINDOW){
        hf_destroy_window(&app->window);
    }
    
    if(app->parameters & HF_APP_USE_OPENGL){
        hf_renderer_destroy(app);
        hf_renderer_destroy_2d(app); 
        hf_gl_close();
        hf_free_type_close();
    }
    hf_log("[HF APP] closed app [%s]\n", app->name);
    
    //hf_MLD_close(app);
}