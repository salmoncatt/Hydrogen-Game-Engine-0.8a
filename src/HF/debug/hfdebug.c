#include "hfdebug.h"
#include "stdio.h"
#include "../datatypes/hfstring.h"
#include "../util/hfutil.h"
#include <windows.h>
#include "../math/hfmath.h"

void hf_debug_init(){
    
}

void hf_debug_set_text_color(hf_debug_color foregroundColor, hf_debug_color backgroundColor){
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (foregroundColor | backgroundColor));
}

void hf_log(const char* msg, ...){
    hf_vector split_at_colors = {};
    hf_vector_init(&split_at_colors);
    
    hf_string_split(&split_at_colors, "$hfcc{", msg);
    for(u64 i = 0; i < split_at_colors.size; ++i){
        //current msg
        char* current = hf_vector_get(&split_at_colors, i);
        //length of current msg
        u64 length = hf_strlen(current);
        // NOTE(salmoncatt): finds index of terminating hf color code: $hfcc{FF00FF} <- last one
        u64 index = hf_strfind('}', current, 0, length);
        
        
        
        if(index != hf_string_npos){
            char* color = hf_string_substr(current, 0, index);
            
            switch(hf_hash_str(color)){
                case hf_lookup_debug_black:
                hf_debug_set_text_color(hf_debug_black, hf_debug_black);
                break;
                case hf_lookup_debug_blue:
                hf_debug_set_text_color(hf_debug_blue, hf_debug_black);
                break;
                case hf_lookup_debug_green:
                hf_debug_set_text_color(hf_debug_green, hf_debug_black);
                break;
                case hf_lookup_debug_aqua:
                hf_debug_set_text_color(hf_debug_aqua, hf_debug_black);
                break;
                case hf_lookup_debug_red:
                hf_debug_set_text_color(hf_debug_red, hf_debug_black);
                break;
                case hf_lookup_debug_purple:
                hf_debug_set_text_color(hf_debug_purple, hf_debug_black);
                break;
                case hf_lookup_debug_yellow:
                hf_debug_set_text_color(hf_debug_yellow, hf_debug_black);
                break;
                case hf_lookup_debug_white:
                hf_debug_set_text_color(hf_debug_white, hf_debug_black);
                break;
                case hf_lookup_debug_gray:
                hf_debug_set_text_color(hf_debug_gray, hf_debug_black);
                break;
                case hf_lookup_debug_light_blue:
                hf_debug_set_text_color(hf_debug_light_blue, hf_debug_black);
                break;
                case hf_lookup_debug_light_green:
                hf_debug_set_text_color(hf_debug_light_green, hf_debug_black);
                break;
                case hf_lookup_debug_light_aqua:
                hf_debug_set_text_color(hf_debug_light_aqua, hf_debug_black);
                break;
                case hf_lookup_debug_light_red:
                hf_debug_set_text_color(hf_debug_light_red, hf_debug_black);
                break;
                case hf_lookup_debug_light_purple:
                hf_debug_set_text_color(hf_debug_light_purple, hf_debug_black);
                break;
                case hf_lookup_debug_light_yellow:
                hf_debug_set_text_color(hf_debug_light_yellow, hf_debug_black);
                break;
                case hf_lookup_debug_bright_white:
                hf_debug_set_text_color(hf_debug_bright_white, hf_debug_black);
                break;
            }
            hf_free(color);
        }
        
        
        char* msg_without_color_codes = hf_string_substr(current, index + 1, length);
        
        if(msg_without_color_codes != NULL)
            printf("%s\n", msg_without_color_codes);
        
        hf_free(msg_without_color_codes);
    }
    
    // NOTE(salmoncatt): reset text color back to white and black background
    hf_debug_set_text_color(hf_debug_white, hf_debug_black);
    hf_vector_free(&split_at_colors);
}

void hf_debug_err(const char* msg){
    hf_log(msg);
    /* 
        hf_vector split_at_colors = {};
        hf_vector_init(&split_at_colors);
        
        hf_string_split(&split_at_colors, "$hfcc{", msg);
        for(u64 i = 0; i < split_at_colors.size; ++i){
            //current msg
            char* current = hf_vector_get(&split_at_colors, i);
            //length of current msg
            u64 length = hf_strlen(current);
            // NOTE(salmoncatt): finds index of terminating hf color code: $hfcc{FF00FF} <- last one
            u64 index = hf_strfind('}', current, 0, length);
            
            
            if(index == hf_string_npos){
                printf("[HF Err]: msg doesn't have correct color formating\n");
            }
            
            char* color_hex = hf_string_substr(current, 0, index);
            printf("char hex:%s\n", color_hex);
            
            u32 color = strtol(color_hex, NULL, 16);
            printf("%u\n", color);
            //printf("%s\n", (char*)(hf_string_substr(hf_vector_get(&split_at_colors, i), index, hf_strlen(hf_vector_get(&split_at_colors, i)))));
        }
        
        hf_vector_free(&split_at_colors);
     */
}

/* 
void hf_debug_err_msg_box(const char* title, const char* msg, u32 format, ...){
    
}
 */