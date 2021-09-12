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
        printf("err string substr");
        return NULL;
    }
    
    
    if(end > size){
        u64 newLength = size - start;
        out = (char*)hf_malloc(sizeof(char) * (newLength + 1));
        hf_memcpy(out, data + start, newLength);
        out[size] = '\0';
        
    }else{
        out = hf_malloc(sizeof(char) * (end - start + 1));
        hf_memcpy(out, &data[start], end - start);
        out[end - start] = '\0';
    }
    
    return out;
}

void hf_string_split(hf_vector* vector, const char* delimiter, const char* data){
    u64 index = 0;
    u64 previousIndex = 0;
    u64 sizeDelimiter = hf_strlen(delimiter);
    u64 size = hf_strlen(data);
    //char* current = (char*)data;
    
    while((index = hf_string_find(delimiter, data, index)) != hf_string_npos){
        hf_vector_push_back(vector, hf_string_substr(data, previousIndex, index));
        //printf("cur: %u %u\n", previousIndex, index);
        
        index += sizeDelimiter;
        previousIndex = index;
    }
    
    
    if(previousIndex < size){
        hf_vector_push_back(vector, hf_string_substr(data, previousIndex, size));
        
        //printf("cur: %u %u\n", previousIndex + 1, size);
    }
}