/* date = August 23rd 2021 8:10 pm */

#ifndef TIME_H
#define TIME_H

#include "../core/hfapp.h"

/* 
extern f64 hf_cpu_freq;
extern i64 hf_time_start;
 */

void hf_time_init(hf_app* app);

f64 hf_get_time(hf_app* app);

void hf_time_update(hf_app* app);

f64 hf_get_delta_time(hf_app* app);

#endif //TIME_H
