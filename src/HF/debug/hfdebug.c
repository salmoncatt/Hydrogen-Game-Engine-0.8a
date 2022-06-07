#include "hfdebug.h"

void hf_debug_init(){
    
}

void hf_debug_set_text_color(hf_debug_color foregroundColor, hf_debug_color backgroundColor){
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (foregroundColor | backgroundColor));
}

void hf_log(const char* msg, ...){
    va_list args;
    va_start(args, msg);
    hf_vlog(msg, args);
    va_end(args);
}

void hf_log_v2f(v2f vec){
    printf("[%f %f]\n", vec.x, vec.y);
}

void hf_log_v3f(v3f vec){
    printf("[%f %f %f]\n", vec.x, vec.y, vec.z);
}

void hf_log_v4f(v4f vec){
    printf("[%f %f %f]\n", vec.x, vec.y, vec.z, vec.w);
}

/* 
void hf_debug_print_data(void* data, type){
    
}
 */

void hf_vlog(const char* msg, va_list args){
    
    // NOTE(salmoncatt): format the msg itself
    /* 
        u64 buffer_size = 0;
        char* formatted_msg = (char*)hf_malloc(256);;
        i32 length = vsnprintf(formatted_msg, 256, msg, args);
        
        if(length > 256){
            i32 old_length = length;
            hf_free(formatted_msg);
            formatted_msg = (char*)hf_malloc(length + 64);
            length = vsnprintf(formatted_msg, length + 64, msg, args);
            
            if(length > old_length + 64){
                printf("hf log not doin so good");
                // TODO(salmoncatt): add break here
            }
        }
     */
    
    char* formatted_msg = hf_vformat_string(msg, args);
    
    // NOTE(salmoncatt): format the color codes
    hf_vector split_at_colors = {};
    hf_vector_init(&split_at_colors);
    hf_string_split(&split_at_colors, "$hfcc{", formatted_msg);
    
    hf_free(formatted_msg);
    
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
            printf("%s", msg_without_color_codes);
        
        hf_free(msg_without_color_codes);
    }
    
    // NOTE(salmoncatt): reset text color back to white and black background
    hf_debug_set_text_color(hf_debug_white, hf_debug_black);
    hf_vector_free(&split_at_colors);
}

void hf_debug_err(const char* msg, ...){
    va_list args;
    va_start(args, msg);
    hf_vlog(msg, args);
    va_end(args);
}

void hf_print_windows_last_error(){
    DWORD errorID = GetLastError();
    if(!errorID){
        hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}] $hfcc{yellow}windows error returned with $hfcc{aqua}0\n");
        return;
    }
    
    LPSTR messageBuffer = NULL;
    
    u64 size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    char message[size];
    strcpy(message, messageBuffer);
    
    // TODO(salmoncatt): make output something cooler than windows error
    hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}] $hfcc{yellow}windows error returned with$hfcc{red}: [$hfcc{yellow}ID$hfcc{red}]: $hfcc{aqua}%lu$hfcc{red} [$hfcc{yellow}MESSAGE$hfcc{red}]: $hfcc{aqua}%s\n", errorID, message);
    
    LocalFree(message);
    free(message);
}

void hf_print_gcc_last_error(){
    
}

void hf_print_errors(){
    hf_print_windows_last_error();
}