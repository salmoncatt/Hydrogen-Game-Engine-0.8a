
#include <stdio.h>
#include <stdlib.h>

#include "HF/hf.h"
#include <GL/gl.h>


//TODO: FINISH THE THEME

/* 
void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}
 */


int main(void){
    setvbuf(stdout, NULL, _IONBF, 0);
    
    hf_window window = {};
    window.width = 1000;
    window.height = 600;
    window.bits_per_pixel = 32;
    window.title = "what a goober";
    
    setvbuf(stdout, NULL, _IONBF, 0); 
    
    if(hf_create_window(&window)){
        printf("created window\n");
    }else{
        printf("couldn't create window\n");
        return -1;
    }
    
    
    /* 
        hf_profile_scope() {
            printf("what a goober inside scope\n");
        }
     */
    
    const char* goober = "what a super goober";
    
    
    
    
    //hf_free(bytes);
    /* 
        hf_vector_free(&vector);
     */
    
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    
    while(hf_should_window_update(&window)){
        hf_update_window(&window);
        hf_swap_buffers(&window);
    }
    
    if(hf_destroy_window(&window))
        printf("destroyed window\n");
    
    
    return window.msg.wParam;
}












































