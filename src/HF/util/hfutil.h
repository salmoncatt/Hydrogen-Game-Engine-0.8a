/* date = August 16th 2021 0:46 pm */

#ifndef HFUTIL_H
#define HFUTIL_H

#include <immintrin.h>
#include "../datatypes/hfdatatypes.h"
#include "../debug/hfdebug.h"

// NOTE(salmoncatt): assert functions

#define assert(expression) if(expression) {} else { hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{aqua}expression: $hfcc{yellow}%s) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else { hf_debug_err("$hfcc{red}[$hfcc{yellow}HF Error$hfcc{red}]: ($hfcc{aqua}expression: $hfcc{red}[$hfcc{yellow}%s$hfcc{red}] $hfcc{aqua}with msg: $hfcc{red}[$hfcc{yellow}%s$hfcc{red}]) threw at: [$hfcc{aqua}file: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}function: $hfcc{yellow}%s$hfcc{red}] [$hfcc{aqua}line: $hfcc{yellow}%i$hfcc{red}]\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__);  }


/* 
printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }
 */

// TODO(salmoncatt): add static asserts pls

extern void* hf_memcpy(void* destination, const void* source, u64 size);

// NOTE(salmoncatt): compares two memory addresses for equality
extern b8 hf_memcmp(const void* a, const void* b, size_t bytes);

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
