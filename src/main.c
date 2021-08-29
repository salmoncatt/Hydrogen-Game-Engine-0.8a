
#include <stdio.h>
#include <stdlib.h>
#include <GL/gl.h>

#include "HF/hf.h"

//TODO: FINISH THE THEME

/* 
void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}
 */

int main(void){
    setvbuf(stdout, NULL, _IONBF, 0);
    /* 
        hf_window window = {};
        window.width = 1000;
        window.height = 600;
        window.bitsPerPixel = 32;
        window.title = "what a goober";
        
        setvbuf(stdout, NULL, _IONBF, 0); 
        
        if(hfCreateWindow(&window)){
            printf("created window\n");
        }else{
            printf("couldn't create window\n");
            return -1;
        }
     */
    
    /* 
        hf_profile_scope() {
            printf("what a goober inside scope\n");
        }
     */
    
    const char* goober = "ba      aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n";
    hf_vector vector = {};
    hfVectorInit(&vector);
    //u64 index = hfstrfind(' ', goober, 7);
    //u64 index = hfstrlen(goober);
    u64 index = hfStringFind("a", goober, 0);
    printf("%lu\n", index);
    printf("%lu\n", hf_string_npos);
    /* 
        hfStringSplit(&vector, " ", goober);
        printf("%s", (char*)vector.data[0]);
        printf("%s", (char*)vector.data[1]);
        printf("%s", (char*)vector.data[2]);
     */
    
    //hf_free(bytes);
    hfVectorFree(&vector);
    
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    /* 
        while(hfShouldWindowUpdate(&window)){
            hfUpdateWindow(&window);
            hfSwapBuffers(&window);
        }
        
        if(hfDestroyWindow(&window))
            printf("destroyed window\n");
        


        return window.msg.wParam;
         */
    return 0;
}












































