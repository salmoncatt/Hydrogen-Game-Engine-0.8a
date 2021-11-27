
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

typedef struct poopy{
    u32 num_of_poopies;
}poopy;

int main(void){
    //hf_MLD_start();
    hf_app app = {};
    app.name = "main";
    hf_app_start(&app);
    
    app.window.title = "what a goober";
    
    //hf_window window = {};
    //set some default values
    //hf_window_init(&app.window);
    
    if(!hf_create_window(&app.window))
        return -1;
    
    /* 
        if(hf_create_window(&app.window)){
            printf("created window\n");
            //hf_gl_init();
        }else{
            printf("couldn't create window\n");
            return -1;
        }
     */
    
    hf_ecs ecs = {};
    hf_ecs_init(&ecs);
    
    hf_mesh mesh = {};
    
    
    float vertices[] = {
        -0.5f, 0.5f, 0,
        -0.5f, -0.5f, 0,
        0.5f, -0.5f, 0,
        0.5f, -0.5f, 0,
        0.5f, 0.5f, 0,
        -0.5f, 0.5f, 0
    };
    
    mesh.vertices = vertices;
    mesh.vertices_amount = 18; 
    mesh.type = 3;
    
    hf_mesh_create(&mesh);
    
    v3f pos = {0, 0, 0};
    v3f rot = {0, 0, 0};
    v3f scale = {1, 1, 1};
    hf_transform transform = {pos, rot, scale};
    
    //mesh.vertices.data[0] = vertices;
    
    //u32 component_id = hf_ecs_register_component(&ecs, poopy);
    
    //printf("id (should be 0): %u\n", component_id);
    //printf("%s\n", ((hf_ecs_component*)ecs.component_types.data[0])->name);
    
    /* 
        hf_entity entity = hf_ecs_create_entity(&ecs);
        hf_entity entity2 = hf_ecs_create_entity(&ecs);
        
        poopy poopy_yes = {};
        poopy_yes.num_of_poopies = 50;
        
        
        hf_ecs_add_component(&ecs, entity, poopy, &poopy_yes);
        
        poopy_yes.num_of_poopies = 70;
        hf_ecs_add_component(&ecs, entity2, poopy, &poopy_yes);
        
        poopy* poopy_get = (poopy*)hf_ecs_get_component(&ecs, entity, poopy);
        //poopy_get->num_of_poopies = 0;
        printf("num of poopies: %u\n", poopy_get->num_of_poopies);
        
        
        poopy_get = (poopy*)hf_ecs_get_component(&ecs, entity2, poopy);
        //poopy_get->num_of_poopies = 0;
        printf("num of poopies: %u\n", poopy_get->num_of_poopies);
     */
    
    /* 
        hf_ecs_remove_component(&ecs, entity, poopy);
        
        poopy_get = (poopy*)hf_ecs_get_component(&ecs, entity, poopy);
        
        printf("is null: %u\n", (poopy_get == NULL));
     */
    //printf("num of poopies: %u\n", poopy_get->num_of_poopies);
    
    //printf("%u\n", hf_ecs_create_entity(&ecs));
    
    //char* kasjodigjawoiejg = malloc(20);
    
    
    //hf_err("skibibopmmdada %s %s", "235235", "ajsdogijaw");
    //hf_assertf(22 == 8, "stinkin goober");
    
    //Sleep(1000);
    /* 
        hf_profile_scope() {
            printf("what a goober inside scope\n");
        }
     */
    
    
    /* 
        const char* goober = "what a super goober";
        
        hf_vector vector = {};
        hf_vector_init(&vector);
     */
    
    
    //printf("is this changing\n");
    
    /* 
        hf_vector_push_back(&vector, "goober");
        hf_vector_push_back(&vector, &goober);
        hf_vector_push_back(&vector, "goober");
     */
    
    //hf_vector_find(&vector, &goober);
    
    //printf("%I64u\n", hf_vector_find(&vector, &goober));
    
    
    printf("time: %lf\n", hf_get_time(&app));
    
    //hf_vector_free(&vector);
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    
    glClearColor(0.5, 0.5, 0.5, 1);
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        //hf_update_window(&window);
        
        /* 
                glBegin(GL_TRIANGLES);
                glVertex2i(0, 0);
                glVertex2i(100, 0);
                glVertex2i(100, 100);
                
                glEnd();
         */
        
        hf_render_mesh(&mesh, transform);
        
        if(hf_input_get_key_down(HF_KEY_MINUS)){
            
            //printf("key pressed: %u %u\n", hf_input_keys[HF_KEY_MINUS], hf_input_keys_old[HF_KEY_MINUS]);
            printf("key pressed\n");
        }
        
        
        
        //hf_swap_buffers(&window);
    }
    
    //if(hf_destroy_window(&window))
    //printf("destroyed window\n");
    
    
    //getchar();
    
    hf_app_stop(&app);
    
    //hf_mesh_destroy(&mesh);
    
    hf_ecs_destroy(&ecs);
    
    //hf_MLD_stop();
    return app.window.msg.wParam;
}












































