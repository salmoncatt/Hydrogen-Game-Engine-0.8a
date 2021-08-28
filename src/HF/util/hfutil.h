/* date = August 16th 2021 0:46 pm */

#ifndef HFUTIL_H
#define HFUTIL_H

#include <immintrin.h>
#include "../datatypes/hfdatatypes.h"

// NOTE(salmoncatt): assert functions

#define assert(expression) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

#define assertf(expression,msg) if(expression) {} else {  printf("[ERROR ASSERT]: [%s] returned false, with message: [%s], in file: [%s], in function: [%s], at line: [%i]\n\n", #expression, msg, __FILE__, __FUNCTION__, __LINE__); exit(-1); }

// TODO(salmoncatt): add static asserts pls

extern void* hfmemcpy(void* destination, const void* source, u64 size);

extern u64 hfstrlen(const char* data);

extern const u64 hf_string_npos;
extern u64 hfstrfind(const char delimiter, const char* data, u64 startingIndex);

extern char* hfstrcpy(char* destination, const char* source, u64 offset);

extern void* hfmalloc(u64 bytes);

//inline char* strcpywoffset


// NOTE(salmoncatt): windows get last error
void printWindowsLastError();

#endif //HFUTIL_H
