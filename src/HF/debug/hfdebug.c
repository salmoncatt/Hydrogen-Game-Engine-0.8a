#include "hfdebug.h"
#include "stdio.h"
#include "../datatypes/hfstring.h"

void hf_debug_init(){
    
}

void hf_debug_set_text_color(v3f foregroundColor, v3f backgroundColor){
    
}

void hf_debug_err(const char* msg, ...){
    hf_vector split_at_colors = {};
    hf_vector_init(&split_at_colors);
    
    hf_string_split(&split_at_colors, "$hfcc{", msg);
    for(u64 i = 0; i < split_at_colors.size; ++i){
        printf("%s\n", (char*)(hf_vector_get(&split_at_colors, i) + hf_strfind()));
    }
    
    hf_vector_free(&split_at_colors);
}

void hf_debug_err_msg_box(const char* title, const char* msg, u32 format, ...){
    
}