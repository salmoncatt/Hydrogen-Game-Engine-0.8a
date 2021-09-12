#include "hfstring.h"
#include "../util/hfutil.h"
#include "../debug/hfdebug.h"
#include <stdio.h>

/* 
u64 hfStringFind(const char* delimiter, const char* data){
    return 0;
}
 */

u64 hf_string_find(const char* delimiter, const char* data, u64 startingIndex){
    u64 size = hf_strlen(data);
    u64 sizeDelimiter = hf_strlen(delimiter);
    
    if(size < sizeDelimiter + startingIndex)
        return hf_string_npos;
    
    u64 index = 0;
    while((index = hf_strfind(delimiter[0], data, startingIndex + index, size)) != hf_string_npos){
        if(hf_memcmp(data + index, delimiter, sizeDelimiter))
            return index;
    }
    
    return hf_string_npos;
}

char* hf_string_substr(const char* data, u64 start, u64 end){
    u64 size = hf_strlen(data);
    char* out;
    
    if(start > size){
        hf_debug_err("err string substr");
        return NULL;
    }
    
    if(end > size){
        u64 newLength = size - start;
        out = (char*)hf_malloc(newLength + 1);
        
    }else{
        out = (char*)hf_malloc(end - start);
        
        hf_memcpy(out, data + start, start + end + 1);
        
        out[end] = '\0';
    }
    
    return out;
}

void hf_string_split(hf_vector* vector, const char* delimiter, const char* data){
    u64 index;
    
    // NOTE(salmoncatt): cring scalar code
    while((index = hf_string_find(delimiter, data, index)) != hf_string_npos){
        hf_vector_push_back(vector, hf_string_substr(data, index, index + hf_strlen(delimiter)));
        index += hf_strlen(delimiter);
    }
    
    if((index = hf_string_find(delimiter, data, index)) != hf_string_npos)
        hf_vector_push_back(vector, hf_string_substr(data, index, index + hf_strlen(delimiter)));
}