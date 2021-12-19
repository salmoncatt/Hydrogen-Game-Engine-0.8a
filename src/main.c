
/* 
#include <stdio.h>
#include <stdlib.h>
 */
//#define HF_DEBUG
#include "HF/hf.h"
//#include "HF/hfpch.h"
//#include <GL/gl.h>

/* 
void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}
 */

/* 
typedef struct poopy{
    u32 num_of_poopies;
}poopy;
 */


//const char* port, const char* gcode file, b8 home before running
int main(){
    hf_log("running\n");
    hf_serial_list_open_ports();
    
    hf_serial_port port = {};
    port = hf_serial_open_port("COM4", 115200);
    
    
    hf_3d_printer_run_gcode(&port, "../res/test.gcode");
    
    /* 
        while(1){
            if(hf_serial_read(&port, buffer, 255) > 0){
                
                if(!hf_strcmp(buffer, "goober")){
                    hf_log("%s\n", buffer);
                    
                }
            }
            Sleep(10);
        }
     */
    
    hf_serial_close_port(&port);
}