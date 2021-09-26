/* date = August 28th 2021 10:29 am */

#ifndef HFSTRING_H
#define HFSTRING_H

#include "hfvector.h"

void hf_string_split(hf_vector* vector, const char* delimiter, const char* data);

//u64 hfStringFind(const char* delimiter, const char* data);

u64 hf_string_find(const char* delimiter, const char* data, u64 startingIndex);

char* hf_string_substr(const char* data, u64 start, u64 end);

#endif //HFSTRING_H
