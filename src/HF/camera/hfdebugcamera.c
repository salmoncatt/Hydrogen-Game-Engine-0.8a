#include "hfdebugcamera.h"

void hf_update_debug_camera(hf_debug_camera* camera){
    
    f32 speed = hf_get_delta_time() * ((hf_input_get_key(HF_KEY_SHIFT)) ? camera->movement_speed * 2 : camera->movement_speed);
    
    f32 dir_x = camera->direction.x * speed;
    f32 dir_z = camera->direction.z * speed;
    
    //hf_log("[%f %f]", camera->direction.x, camera->direction.z);
    
    if(hf_input_get_key(HF_KEY_W))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(dir_x, 0, dir_z));
    if(hf_input_get_key(HF_KEY_A))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(dir_z, 0, -dir_x));
    if(hf_input_get_key(HF_KEY_S))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(-dir_x, 0, -dir_z));
    if(hf_input_get_key(HF_KEY_D))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(-dir_z, 0, dir_x));
    if(hf_input_get_key(HF_KEY_SPACE))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(0, speed, 0));
    if(hf_input_get_key(HF_KEY_CONTROL))
        camera->transform.pos = hf_add_v3f(camera->transform.pos, hf_v3f(0, -speed, 0));
    
    //v2f rotation_amount = !hf_input_get_cursor_visibility() ? hf_mul_v2f_f(hf_input_get_mouse_movement(), -camera->sensitivity) : hf_v2f(0, 0);
    
    v2f rotation_amount = hf_mul_v2f_f(hf_input_get_mouse_movement(), -camera->sensitivity);
    
    
    
    
    camera->transform.rot = hf_add_v3f(camera->transform.rot, hf_v3f(rotation_amount.y, rotation_amount.x, 0));
    
    camera->direction = hf_get_dir_from_rot(hf_v3f(0, camera->transform.rot.y, 0));
    
    //hf_log("[%f %f %f]\n", camera->direction.x, camera->direction.y, camera->direction.z);
    
    //hf_log(" [%f %f %f] [%f %f %f]\n", camera->transform.pos.x, camera->transform.pos.y, camera->transform.pos.z, camera->transform.rot.x, camera->transform.rot.y, camera->transform.rot.z);
    
    
    if (camera->transform.rot.x < -90)
        camera->transform.rot.x = -90;
    else if (camera->transform.rot.x > 90)
        camera->transform.rot.x = 90;
    
    
    //this is the camera in the debug camera
    camera->camera.pos = camera->transform.pos;
    camera->camera.rot = camera->transform.rot;
}