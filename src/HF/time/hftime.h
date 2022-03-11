/* date = August 23rd 2021 8:10 pm */

#ifndef TIME_H
#define TIME_H

#include "../core/hfapp.h"


extern f64 hf_cpu_freq;
extern i64 hf_time_start;

extern f64 hf_fps_smoothing;
extern f64 hf_frame_time;
extern f64 hf_last_frame_time;
extern f64 hf_last_fps;

void hf_time_init(f64 fps_smoothing);

f64 hf_get_time();

void hf_time_update();

f64 hf_get_delta_time();

u32 hf_get_fps();

void hf_limit_fps(f64 fps);

void hf_sleep(f64 milli);

#endif //TIME_H
