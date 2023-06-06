#include "HF/hf.h"



int main(void){
    hf_app app = hf_app_defaults();
    app.name = "linux womp womp";
    app.parameters = 0;
    
    hf_app_init(&app);
    hf_app_start(&app);
    
    
    
    printf("time: %lf\n", hf_get_time());
    
    hf_app_stop(&app);
    return 1;
}