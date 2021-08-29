#include "hfstring.h"
#include "../util/hfutil.h"
#include "../debug/hfdebug.h"

/* 
u64 hfStringFind(const char* delimiter, const char* data){
    return 0;
}
 */

u64 hfStringFind(const char* delimiter, const char* data, u64 startingIndex){
    u64 out = hfstrfind(delimiter[0], data, startingIndex);
    if(out == hf_string_npos)
        return out;
    
    u64 end = hfstrlen(delimiter);
    //b8 inDelimiter = 0;
    
    //u64 end = hfstrlen(data);
    //u64 index = out;
    
    __m128i* mdata = (__m128i*)(data);
    __m128i* mdelimiter = (__m128i*)(delimiter);
    const __m128i currentDelimiter = _mm_loadu_si128(mdelimiter);
    
    for(;; mdata++){
        const __m128i current = _mm_loadu_si128(pointer);
        
    }
    
    /* 
        for(;; mdata++){
            const __m128i currentData = _mm_loadu_si128(mdata);
            i8 result = _mm_testz_si128(currentData, currentDelimiter);
            
            if(result)
                inDelimiter = 1;
        }
     */
    
    /* 
        for(;index < end - 15; mdata++, index += 16){
            
            const __m128i currentData = _mm_loadu_si128(mdata);
            i8 result = _mm_testz_si128(currentData, currentDelimiter);
            
            if(result){
            }
            
        }
     */
    
    return hf_string_npos;
}

char* hfStringSubstr(const char* data, u64 start, u64 end){
    u64 size = hfstrlen(data);
    char* out;
    
    if(start > size){
        hfDebugErr("err");
        return NULL;
    }
    
    if(end > size){
        u64 newLength = size - start;
        out = (char*)hfmalloc(newLength + 1);
        
    }else{
        out = (char*)hfmalloc(end - start);
        
        hfmemcpy(out, data + start, start + end + 1);
        
        out[end] = '\0';
    }
    
    return out;
}

void hfStringSplit(hf_vector* vector, const char* delimiter, const char* data){
    u64 index;
    
    // NOTE(salmoncatt): cring scalar code
    while((index = hfStringFind(delimiter, data, index)) != hf_string_npos){
        hfVectorPushBack(vector, hfStringSubstr(data, index, index + hfstrlen(delimiter)));
        index += hfstrlen(delimiter);
    }
    
    if((index = hfStringFind(delimiter, data, index)) != hf_string_npos)
        hfVectorPushBack(vector, hfStringSubstr(data, index, index + hfstrlen(delimiter)));
}