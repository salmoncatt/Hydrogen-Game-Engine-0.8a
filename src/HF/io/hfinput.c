#include "hfinput.h"

b8 hf_input_keys[HF_KEY_LAST];
b8 hf_input_keys_old[HF_KEY_LAST];

b8 hf_input_cursor_visibility = 1;

v2f hf_input_cursor_pos = {};

void hf_input_update(){
    //hf_input_keys_old[key] = hf_input_keys[key];
    
    hf_memcpy(hf_input_keys_old, hf_input_keys, (sizeof(b8) * HF_KEY_LAST));
    
    
    
    //hf_log("[HF Input] initializing...\n");
    
    //hf_input_keys.init_capacity = HF_KEY_LAST;
    //hf_vector_init(&hf_input_keys);
    
    //hf_log("[HF Input] initialized\n");
}

b8 hf_input_get_key(u32 key){
    return hf_input_keys[key];
}


b8 hf_input_get_key_down(u32 key){
    return (hf_input_keys[key] && !hf_input_keys_old[key]);
}

/*
b8 hf_input_get_key_up();

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button();

b8 hf_input_get_mouse_button_down();

b8 hf_input_get_mouse_button_up();
 */

void hf_input_show_cursor(b8 visibility){
    ShowCursor(visibility ? TRUE : FALSE);
    hf_input_cursor_visibility = visibility;
}

void hf_input_toggle_cursor(){
    hf_input_cursor_visibility = !hf_input_cursor_visibility;
    ShowCursor(hf_input_cursor_visibility ? TRUE : FALSE);
}

void hf_input_destroy(){
    //hf_log("[HF Input] destroying...\n");
    //hf_vector_free(&hf_input_keys);
    //hf_log("[HF Input] destroyed\n");
}