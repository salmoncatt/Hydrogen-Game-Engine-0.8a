#include "hffloatbuffer.h"

void hf_f32_buf_init(hf_f32_buf* buffer, u32 size){
    buffer->data = hf_malloc(sizeof(f32) * size);
    buffer->index = 0;
    buffer->size = size;
}

void hf_f32_buf_destroy(hf_f32_buf* buffer){
    hf_free(buffer->data);
}

void hf_f32_buf_put(hf_f32_buf* buffer, u32 index, f32 value){
    if(index < buffer->size)
        buffer->data[index] = value;
    else
        hf_err("[HF ERR] trying to set value in buffer that is out of range, buffer size: [%u], index requested: [%u], value: [%f]\n", buffer->size, index, value);
}

void hf_f32_buf_store_m4f(hf_f32_buf* buffer, m4f* matrix){
    hf_f32_buf_put(buffer, 0, matrix->m00);
    hf_f32_buf_put(buffer, 1, matrix->m01);
    hf_f32_buf_put(buffer, 2, matrix->m02);
    hf_f32_buf_put(buffer, 3, matrix->m03);
    hf_f32_buf_put(buffer, 4, matrix->m10);
    hf_f32_buf_put(buffer, 5, matrix->m11);
    hf_f32_buf_put(buffer, 6, matrix->m12);
    hf_f32_buf_put(buffer, 7, matrix->m13);
    hf_f32_buf_put(buffer, 8, matrix->m20);
    hf_f32_buf_put(buffer, 9, matrix->m21);
    hf_f32_buf_put(buffer, 10, matrix->m22);
    hf_f32_buf_put(buffer, 11, matrix->m23);
    hf_f32_buf_put(buffer, 12, matrix->m30);
    hf_f32_buf_put(buffer, 13, matrix->m31);
    hf_f32_buf_put(buffer, 14, matrix->m32);
    hf_f32_buf_put(buffer, 15, matrix->m33);
}

