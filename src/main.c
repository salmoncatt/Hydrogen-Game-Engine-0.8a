
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
    
    const char* goober = "a bb ababbabbababaa";
    //char* goober = (char*)hf_malloc(111);
    hf_vector vector = { 0 };
    hf_vector_init(&vector);
    //u64 index = hfstrfind('e', goober, 3, hfstrlen(goober));
    //u64 index = hfstrlen(goober);
    u64 index = hf_string_find("aa", goober, 1);
    printf("hfsf output: %I64u\n", index);
    printf("hf_string_npos: %I64u\n", hf_string_npos);
    //printf("ctz: %u\n", hf_ctzu32(8));
    
    //const char* a = "abaaaaabaaaaaaaaaaaabaaaa";
    //const char* b = "abaaaaabaaaaaaaaaaaabaaaa";
    
    //printf("%d\n", hf_memcmp(a, b, hf_strlen(a)));
    
    /* 
        for(int i = 0; i < 100; ++i){
            goober[i] = 'e';
            goober[i + 1] = '\0';
            u64 size = hfstrlen(goober);
            if(size != i + 1)
                printf("size of characters: %i, strlen: %I64u\n", i + 1, size);
        }
        hf_free(goober);
     */
    
    /* 
        hfStringSplit(&vector, " ", goober);
        printf("%s", (char*)vector.data[0]);
        printf("%s", (char*)vector.data[1]);
        printf("%s", (char*)vector.data[2]);
     */
    
    //hf_free(bytes);
    hf_vector_free(&vector);
    
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












































