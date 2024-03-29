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
    
    
    // NOTE(salmoncatt): moved all this mouse movement crap to window update, mouse movement actually works over there
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


b8 hf_input_get_key_up(u32 key);

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button(u32 button){
    return hf_input_buttons[button];
}

b8 hf_input_get_mouse_button_down(u32 button){
    return (hf_input_buttons[button] && !hf_input_buttons_old[button]);
}

b8 hf_input_get_mouse_button_up(u32 button){
    return (!hf_input_buttons[button] && hf_input_buttons_old[button]);
}


void hf_input_show_cursor(b8 visibility){
#ifdef _WIN32
    ShowCursor(visibility ? TRUE : FALSE);
#endif
    hf_input_cursor_visibility = visibility;
}

void hf_input_toggle_cursor(){
    hf_input_cursor_visibility = !hf_input_cursor_visibility;
#ifdef _WIN32
    ShowCursor(hf_input_cursor_visibility ? TRUE : FALSE);
#endif
}

b8 hf_input_get_cursor_visibility(){
    return hf_input_cursor_visibility;
}

void hf_input_destroy(){
    //hf_log("[HF Input] destroying...\n");
    //hf_vector_free(&hf_input_keys);
    //hf_log("[HF Input] destroyed\n");
}