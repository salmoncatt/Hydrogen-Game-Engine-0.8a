/* date = August 15th 2021 8:25 pm */

#ifndef HFMATH_H
#define HFMATH_H

#include "../datatypes/hfdatatypes.h"

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
