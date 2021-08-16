/* date = August 15th 2021 8:25 pm */

#ifndef HFMATH_H
#define HFMATH_H

#include <stdint.h>


//yoinked from tsfoundation.h (heh)
typedef int8_t    int8;
typedef int16_t   int16;
typedef int32_t   int32;
typedef int64_t   int64;
typedef uint8_t   uint8;
typedef uint16_t  uint16;
typedef uint32_t  uint32;
typedef uint64_t  uint64;
typedef float     real32;
typedef double    real64;
typedef float     float32;
typedef double    float64;
typedef int8      bool8;
typedef int16     bool16;
typedef int32     bool32;
typedef int64     bool64;


// NOTE(salmoncatt): data types
typedef int8      i8;
typedef int16     i16;
typedef int32     i32;
typedef int64     i64;
typedef uint8     u8;
typedef uint16    u16;
typedef uint32    u32;
typedef uint64    u64;
typedef real32    r32;
typedef real64    r64;
typedef float32   f32;
typedef float64   f64;
typedef bool8     b8;
typedef bool16    b16;
typedef bool32    b32;
typedef bool64    b64;


// NOTE(salmoncatt): vector types
typedef struct {
    f32 x;
    f32 y;
    
} v2;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    
} v3;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    
} v4;

//adds a and b and returns the result
v2 v2_add_v2(v2* a, v2* b);
//adds a and b and stores the result in a
v2 v2_addsto_v2(v2* a, v2* b);

//adds a and b and returns the result
v3 v3_add_v3(v3* a, v3* b);
//adds a and b and stores the result in a
v3 v3_addsto_v3(v3* a, v3* b);

//adds a and b and returns the result
v4 v4_add_v4(v4* a, v4* b);
//adds a and b and stores the result in a
v4 v4_addsto_v4(v4* a, v4* b);
#endif //HFMATH_H
