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
        const __m128i comparison = _mm_cmpeq_epi8(current, zeros);
        u32 mask = _mm_movemask_epi8(comparison);
        
        if(mask){
            return ((char*)(pointer) - data) + hf_ctzu32(mask);
        }
        
        /* 
                if (_mm_cmpistrc(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
                    int index = _mm_cmpistri(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
                    
                    return ((char*)(pointer) - data) + index;
                }
         */
    }
}

// TODO(salmoncatt): convert strlen and strfind to _mm256i
extern u64 hfstrfind(const char d, const char* data, u64 startingIndex){
    // TODO(salmoncatt): make this faster pls (and hfStringFind too)
    const __m128i delimiters = _mm_set_epi8(d, d, d, d, d, d, d, d, d, d, d, d, d, d, d, d);
    const __m128i zeros = _mm_setzero_si128();
    __m128i* pointer = (__m128i*)(data + startingIndex);
    
    u64 size = hfstrlen(data);
    if(startingIndex >= size)
        return hf_string_npos;
    
    for(;((char*)(pointer) - data) + 16 < size;){
        const __m128i current = _mm_loadu_si128(pointer);
        __m128i comparison = _mm_cmpeq_epi8(current, delimiters);
        u32 mask = _mm_movemask_epi8(comparison);
        
        if(mask){
            return ((char*)(pointer) - data) + hf_ctzu32(mask);
        }
        
        /* 
                if (_mm_cmpistrc(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH)) {
                    int index = _mm_cmpistri(current, delimiters, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH);
                    
                    return ((char*)(pointer) - data) + index;
                }else if(_mm_cmpistrc(current, zeros, _SIDD_UBYTE_OPS | _SIDD_LEAST_SIGNIFICANT | _SIDD_CMP_EQUAL_EACH))
                    return hf_string_npos;
         */
        
        pointer++;
    }
    
    return hf_string_npos;
}

extern char* hfstrcpy(char* destination, const char* source, u64 offset){
    return (char*)hfmemcpy(destination, source + offset, hfstrlen(source) + 1 - offset);
}

extern void* hf_malloc(u64 bytes){
    return malloc(bytes);
}

extern void hf_free(void* pointer){
    free(pointer);
}

char* hfConvertToBits(u64 size, const void* data){
    /* 
char* bytes = (char*)data;
char* out = (char*)hf_malloc((size * 8) + 1);
char byte;
int i, j;

for(i = size - 1; i >= 0; i--){
for(j = 7; j >= 0; j--){
byte = (bytes[i] >> j) & 1;
//out[i * j] = byte;
//printf("%u", byte);
}
}
puts("");


out[size * 8] = '\0';

return out;
*/
    return 0;
}

void hfPrintBits(u64 size, const void* data){
    char* bytes = (char*)data;
    char byte;
    int i, j;
    
    for(i = size - 1; i >= 0; i--){
        for(j = 7; j >= 0; j--){
            byte = (bytes[i] >> j) & 1;
            printf("%u", byte);
        }
    }
    puts("");
}

u32 hf_ctzu32(u32 in){
    u32 c = 32; // c will be the number of zero bits on the right
    in &= -in;
    if (in) c--;
    if (in & 0x0000FFFF) c -= 16;
    if (in & 0x00FF00FF) c -= 8;
    if (in & 0x0F0F0F0F) c -= 4;
    if (in & 0x33333333) c -= 2;
    if (in & 0x55555555) c -= 1;
    
    return c;
    //return __builtin_ctz(in);
}

u32 hfHighestOneBit(u32 in){
    in |= (in >>  1);
    in |= (in >>  2);
    in |= (in >>  4);
    in |= (in >>  8);
    in |= (in >> 16);
    return in - (in >> 1);
}