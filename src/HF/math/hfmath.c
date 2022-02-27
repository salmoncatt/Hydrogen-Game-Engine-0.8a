#include "hfmath.h"
//#include "hfpch.h"

v4f hf_v4f(f32 x, f32 y, f32 z, f32 w){
    v4f out;
    
    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
    
    return out;
}

// NOTE(salmoncatt): djb2 hash algorithm: http://www.cse.yorku.ca/~oz/hash.html
u32 hf_hash_str(const char* str){
    u32 out = 5381;
    i32 c;
    
    while ((c = *str++))
        out= ((out << 5) + out) + c;
    return out;
}