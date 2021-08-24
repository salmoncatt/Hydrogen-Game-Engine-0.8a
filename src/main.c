
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "HF/hf.h"

//TODO: FINISH THE THEME

void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}

int main(void){
    hf_window window = {};
    window.width = 1000;
    window.height = 600;
    window.bitsPerPixel = 32;
    window.title = "what a goober";
    
    setvbuf(stdout, NULL, _IONBF, 0); 
    
    if(hf_create_window(&window)){
        printf("created window\n");
    }else{
        printf("couldn't create window\n");
        return -1;
    }
    
    hf_profile_scope() {
        printf("what a goober inside scope\n");
    }
    
    hf_window_set_key_callback(&window, &test_callback);
    
    window.key_callback(NULL, 0, 0);
    
    while(hf_should_window_update(&window)){
        hf_update_window(&window);
    }
    
    if(hf_destroy_window(&window))
        printf("destroyed window\n");
    
    return window.msg.wParam;
}












































