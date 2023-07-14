#include "HF/hf.h"



int main(void){
    
    hf_app app = hf_app_defaults();
    app.name = "fluid test";
    app.parameters = HF_APP_USE_OPENGL | HF_APP_USE_ECS | HF_APP_CREATE_WINDOW;
    hf_app_init(&app);
    
    app.window.title = "fluid test";
    hf_app_start(%app);
    
    hf_ecs* ecs = &app.ecs;
    
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        
        hf_limit_fps(300);
    }
    
    
    hf_app_stop(&app);
}