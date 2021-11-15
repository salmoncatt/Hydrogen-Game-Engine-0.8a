#include "hfinput.h"

b8 hf_input_keys[HF_KEY_LAST];

void hf_input_init(){
    //hf_log("[HF Input] initializing...\n");
    
    //hf_input_keys.init_capacity = HF_KEY_LAST;
    //hf_vector_init(&hf_input_keys);
    
    //hf_log("[HF Input] initialized\n");
}

b8 hf_input_get_key(u32 key){
    return hf_input_keys[key];
}

/* 
b8 hf_input_get_key_down();

b8 hf_input_get_key_up();

void hf_input_set_clipboard(const char* text);

b8 hf_input_get_mouse_button();

b8 hf_input_get_mouse_button_down();

b8 hf_input_get_mouse_button_up();
 */

void hf_input_destroy(){
    //hf_log("[HF Input] destroying...\n");
    //hf_vector_free(&hf_input_keys);
    //hf_log("[HF Input] destroyed\n");
}