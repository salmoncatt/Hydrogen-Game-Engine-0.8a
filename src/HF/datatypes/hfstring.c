#include "hfstring.h"
#include "../util/hfutil.h"
#include "../debug/hfdebug.h"
#include <stdio.h>

/* 
u64 hfStringFind(const char* delimiter, const char* data){
    return 0;
}
 */

u64 hfStringFind(const char* delimiter, const char* data, u64 startingIndex){
    u64 size = hfstrlen(data);
    u64 out = hfstrfind(delimiter[0], data, startingIndex, size);
    if(out == hf_string_npos)
        return out;
    
    u64 sizeDelimiter = hfstrlen(delimiter);
    if(sizeDelimiter == 1)
        return out; //no need to do all this shit if we already found the single character
    
    
    
    // NOTE(salmoncatt): population count (otherwise known as counting the ones in binary form)
    u32 popcnt = 0;
    
    __m128i* mdata = (__m128i*)(data + out);
    __m128i* mdelimiter = (__m128i*)(delimiter);
    const __m128i currentDelimiter = _mm_loadu_si128(mdelimiter);
    
    for(;; mdata++){
        const __m128i current = _mm_loadu_si128(mdata);
        const __m128i compare = _mm_cmpeq_epi8(current, currentDelimiter);
        u32 mask = _mm_movemask_epi8(compare);
        
        // NOTE(salmoncatt): can only do this if size < 16 rn
        // NOTE(salmoncatt): this removes anything past the delimiter that may be true (such as null termination character, or just random memory)
        mask = mask << (32 - sizeDelimiter); 
        mask = mask >> (32 - sizeDelimiter);
        
        popcnt += _mm_popcnt_u32(mask);
        
        
        hfPrintBits(sizeof(mask), &mask);
        //printf("popcnt: %u\n", hf_ctzu32(mask));
        
        if(popcnt >= sizeDelimiter)
            return ((char*)mdata - data);
        else
            return hf_string_npos;
        
        /* 
                if(mask){
                    
                    
                    
                    
                    
                    
                    
                    printf("hfstringfind: %u\n", (((char*)mdata - data)));
                    printf("popcnt: %u\n", _mm_popcnt_u32(mask));
                    hfPrintBits(sizeof(mask), &mask);
                    //printf("ctz: %I32u", hf_ctzu32(mask));
                    return hf_ctzu32(mask);
                    break;
                }
         */
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
        out = (char*)hf_malloc(newLength + 1);
        
    }else{
        out = (char*)hf_malloc(end - start);
        
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