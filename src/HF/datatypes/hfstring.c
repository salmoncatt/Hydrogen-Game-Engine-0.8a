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
    
    uptr endingPointer = (uptr)(data + size);
    
    // NOTE(salmoncatt): population count (otherwise known as counting the ones in binary form)
    u32 totalPopcnt = 0;
    
    /* 
        __m256i* mdata = (__m256i*)(data + out);
        __m256i* mdelimiter = (__m256i*)(delimiter);
        const __m256i currentDelimiter = _mm256_loadu_si256(mdelimiter);
        
        for(;; mdata++){
            const __m256i current = _mm256_loadu_si256(mdata);
            const __m256i compare = _mm256_cmpeq_epi8(current, currentDelimiter);
            u32 mask = _mm256_movemask_epi8(compare);
     */
    
    __m128i* mdata = (__m128i*)(data + out);
    __m128i* mdelimiter = (__m128i*)(delimiter);
    const __m128i currentDelimiter = _mm_loadu_si128(mdelimiter);
    
    for(;(uptr)mdata < endingPointer; mdata++){
        const __m128i current = _mm_loadu_si128(mdata);
        const __m128i compare = _mm_cmpeq_epi8(current, currentDelimiter);
        // NOTE(salmoncatt): u16 so i dont have to chop off anything past the 16th bit
        u16 mask = _mm_movemask_epi8(compare);
        
        u32 highestZero = hfHighestOneBit(mask);
        
        printf("%u\n", highestZero);
        mask <<= highestZero;
        mask >>= highestZero;
        
        u32 popcnt = _mm_popcnt_u32(mask);
        totalPopcnt = popcnt;
        
        hfPrintBits(sizeof(mask), &mask);
        
        if(totalPopcnt >= sizeDelimiter){
            return ((char*)mdata - data);
        }else if(popcnt < 16 && hf_ctzu32(popcnt) == 0){
            totalPopcnt = 0;
        }
    }
    
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