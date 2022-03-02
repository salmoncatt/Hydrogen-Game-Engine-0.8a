/* date = March 1st 2022 6:33 pm */

#ifndef HFFLOATBUFFER_H
#define HFFLOATBUFFER_H

#include "../math/hfmath.h"

typedef struct hf_f32_buf{
    
    f32* data;
    u32 index;
    f64 size;
    
} hf_f32_buf;

void hf_f32_buf_init(hf_f32_buf* buffer, u32 size);
void hf_f32_buf_destroy(hf_f32_buf* buffer);
void hf_f32_buf_put(hf_f32_buf* buffer, u32 index, f32 value);
void hf_f32_buf_store_m4f(hf_f32_buf* buffer, m4f* matrix);


#endif //HFFLOATBUFFER_H
