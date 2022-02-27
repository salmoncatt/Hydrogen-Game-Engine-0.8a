/* date = August 15th 2021 8:25 pm */

#ifndef HFMATH_H
#define HFMATH_H

#include "../datatypes/hfdatatypes.h"

#define hf_min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; }) \

#define hf_max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; }) \


// NOTE(salmoncatt): vector types
typedef union v2f{
    
    struct{
        f32 x, y;
    };
    
    struct{
        f32 u, v;
    };
    
    struct{
        f32 left, right;
    };
    
    struct{
        f32 width, height;
    };
    
    struct{
        f32 w, h;
    };
    
    f32 elements[2];
    
} v2f;

typedef union v3f{
    
    struct{
        f32 x, y, z;
    };
    
    struct{
        f32 u, v, w;
    };
    
    struct{
        f32 r, g, b;
    };
    
    struct{
        v2f xy;
        f32 ignored0_;
    };
    
    struct{
        f32 ignored1_;
        v2f yz;
    };
    
    struct{
        v2f uv;
        f32 ignored2_;
    };
    
    struct{
        f32 ignored3_;
        v2f vw;
    };
    
    f32 elements[3];
    
} v3f;

typedef union v4f{
    
    struct{
        
        union{
            v3f xyz;
            struct{
                f32 x, y, z;
            };
            f32 w;
        };
    };
    
    struct{
        
        union{
            v3f rgb;
            struct{
                f32 r, g, b;
            };
        };
        f32 a;
    };
    
    struct{
        v2f xy;
        f32 ignored0_;
        f32 ignored1_;
    };
    
    struct{
        f32 ignored2_;
        v2f yz;
        f32 ignored3_;
    };
    
    struct{
        f32 ignored4_;
        f32 ignored5_;
        v2f zw;
    };
    
    f32 elements[4];
    
} v4f;

// TODO(salmoncatt): do this
typedef struct m4f{
    f32 x;
    f32 y;
    f32 z;
    f32 w;
    
} m4f;

typedef struct hf_transform{
    v3f pos;
    v3f rot;
    v3f scale;
} hf_transform;

v4f hf_v4f(f32 x, f32 y, f32 z, f32 w);

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

u32 hf_hash_str(const char* str);

#endif //HFMATH_H
