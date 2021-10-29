
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


int main(void){
    hf_MLD_start();
    hf_app app = {};
    app.name = "main";
    hf_app_start(&app);
    
    hf_window window = {};
    //set some default values
    hf_window_init(&window);
    
    //setvbuf(stdout, NULL, _IONBF, 0); 
    
    if(hf_create_window(&window)){
        printf("created window\n");
    }else{
        printf("couldn't create window\n");
        return -1;
    }
    
    char* kasjodigjawoiejg = malloc(20);
    
    //hf_err("skibibopmmdada %s %s", "235235", "ajsdogijaw");
    //hf_assertf(22 == 8, "stinkin goober");
    
    //Sleep(1000);
    /* 
        hf_profile_scope() {
            printf("what a goober inside scope\n");
        }
     */
    
    
    const char* goober = "what a super goober";
    
    hf_vector vector = {};
    hf_vector_init(&vector);
    
    
    /* 
        hf_vector_push_back(&vector, "goober");
        hf_vector_push_back(&vector, &goober);
        hf_vector_push_back(&vector, "goober");
     */
    
    //hf_vector_find(&vector, &goober);
    
    printf("%I64u\n", hf_vector_find(&vector, &goober));
    
    
    printf("time: %lf\n", hf_get_time(&app));
    
    hf_vector_free(&vector);
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    
    while(hf_should_window_update(&window)){
        hf_update_window(&window);
        hf_swap_buffers(&window);
    }
    
    if(hf_destroy_window(&window))
        printf("destroyed window\n");
    
    
    //getchar();
    
    hf_app_stop(&app);
    
    hf_MLD_close();
    return window.msg.wParam;
}












































