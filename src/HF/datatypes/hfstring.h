/* date = August 28th 2021 10:29 am */

#ifndef HFSTRING_H
#define HFSTRING_H

#include "hfvector.h"
#include "hfdatatypes.h"

void hfStringSplit(hf_vector* vector, const char* delimiter, const char* data);

//u64 hfStringFind(const char* delimiter, const char* data);

u64 hfStringFind(const char* delimiter, const char* data, u64 startingIndex);

char* hfStringSubstr(const char* data, u64 start, u64 end);

#endif //HFSTRING_H
