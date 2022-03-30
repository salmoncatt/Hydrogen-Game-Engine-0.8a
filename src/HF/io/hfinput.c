#include "hfinput.h"

b8 hf_input_keys[HF_KEY_LAST];
b8 hf_input_keys_old[HF_KEY_LAST];

b8 hf_input_buttons[HF_MOUSE_BUTTON_LAST];
b8 hf_input_buttons_old[HF_MOUSE_BUTTON_LAST];

b8 hf_input_cursor_visibility = 1;
b8 hf_input_cursor_visibility_last = 1;

v2f hf_input_cursor_pos = {};
v2f hf_input_cursor_pos_last = {};
v2f hf_input_cursor_movement = {};
v2f hf_input_center = {};

void hf_input_update(hf_app* app){
    hf_memcpy(hf_input_keys_old, hf_input_keys, (sizeof(b8) * HF_KEY_LAST));
    hf_memcpy(hf_input_buttons_old, hf_input_buttons, (sizeof(b8) * HF_MOUSE_BUTTON_LAST));
    
    if(hf_input_cursor_visibility){
        hf_input_cursor_movement = hf_sub_v2f(hf_input_cursor_pos, hf_input_cursor_pos_last);
        
    }else if(!hf_input_cursor_visibility && !hf_input_cursor_visibility_last){
        hf_input_cursor_movement = hf_sub_v2f(hf_input_cursor_pos, hf_input_center);
        hf_log("[%f %f]\n", hf_input_cursor_pos.x, hf_input_cursor_pos.y);
        hf_log("[%f %f]\n", hf_input_center.x, hf_input_center.y);
        //hf_log("[%f %f]\n", hf_input_cursor_movement.x, hf_input_cursor_movement.y);
        hf_input_cursor_pos = hf_input_center;
        SetCursorPos((i32)hf_input_center.x + app->window.x + 10, (i32)hf_input_center.y + app->window.y + 33);
        
    }else if(!hf_input_cursor_visibility  && hf_input_cursor_visibility_last){
        hf_input_cursor_movement = hf_v2f(0, 0);
        hf_input_cursor_pos = hf_input_center;
        SetCursorPos((i32)hf_input_center.x + app->window.x, (i32)hf_input_center.y + app->window.y);
    }
    
    /* 
        if(!hf_input_cursor_visibility_last && hf_input_cursor_visibility){
            
        }
     */
    
    //hf_input_cursor_pos = hf_input_middle;
    hf_input_cursor_pos_last = hf_input_cursor_pos;
    hf_input_cursor_visibility_last = hf_input_cursor_visibility;
}

v2f hf_input_get_mouse_movement(){
    return hf_input_cursor_movement;
}

b8 hf_input_get_key(u32 key){
    return hf_input_keys[key];
}


b8 hf_input_get_key_down(u32 key){
    return (hf_input_keys[key] && !hf_input_keys_old[key]);
}


b8 hf_input_get_key_up();

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button(){
    
}

b8 hf_input_get_mouse_button_down(u32 button){
    return (hf_input_buttons[button] && !hf_input_buttons_old[button]);
}

b8 hf_input_get_mouse_button_up();


void hf_input_show_cursor(b8 visibility){
    ShowCursor(visibility ? TRUE : FALSE);
    hf_input_cursor_visibility = visibility;
}

void hf_input_toggle_cursor(){
    hf_input_cursor_visibility = !hf_input_cursor_visibility;
    ShowCursor(hf_input_cursor_visibility ? TRUE : FALSE);
}

b8 hf_input_get_cursor_visibility(){
    return hf_input_cursor_visibility;
}

void hf_input_destroy(){
    //hf_log("[HF Input] destroying...\n");
    //hf_vector_free(&hf_input_keys);
    //hf_log("[HF Input] destroyed\n");
}