/* date = August 15th 2021 8:25 pm */

#ifndef HFMATH_H
#define HFMATH_H

#include "../datatypes/hfdatatypes.h"

#define hf_inline

#define hf_min(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a < _b ? _a : _b; }) \

#define hf_max(a,b) \
({ __typeof__ (a) _a = (a); \
__typeof__ (b) _b = (b); \
_a > _b ? _a : _b; }) \

#define hf_abs(x)  ( ( (x) < 0) ? -(x) : (x) )

const extern f64 hf_PI;


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
        };
        f32 w;
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

typedef struct m4f{
    f32 m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33;
} m4f;

typedef struct hf_transform{
    v3f pos;
    v3f rot;
    v3f scale;
} hf_transform;

typedef struct hf_transform_2d{
    v2f pos;
    v2f rot;
    v2f scale;
} hf_transform_2d;

//mainly for gui
typedef struct hf_rect{
    u32 x;
    u32 y;
    u32 w;
    u32 h;
} hf_rect;


hf_inline f32 hf_f_sqrt(f32 in);
hf_inline f32 hf_f_isqrt(f32 in);

hf_inline v2f hf_v2f(f32 x, f32 y);
hf_inline v3f hf_v3f(f32 x, f32 y, f32 z);
hf_inline v4f hf_v4f(f32 x, f32 y, f32 z, f32 w);

hf_inline v2f hf_normalize_v2f(v2f vec);
hf_inline v3f hf_normalize_v3f(v3f vec);
hf_inline v4f hf_normalize_v4f(v4f vec);

hf_inline f32 hf_length_v2f(v2f vec);
hf_inline f32 hf_length_v3f(v3f vec);
hf_inline f32 hf_length_v4f(v4f vec);

hf_inline f32 hf_ilength_v2f(v2f vec);
hf_inline f32 hf_ilength_v3f(v3f vec);
hf_inline f32 hf_ilength_v4f(v4f vec);

hf_inline v2f hf_add_v2f(v2f a, v2f b);
hf_inline v2f hf_sub_v2f(v2f a, v2f b);
hf_inline v2f hf_mul_v2f(v2f a, v2f b);
hf_inline v2f hf_div_v2f(v2f a, v2f b);

hf_inline v2f hf_add_v2f_f(v2f a, f32 b);
hf_inline v2f hf_sub_v2f_f(v2f a, f32 b);
hf_inline v2f hf_mul_v2f_f(v2f a, f32 b);
hf_inline v2f hf_div_v2f_f(v2f a, f32 b);


hf_inline v3f hf_add_v3f(v3f a, v3f b);
hf_inline v3f hf_sub_v3f(v3f a, v3f b);
hf_inline v3f hf_mul_v3f(v3f a, v3f b);
hf_inline v3f hf_div_v3f(v3f a, v3f b);

hf_inline v3f hf_add_v3f_f(v3f a, f32 b);
hf_inline v3f hf_sub_v3f_f(v3f a, f32 b);
hf_inline v3f hf_mul_v3f_f(v3f a, f32 b);
hf_inline v3f hf_div_v3f_f(v3f a, f32 b);


hf_inline v4f hf_add_v4f(v4f a, v4f b);
hf_inline v4f hf_sub_v4f(v4f a, v4f b);
hf_inline v4f hf_mul_v4f(v4f a, v4f b);
hf_inline v4f hf_div_v4f(v4f a, v4f b);

hf_inline v4f hf_add_v4f_f(v4f a, f32 b);
hf_inline v4f hf_sub_v4f_f(v4f a, f32 b);
hf_inline v4f hf_mul_v4f_f(v4f a, f32 b);
hf_inline v4f hf_div_v4f_f(v4f a, f32 b);


hf_inline m4f hf_mul_m4f(m4f a, m4f b);


hf_inline void hf_identity_m4f(m4f* src);
hf_inline void hf_transpose_m4f(m4f* dest, m4f* src);
hf_inline void hf_transpose_no_rotation_m4f(m4f* dest, m4f* src);
hf_inline void hf_scale_m4f(m4f* matrix, v3f scale);
//hf_inline void hf_scale_m4f_v3f(m4f* matrix, v3f scale);
//hf_inline void hf_scale_m4f_v2f(m4f* matrix, v2f scale);
void hf_rotate_m4f(m4f* matrix, f32 angle, v3f axis);
hf_inline void hf_translate_m4f(m4f* matrix, v3f translation);
//hf_inline void hf_translate_m4f_v3f(m4f* matrix, v3f translation);
//hf_inline void hf_translate_m4f_v2f(m4f* matrix, v2f translation);

m4f hf_transformation_m4f(v3f translation, v3f rotation, v3f scale);
m4f hf_transformation_m4f_2d(v2f translation, f32 rotation, v2f scale);
//m4f hf_transformation_m4f_v3f(v3f translation, v3f rotation, v3f scale);
//m4f hf_transformation_m4f_v2f(v2f translation, v2f rotation, v2f scale);
m4f hf_perspective_m4f(f32 screen_width, f32 screen_height, f32 fov, f32 near_plane, f32 far_plane);
m4f hf_ortho_m4f(f32 left, f32 right, f32 bottom, f32 top, f32 near_plane, f32 far_plane);
m4f hf_view_m4f(v3f position, v3f rotation);

v3f hf_get_dir_from_rot(v3f rot);

u32 hf_hash_str(const char* str);

hf_inline f64 hf_to_radians(f64 degrees);
hf_inline f64 hf_to_degrees(f64 radians);

hf_inline f64 hf_lerp(f64 a, f64 b, f64 percentage);

#endif //HFMATH_H
