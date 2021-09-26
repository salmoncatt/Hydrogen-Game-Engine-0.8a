#include "hfmath.h"
//#include "hfpch.h"

// NOTE(salmoncatt): djb2 hash algorithm: http://www.cse.yorku.ca/~oz/hash.html
u32 hf_hash_str(const char* str){
    u32 out = 5381;
    i32 c;
    
    while ((c = *str++))
        out= ((out << 5) + out) + c;
    return out;
}