
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
    app.parameters = HF_APP_USE_OPENGL | HF_APP_USE_ECS;
    
    hf_app_init(&app);
    app.window.title = "what a goober";
    hf_app_start(&app);
    
    hf_ecs* ecs = &app.ecs;
    
    // NOTE(salmoncatt): please put all opengl things after this thaaaanks
    
    hf_shader shader = {};
    shader.name = "goober shader";
    
    hf_shader_create(&shader, "../res/shaders/vertex.glsl", "../res/shaders/fragment.glsl");
    
    
    
    glEnable(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    
    v3f pos = {0.2f, 0, -1};
    v3f rot = {0, 0, 0};
    v3f scale = {1, 1, 1};
    hf_transform transform = {pos, rot, scale};
    
    hf_mesh mesh = hf_mesh_load_from_file("../res/models/stall/stall.obj");
    hf_texture texture = hf_texture_from_file("../res/models/stall/stallTexture.bmp");
    hf_texture_create(&texture);
    mesh.texture = texture;
    
    hf_entity mesh_test = hf_ecs_create_entity(ecs);
    hf_tag tag = {"mesh", "patrick les go"};
    hf_ecs_add_component(ecs, mesh_test, hf_tag, &tag);
    hf_ecs_add_component(ecs, mesh_test, hf_mesh, &mesh);
    hf_ecs_add_component(ecs, mesh_test, hf_transform, &transform);
    //hf_log("%s\n", ((hf_tag*)(hf_ecs_get_component(ecs, mesh_test, hf_tag)))->name);
    
    printf("time: %lf\n", hf_get_time());
    
    //hf_vector_free(&vector);
    //hf_window_set_key_callback(&window, &test_callback);
    
    //window.key_callback(NULL, 0, 0);
    
    glClearColor(0.5, 0.5, 0.5, 1);
    
    hf_gui_panel panel = {};
    panel.color = hf_v4f(0.3, 0.3, 0.3, 1);
    panel.title_bar_color = hf_v4f(0.9, 0.5, 0, 1);
    panel.element_spacing = 10;
    
    hf_texture gui_image_test = hf_texture_from_file("../res/images/patrick.png");
    hf_texture_create(&gui_image_test);
    
    hf_font font = hf_font_from_file("../res/fonts/oxygen/Oxygen-Regular.ttf", 64);
    font.color = (v3f){0.9, 0.9, 0.9};
    
    panel.font = &font;
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        
        char* title = hf_format_string("HF Engine test [%u] [%u, %u] [%i, %i]", (u32)hf_get_fps(), (u32)hf_input_cursor_pos.x, (u32)hf_input_cursor_pos.y, (i32)hf_input_get_mouse_movement().x, (i32)hf_input_get_mouse_movement().y);
        
        hf_set_window_title(&app.window, title);
        
        hf_render_mesh((hf_mesh*)(hf_ecs_get_component(ecs, mesh_test, hf_mesh)), &shader, (hf_transform*)(hf_ecs_get_component(ecs, mesh_test, hf_transform)));
        
        //printf("%u\n", font.line_spacing);
        
        //transform.pos.x += 0.0001f;
        //transform.pos = hf_add_v3f(transform.pos, hf_v3f(hf_input_get_mouse_movement().x, hf_input_get_mouse_movement().y, 0));
        
        //hf_log("[%i %i]\n", app.window.width, app.window.height);
        
        //printf("[%u %u]\n", app.window.width, app.window.height);
        
        //hf_render_rect(0, 0, 100, 100, (v4f){1, 1, 1, 1});
        
        if(hf_gui_panel_begin(&panel, "HF Engine Test", 110, 180, 150, 250, HF_TITLE_BAR | HF_MOVEABLE, 25)){
            
            if(hf_gui_button(80, 30, hf_v4f(0.9, 0.6, 0, 1))){
                printf("clicked\n");
            }
            
            
            hf_gui_image(100, 100, &gui_image_test);
            
            char fps[40];
            //f32 percentage = ((hf_get_delta_time() / hf_sleep_time)) * 100;
            //sprintf(fps, "gpu: %u%%", (u32)percentage);
            sprintf(fps, "fps: %u", (u32)hf_get_fps());
            
            hf_gui_text(100, 96, 0, fps, &font);
            hf_gui_text(100, 96, 0, "The quick brown fox jumps over the lazy dog", &font);
            hf_gui_text(100, 96, 0, "The quick brown fox jumps over the lazy dog", &font);
            hf_gui_text(100, 96, 0, "the quick brown fox jumps over the lazy dog", &font);
            
            hf_gui_panel_end();
        }
        
        
        
        hf_free(title);
        
        //hf_log("[%f, %f]\n", hf_input_get_mouse_movement().x, hf_input_get_mouse_movement().y);
        
        if(hf_input_get_key_down(HF_KEY_BACKSLASH)){
            hf_renderer_toggle_wireframe();
        }
        
        if(hf_input_get_mouse_button_down(HF_MOUSE_BUTTON_RIGHT)){
            
            hf_input_toggle_cursor();
            
            
            
            //printf("key pressed: %u %u\n", hf_input_keys[HF_KEY_MINUS], hf_input_keys_old[HF_KEY_MINUS]);
            //printf("key pressed\n");
        }
        
        //hf_log("[%f %f %f]\n", hf_renderer_cam.transform.rot.x, hf_renderer_cam.transform.rot.y, hf_renderer_cam.transform.rot.z);
        
        
        //hf_log_v3f(hf_renderer_cam.direction);
        
        
        //hf_update_debug_camera(&hf_renderer_cam);
        
        hf_render_font(&font);
        
        hf_limit_fps(300);
    }
    
    
    hf_texture_destroy(&texture);
    hf_texture_destroy(&gui_image_test);
    hf_font_destroy(&font);
    
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

