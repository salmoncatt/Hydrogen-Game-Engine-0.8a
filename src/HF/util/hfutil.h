/* date = August 16th 2021 0:46 pm */

#ifndef HFUTIL_H
#define HFUTIL_H

#include <immintrin.h>
#include "../datatypes/hfdatatypes.h"

// NOTE(salmoncatt): assert functions

#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

// TODO(salmoncatt): add static asserts pls

extern void* hf_memcpy(void* destination, const void* source, u64 size);

// NOTE(salmoncatt): compares two memory addresses for equality
extern b8 hf_memcmp(const void* a, const void* b, size_t bytes);

// NOTE(salmoncatt): returns index at which memcmp fails
extern b8 hf_memcmp_ri(const void* a, const void* b, size_t bytes, size_t* return_index);

extern u64 hf_strlen(const char* data);

extern const u64 hf_string_npos;
extern u64 hf_strfind(const char delimiter, const char* data, u64 startingIndex, u64 endingIndex);
//extern u64 hfstrfind(const char delimiter, const char* data, u64 startingIndex);

extern char* hf_strcpy(char* destination, const char* source, u64 offset);

extern void* hf_malloc(u64 bytes);

extern void hf_free(void* pointer);

// NOTE(salmoncatt): NEEDS TO BE A REFERENCE TO THE DATA
//char* hf_convert_to_bits(u64 size, const void* data);

void hf_print_bits(const void* data, u64 size);

// NOTE(salmoncatt): count trailing zeros of a u32
u32 hf_ctzu32(u32 in);

/* 
u32 hfHighestOneBit(u32 in);
u32 hfHighestZeroBit(u32 in);
 */

// NOTE(salmoncatt): windows get last error
void hf_print_windows_last_error();

#endif //HFUTIL_H
