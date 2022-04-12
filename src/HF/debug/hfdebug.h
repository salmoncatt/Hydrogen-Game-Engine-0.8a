/* date = August 28th 2021 9:35 am */

#ifndef HFDEBUG_H
#define HFDEBUG_H

/* 
struct vec2f;
struct vec3f;
struct vec4f;
 */

// NOTE(salmoncatt): in hf app have current foreground and background color pls cool thanks

// NOTE(salmoncatt): debug text colors (see here for color codes)
typedef enum hf_debug_color {
    hf_debug_black = 0, //type $hfcc{black}
    hf_debug_blue = 1, //type $hfcc{blue}
    hf_debug_green = 2, //type $hfcc{green}
    hf_debug_aqua = 3, //type $hfcc{aqua}
    hf_debug_red = 4, //type $hfcc{red}
    hf_debug_purple = 5, //type $hfcc{purple}
    hf_debug_yellow = 6, //type $hfcc{yellow}
    hf_debug_white = 7, //type $hfcc{white}
    hf_debug_gray = 8, //type $hfcc{gray}
    hf_debug_light_blue = 9, //type $hfcc{light_blue}
    hf_debug_light_green = 10, //type $hfcc{light_green}
    hf_debug_light_aqua = 11, //type $hfcc{light_aqua}
    hf_debug_light_red = 12, //type $hfcc{light_red}
    hf_debug_light_purple = 13, //type $hfcc{light_purple}
    hf_debug_light_yellow = 14, //type $hfcc{light_yellow}
    hf_debug_bright_white = 15 //type $hfcc{bright_white}
} hf_debug_color;


typedef enum hf_debug_color_lookup_table {
	hf_lookup_debug_black = 254362690, //type $hfcc{black}
	hf_lookup_debug_blue = 2090117005, //type $hfcc{blue}
	hf_lookup_debug_green = 260512342, //type $hfcc{green}
	hf_lookup_debug_aqua = 2090086509, //type $hfcc{aqua}
	hf_lookup_debug_red = 193504576, //type $hfcc{red}
	hf_lookup_debug_purple = 363228189, //type $hfcc{purple}
	hf_lookup_debug_yellow = 696252129, //type $hfcc{yellow}
	hf_lookup_debug_white = 279132550, //type $hfcc{white}
	hf_lookup_debug_gray = 2090302584, //type $hfcc{gray}
	hf_lookup_debug_light_blue = 450355300, //type $hfcc{light_blue}
	hf_lookup_debug_light_green = 1982950925, //type $hfcc{light_green}
	hf_lookup_debug_light_aqua = 450324804, //type $hfcc{light_aqua}
	hf_lookup_debug_light_red = 4048330551, //type $hfcc{light_red}
	hf_lookup_debug_light_purple = 1369126580, //type $hfcc{light_purple}
	hf_lookup_debug_light_yellow = 1702150520, //type $hfcc{light_yellow}
	hf_lookup_debug_bright_white = 3252455557 //type $hfcc{bright_white}
} hf_debug_color_lookup_table;

void hf_debug_init();
void hf_debug_set_text_color(hf_debug_color foregroundColor, hf_debug_color backgroundColor);

// NOTE(salmoncatt): lets you use hf color codes: $hfcc{FF0000} makes it red
void hf_log(const char* msg, ...);


//i dont know how this part compiles without including hfmath, probably pch or something
void hf_log_v2f(v2f vec);
void hf_log_v3f(v3f vec);
void hf_log_v4f(v4f vec);

void hf_vlog(const char* msg, va_list list);

// NOTE(salmoncatt): maybe just hex values for color ex. $hfcc{FF00A0}
void hf_debug_err(const char* msg, ...);

void hf_print_windows_last_error();

void hf_print_gcc_last_error();

void hf_print_errors();

// TODO(salmoncatt): finish this
/* 
#ifdef HF_DEBUG
#define hf_warning(msg, ...) hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{yellow}%s$hfcc{red}) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", msg,## __VA_ARGS__, __FILE__, __FUNCTION__, __LINE__);\
MessageBox(NULL, msg, __FILE__, MB_OK | MB_ICONERROR)
#else
#define hf_warning(msg, ...) hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{yellow}%s$hfcc{red}) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", msg, ##__VA_ARGS__, __FILE__, __FUNCTION__, __LINE__);

#endif
 */

#ifdef HF_DEBUG
#define hf_err(msg, ...) do{ char* HF_FORMATTED_MSG_STRING = hf_format_string(msg, ##__VA_ARGS__); hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{yellow}%s$hfcc{red}) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", HF_FORMATTED_MSG_STRING, __FILE__, __FUNCTION__, __LINE__); MessageBox(NULL, msg, __FILE__, MB_OK | MB_ICONERROR); hf_print_errors(); hf_free(HF_FORMATTED_MSG_STRING);} while(0)
#else
#define hf_err(msg, ...) do{ char* HF_FORMATTED_MSG_STRING = hf_format_string(msg, ##__VA_ARGS__); hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{yellow}%s$hfcc{red}) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", HF_FORMATTED_MSG_STRING, __FILE__, __FUNCTION__, __LINE__); hf_free(HF_FORMATTED_MSG_STRING);} while(0)
#endif

#define hf_exit(exit_code) do{hf_log("$hfcc{red}[$hfcc{yellow}HF$hfcc{red}] ($hfcc{yellow}exiting with error code:$hfcc{aqua} %i$hfcc{red})\n", exit_code); exit(exit_code);} while(0)


#endif //HFDEBUG_H
