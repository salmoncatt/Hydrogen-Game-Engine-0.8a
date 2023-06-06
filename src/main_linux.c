#include "HF/hf.h"



//welcome to the linux playground
int main(void){
    hf_app app = hf_app_defaults();
    app.name = "linux womp womp";
    app.parameters = HF_APP_CREATE_WINDOW;
    
    hf_app_init(&app);
    app.window.title = "linux nerrrrd";
    hf_app_start(&app);
    
    
    //hf_serial_list_open_ports();
    
    while(hf_app_should_update(&app)){
        
    }
    
    
    hf_app_stop(&app);
    
    printf("time ran: [%lf] millis\n", hf_get_time());
    
    return 1;
}