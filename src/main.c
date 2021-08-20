
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "HF/hf.h"

//TODO: FINISH THE THEME



int main(void){
    hf_window window = {};
    window.width = 1000;
    window.height = 600;
    window.bitsPerPixel = 32;
    window.title = "what a goober";
    
    if(hf_create_window(&window))
        printf("created window\n");
    else
        printf("couldn't create window\n");
    
    
    while(hf_should_window_update(&window)){
        hf_update_window(&window);
    }
    
    return window.msg.wParam;
}












































