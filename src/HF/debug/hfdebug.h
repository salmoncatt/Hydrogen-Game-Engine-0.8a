/* date = August 28th 2021 9:35 am */

#ifndef HFDEBUG_H
#define HFDEBUG_H

#include "../math/hfmath.h"

// NOTE(salmoncatt): in hf app have current foreground and background color pls cool thanks

void hf_debug_init();
void hf_debug_set_text_color(v3f foregroundColor, v3f backgroundColor);

//                                                                       $hf color code
// NOTE(salmoncatt): when displaying text add color codes to the output: $hfcc{255,255,255} would be white or $hfcc{red} would be 255, 0, 0
void hf_debug_err(const char* msg, ...);
void hf_debug_err_msg_box(const char* title, const char* msg, u32 format, ...);

#endif //HFDEBUG_H
