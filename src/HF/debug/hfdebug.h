/* date = August 28th 2021 9:35 am */

#ifndef HFDEBUG_H
#define HFDEBUG_H

#include "../math/hfmath.h"

// NOTE(salmoncatt): in hf app have current foreground and background color pls cool thanks

void hfDebugInit();
void hfDebugSetTextColor(v3f foregroundColor, v3f backgroundColor);

//                                                                       $hf color code
// NOTE(salmoncatt): when displaying text add color codes to the output: $hfcc{255,255,255} would be white or $hfcc{red} would be 255, 0, 0
void hfDebugErr(const char* msg, ...);
void hfDebugErrMsgBox(const char* title, const char* msg, u32 format, ...);

#endif //HFDEBUG_H
