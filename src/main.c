
//#define HF_DEBUG
#include "HF/hf.h"

/* 
void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}
 */

// NOTE(salmoncatt): shortcuts to remember: alt r (comment out block), crtl shift { (creates double on a new line + ;)

typedef struct poopy{
    u32 num_of_poopies;
}poopy;

int main(void){
    //hf_MLD_start();
    hf_app app = hf_app_defaults();
    app.name = "haha, what a goober";
    app.parameters = HF_APP_CREATE_WINDOW | HF_APP_USE_OPENGL | HF_APP_USE_ECS;
    hf_app_start(&app);
    
    app.window.title = "what a goober";
    if(!hf_create_window(&app.window))
        return -1;
    
    
    // NOTE(salmoncatt): please put all opengl things after this danks
    
    
    hf_shader shader = {};
    shader.name = "goober shader";
    
    hf_shader_create(&shader, "../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
    
    v4f test_vec = hf_v4f(1, 2, 3, 4);
    v3f vec = test_vec.rgb;
    
    hf_log("[%f %f %f %f]\n", vec.x, vec.y, vec.z, test_vec.w);
    
    
    /* 
        hf_ecs ecs = {};
        hf_ecs_init(&ecs);
     */
    
    hf_mesh mesh = {};
    
    
    float vertices[] = {
        -0.5f, 0.5f, 0,
        -0.5f, -0.5f, 0,
        0.5f, -0.5f, 0,
        0.5f, 0.5f, 0,
    };
    
    u32 indices[] = {
        0, 1, 3,
        3, 1, 2
    };
    
    float texture_coords[] = {
        0, 0,
        0, 1,
        1, 1,
        1, 0,
    };
    
    mesh.vertices = vertices;
    mesh.vertices_size = 4 * 3; 
    
    mesh.texture_coords = texture_coords;
    mesh.texture_coords_size = 4 * 2; 
    
    mesh.indices = indices;
    mesh.indices_size = 2 * 3; 
    mesh.type = 3;
    
    hf_mesh_create(&mesh);
    
    v3f pos = {0.2f, 0, 0};
    v3f rot = {0, 0, 0};
    v3f scale = {1, 1, 1};
    hf_transform transform = {pos, rot, scale};
    
    hf_texture texture = hf_texture_from_file("../res/images/patrick.png");
    hf_texture_create(&texture);
    
    mesh.texture = texture;
    
    printf("time: %lf\n", hf_get_time());
    
    //hf_vector_free(&vector);
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    
    glClearColor(0.5, 0.5, 0.5, 1);
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        
        char* title = hf_format_string("HF Engine test [%u] [%u, %u]", (u32)hf_get_fps(), (u32)hf_input_cursor_pos.x, (u32)hf_input_cursor_pos.y);
        
        hf_set_window_title(&app.window, title);
        
        hf_free(title);
        
        //transform.pos.x += 0.0001f;
        
        //hf_log("[%i %i]\n", app.window.width, app.window.height);
        
        hf_render_mesh_2d(&mesh, &shader, &transform);
        
        if(hf_input_get_key_down(HF_KEY_MINUS)){
            
            hf_input_toggle_cursor();
            
            //printf("key pressed: %u %u\n", hf_input_keys[HF_KEY_MINUS], hf_input_keys_old[HF_KEY_MINUS]);
            //printf("key pressed\n");
        }
        
        
        hf_limit_fps(250);
    }
    
    
    hf_texture_destroy(&texture);
    
    
    hf_mesh_destroy(&mesh);
    hf_app_stop(&app);
    //hf_ecs_destroy(&ecs);
    
    return app.window.msg.wParam;
}


/*
 
#include <stdio.h>
#include <stdlib.h>
 
//#define HF_DEBUG
#include "HF/hf.h"
//#include "HF/hfpch.h"
//#include <GL/gl.h>

/* 
void test_callback(hf_window* w, u32 keycode, u32 action){
    printf("skibidi bop mm dada\n");
}
 

/* 
typedef struct poopy{
    u32 num_of_poopies;
}poopy;
 


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
     
    
    hf_serial_close_port(&port);
}*/











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

