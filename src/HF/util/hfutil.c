#include "hfutil.h"
#include <stdio.h>
#include "../math/hfmath.h"
#include <windows.h>
#include <immintrin.h>

const u64 hf_string_npos = -1;

void printWindowsLastError(){
    
    DWORD errorID = GetLastError();
    if(!errorID){
        printf("[ERROR] windows error returned with 0\n");
        return;
    }
    
    LPSTR messageBuffer = NULL;
    
    u64 size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM| FORMAT_MESSAGE_IGNORE_INSERTS, NULL, errorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
    char message[size];
    strcpy(message, messageBuffer);
    
    // TODO(salmoncatt): make output something cooler than windows error
    printf("[ERROR] windows error returned with: [ID]: %lu [MESSAGE]: %s\n", errorID, message);
    
    LocalFree(message);
    free(message);
}

extern void* hfmemcpy(void* destination, const void* source, u64 size){
    char* dest = (char*)destination;
    const char* src = (const char*)source;
    
    u64 length = size;
    
#ifdef __AVX512__
    while (size >= 64) {
        __m256i val = _mm512_loadu_si512((__m512i*)(src));
        _mm512_storeu_si512((__m512i*)dest, val);
        dest += 64;
        src += 64;
        size -= 64;
    }
#endif
    
    while (size >= 32) {
        __m256i val = _mm256_loadu_si256((__m256i*)(src));
        _mm256_storeu_si256((__m256i*)dest, val);
        dest += 32;
        src += 32;
        size -= 32;
    }
    
    while (size >= 16) {
        __m128i val = _mm_loadu_si128((__m128i*)(src));
        _mm_storeu_si128((__m128i*)dest, val);
        dest += 16;
        src += 16;
        size -= 16;
    }
    
    if (length > 16) {
        src += size - 16;
        dest += size - 16;
        __m128i val = _mm_loadu_si128((__m128i*)(src));
        _mm_storeu_si128((__m128i*)(dest), val);
    }
    
    
    // TODO(salmoncatt): add masked load and store instead of this scalar crap pls
    while (size--) {
        *dest++ = *src++;
    }
    
    return destination;
}

extern u64 hfstrlen(const char* data){
    // TODO(salmoncatt): make this faster pls (and hfStringFind too)
    const __m128i zeros = _mm_setzero_si128();
    __m128i* pointer = (__m128i*)(data);
    
    for (;; pointer++) {
        
        const __m128i current = _mm_loadu_si128(pointer);
        
        if (_mm_cmpistrc(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
            int index = _mm_cmpistri(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
            
            return ((char*)(pointer) - data) + index;
        }
    }
}

// TODO(salmoncatt): convert strlen and strfind to _mm256i
extern u64 hfstrfind(const char d, const char* data, u64 startingIndex){
    // TODO(salmoncatt): make this faster pls (and hfStringFind too)
    const __m128i delimiters = _mm_set_epi8(d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d);
    const __m128i zeros = _mm_setzero_si128();
    __m128i* pointer = (__m128i*)(data + startingIndex);
    
    for(;;){
        const __m128i current = _mm_loadu_si128(pointer);
        
        if (_mm_cmpistrc(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
            int index = _mm_cmpistri(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
            
            return ((char*)(pointer) - data) + index;
        }else if(_mm_cmpistrc(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH))
            return hf_string_npos;
        
        pointer++;
    }
    
    /* 
        while(out + 16 < end){
            const __m128i current = _mm_loadu_si128(pointer);
            
            if (_mm_cmpistrc(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
                int index = _mm_cmpistri(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
                
                return out + index;
            }
            
            pointer++;
            out += 16;
        }
     */
    
    return hf_string_npos;
}

extern char* hfstrcpy(char* destination, const char* source, u64 offset){
    return (char*)hfmemcpy(destination, source + offset, hfstrlen(source) + 1 - offset);
}

extern void* hfmalloc(u64 bytes){
    return malloc(bytes);
}