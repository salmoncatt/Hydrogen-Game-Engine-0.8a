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
typedef struct v2f{
    f32 x;
    f32 y;
    
} v2f;

typedef struct v3f{
    f32 x;
    f32 y;
    f32 z;
    
} v3f;

typedef struct v4f{
    f32 x;
    f32 y;
    f32 z;
    
} v4f;

//adds a and b and returns the result
v2f v2f_add_v2f(v2f* a, v2f* b);
//adds a and b and stores the result in a
v2f v2f_addsto_v2f(v2f* a, v2f* b);

//adds a and b and returns the result
v3f v3f_add_v3f(v3f* a, v3f* b);
//adds a and b and stores the result in a
v3f v3f_addsto_v3f(v3f* a, v3f* b);

//adds a and b and returns the result
v4f v4f_add_v4f(v4f* a, v4f* b);
//adds a and b and stores the result in a
v4f v4f_addsto_v4f(v4f* a, v4f* b);
#endif //HFMATH_H
