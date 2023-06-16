#include "HF/hf.h"



//welcome to the linux playground
int main(void){
    hf_app app = hf_app_defaults();
    app.name = "linux womp womp";
    app.parameters = HF_APP_CREATE_WINDOW | HF_APP_USE_OPENGL | HF_APP_USE_ECS;
    
    hf_app_init(&app);
    app.window.title = "linux nerrrrd";
    hf_app_start(&app);
    
    hf_ecs* ecs = &app.ecs;
    
    
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
    
    
    
    //printf("time ran: [%lf] millis\n", hf_get_time());
    //sleep(1);
    //printf("time ran: [%lf] millis\n", hf_get_time());
    
    
    //hf_serial_list_open_ports();
    
    //fix key_last in input.h
    
    glClearColor(0.5, 0.5, 0.5, 1);
    
    
    
    while(hf_app_should_update(&app) && !hf_input_get_key(HF_KEY_ESCAPE)){
        
        hf_render_mesh((hf_mesh*)(hf_ecs_get_component(ecs, mesh_test, hf_mesh)), &shader, (hf_transform*)(hf_ecs_get_component(ecs, mesh_test, hf_transform)));
        //hf_render_mesh(&mesh, &shader, &transform);
        
        
        
        if(hf_input_get_key_down(HF_KEY_BACKSLASH)){
            hf_renderer_toggle_wireframe();
        }
        
        if(hf_input_get_key_down(HF_KEY_T)){
            hf_input_toggle_cursor();
        }
        
        //printf("%f\n", transform.pos.y);
        //hf_renderer_cam.transform.pos.z += 0.01f;
        
        
        
        
        char fps[64];
        sprintf(fps, "fps: %f", hf_get_fps());
        hf_set_window_title(&app.window, fps);
        
        
        
        //usleep(100000);
        //hf_limit_fps(30);
        
    }
    
    printf("time ran: [%lf] millis\n", hf_get_time());
    
    
    hf_texture_destroy(&texture);
    hf_mesh_destroy(&mesh);
    
    return hf_app_stop(&app);;
}