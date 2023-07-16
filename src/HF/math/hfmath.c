#include "hfmath.h"
//#include "hfpch.h"

const f64 hf_PI = 3.14159265;


hf_inline f32 hf_f_sqrt(f32 in){
    i64 i;
    f32 x2, y;
    const f32 threeHalfs = 1.5f;
    
    //we are doing the inverse of inverse and its fast
    f32 inverseIn = 1 / in;
    
    x2 = inverseIn * 0.5f;
    y = inverseIn;
    
    i = *(i64*)&y; // convert memory address to long for bit shifting
    i = 0x5f375a86 - (i >> 1); // shift exponent right to divide by two and negate that (y^(-1/2)), also what the fuck?
    y = *(f32*)(&i); //convert memory address back to float for output
    y = y * (threeHalfs - (x2 * y * y)); // newton iteration, 1 is fine because we are close enough to answer, btw what the fuck is this
    //second iteration to make it more accurate
    y = y * (threeHalfs - (x2 * y * y)); // newton iteration, 2 is fine because we are close enough to answer, btw what the fuck is this
    
    
    //i literally have no idea why it returns a negative
    return fabs(y);
}

hf_inline f32 hf_f_isqrt(f32 in){
    i64 i;
    f32 x2, y;
    const f32 threeHalfs = 1.5f;
    
    x2 = in * 0.5f;
    y = in;
    
    i = *(i64*)&y; // convert memory address to long for bit shifting
    i = 0x5f375a86 - (i >> 1); // shift exponent right to divide by two and negate that (y^(-1/2)), also what the fuck?
    y = *(f32*)&i; //convert memory address back to float for output
    y = y * (threeHalfs - (x2 * y * y)); // newton iteration, 1 is fine because we are close enough to answer, btw what the fuck is this
    
    return y;
}




hf_inline f32 hf_length_v2f(v2f vec){
    return hf_f_sqrt(vec.x * vec.x + vec.y * vec.y);
}

hf_inline f32 hf_length_v3f(v3f vec){
    return hf_f_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

hf_inline f32 hf_length_v4f(v4f vec){
    return hf_f_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}






hf_inline f32 hf_ilength_v2f(v2f vec){
    return hf_f_isqrt(vec.x * vec.x + vec.y * vec.y);
}

hf_inline f32 hf_ilength_v3f(v3f vec){
    return hf_f_isqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

hf_inline f32 hf_ilength_v4f(v4f vec){
    return hf_f_isqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}






hf_inline v2f hf_normalize_v2f(v2f vec){
    f32 i_length = hf_ilength_v2f(vec);
    vec.x *= i_length;
    vec.y *= i_length;
    
    return vec;
}

hf_inline v3f hf_normalize_v3f(v3f vec){
    f32 i_length = hf_ilength_v3f(vec);
    vec.x *= i_length;
    vec.y *= i_length;
    vec.z *= i_length;
    
    return vec;
}

hf_inline v4f hf_normalize_v4f(v4f vec){
    f32 i_length = hf_ilength_v4f(vec);
    vec.x *= i_length;
    vec.y *= i_length;
    vec.z *= i_length;
    vec.w *= i_length;
    
    return vec;
}



//-----------------------------v2f------------------------

hf_inline v2f hf_v2f(f32 x, f32 y){
    v2f out;
    
    out.x = x;
    out.y = y;
    
    return out;
}

hf_inline v2f hf_add_v2f(v2f a, v2f b){
    v2f out;
    
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    
    return out;
}

hf_inline v2f hf_sub_v2f(v2f a, v2f b){
    v2f out;
    
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    
    return out;
}

hf_inline v2f hf_mul_v2f(v2f a, v2f b){
    v2f out;
    
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    
    return out;
}

hf_inline v2f hf_div_v2f(v2f a, v2f b){
    v2f out;
    
    out.x = a.x / b.x;
    out.y = a.y / b.y;
    
    return out;
}





hf_inline v2f hf_add_v2f_f(v2f a, f32 b){
    v2f out;
    
    out.x = a.x + b;
    out.y = a.y + b;
    
    return out;
}

hf_inline v2f hf_sub_v2f_f(v2f a, f32 b){
    v2f out;
    
    out.x = a.x - b;
    out.y = a.y - b;
    
    return out;
}

hf_inline v2f hf_mul_v2f_f(v2f a, f32 b){
    v2f out;
    
    out.x = a.x * b;
    out.y = a.y * b;
    
    return out;
}

hf_inline v2f hf_div_v2f_f(v2f a, f32 b){
    v2f out;
    
    out.x = a.x / b;
    out.y = a.y / b;
    
    return out;
}






//-----------------------------v3f------------------------

hf_inline v3f hf_v3f(f32 x, f32 y, f32 z){
    v3f out;
    
    out.x = x;
    out.y = y;
    out.z = z;
    
    return out;
}

hf_inline v3f hf_add_v3f(v3f a, v3f b){
    v3f out;
    
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    
    return out;
}

hf_inline v3f hf_sub_v3f(v3f a, v3f b){
    v3f out;
    
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    
    return out;
}

hf_inline v3f hf_mul_v3f(v3f a, v3f b){
    v3f out;
    
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    out.z = a.z * b.z;
    
    return out;
}

hf_inline v3f hf_div_v3f(v3f a, v3f b){
    v3f out;
    
    out.x = a.x / b.x;
    out.y = a.y / b.y;
    out.z = a.z / b.z;
    
    return out;
}




hf_inline v3f hf_add_v3f_f(v3f a, f32 b){
    v3f out;
    
    out.x = a.x + b;
    out.y = a.y + b;
    out.z = a.z + b;
    
    return out;
}

hf_inline v3f hf_sub_v3f_f(v3f a, f32 b){
    v3f out;
    
    out.x = a.x - b;
    out.y = a.y - b;
    out.z = a.z - b;
    
    return out;
}

hf_inline v3f hf_mul_v3f_f(v3f a, f32 b){
    v3f out;
    
    out.x = a.x * b;
    out.y = a.y * b;
    out.z = a.z * b;
    
    return out;
}

hf_inline v3f hf_div_v3f_f(v3f a, f32 b){
    v3f out;
    
    out.x = a.x / b;
    out.y = a.y / b;
    out.z = a.z / b;
    
    return out;
}






//-----------------------------v4f------------------------

hf_inline v4f hf_v4f(f32 x, f32 y, f32 z, f32 w){
    v4f out;
    
    out.x = x;
    out.y = y;
    out.z = z;
    out.w = w;
    
    return out;
}

hf_inline v4f hf_add_v4f(v4f a, v4f b){
    v4f out;
    
    out.x = a.x + b.x;
    out.y = a.y + b.y;
    out.z = a.z + b.z;
    out.w = a.w + b.w;
    
    return out;
}

hf_inline v4f hf_sub_v4f(v4f a, v4f b){
    v4f out;
    
    out.x = a.x - b.x;
    out.y = a.y - b.y;
    out.z = a.z - b.z;
    out.w = a.w - b.w;
    
    return out;
}

hf_inline v4f hf_mul_v4f(v4f a, v4f b){
    v4f out;
    
    out.x = a.x * b.x;
    out.y = a.y * b.y;
    out.z = a.z * b.z;
    out.w = a.w * b.w;
    
    return out;
}

hf_inline v4f hf_div_v4f(v4f a, v4f b){
    v4f out;
    
    out.x = a.x / b.x;
    out.y = a.y / b.y;
    out.z = a.z / b.z;
    out.w = a.w / b.w;
    
    return out;
}




hf_inline v4f hf_add_v4f_f(v4f a, f32 b){
    v4f out;
    
    out.x = a.x + b;
    out.y = a.y + b;
    out.z = a.z + b;
    out.w = a.w + b;
    
    return out;
}

hf_inline v4f hf_sub_v4f_f(v4f a, f32 b){
    v4f out;
    
    out.x = a.x - b;
    out.y = a.y - b;
    out.z = a.z - b;
    out.w = a.w - b;
    
    return out;
}

hf_inline v4f hf_mul_v4f_f(v4f a, f32 b){
    v4f out;
    
    out.x = a.x * b;
    out.y = a.y * b;
    out.z = a.z * b;
    out.w = a.w * b;
    
    return out;
}

hf_inline v4f hf_div_v4f_f(v4f a, f32 b){
    v4f out;
    
    out.x = a.x / b;
    out.y = a.y / b;
    out.z = a.z / b;
    out.w = a.w / b;
    
    return out;
}





//-----------------------------m4f------------------------

hf_inline void hf_identity_m4f(m4f* src){
    src->m00 = 1.0f;
    src->m01 = 0.0f;
    src->m02 = 0.0f;
    src->m03 = 0.0f;
    src->m10 = 0.0f;
    src->m11 = 1.0f;
    src->m12 = 0.0f;
    src->m13 = 0.0f;
    src->m20 = 0.0f;
    src->m21 = 0.0f;
    src->m22 = 1.0f;
    src->m23 = 0.0f;
    src->m30 = 0.0f;
    src->m31 = 0.0f;
    src->m32 = 0.0f;
    src->m33 = 1.0f;
}

hf_inline void hf_transpose_m4f(m4f* dest, m4f* src){
    dest->m00 = src->m00;
    dest->m01 = src->m10;
    dest->m02 = src->m20;
    dest->m03 = src->m30;
    dest->m10 = src->m01;
    dest->m11 = src->m11;
    dest->m12 = src->m21;
    dest->m13 = src->m31;
    dest->m20 = src->m02;
    dest->m21 = src->m12;
    dest->m22 = src->m22;
    dest->m23 = src->m32;
    dest->m30 = src->m03;
    dest->m31 = src->m13;
    dest->m32 = src->m23;
    dest->m33 = src->m33;
}

hf_inline void hf_transpose_no_rotation_m4f(m4f* dest, m4f* src){
    dest->m00 = src->m00;
    dest->m01 = src->m10;
    dest->m02 = src->m20;
    dest->m10 = src->m01;
    dest->m11 = src->m11;
    dest->m12 = src->m21;
    dest->m20 = src->m02;
    dest->m21 = src->m12;
    dest->m22 = src->m22;
}

hf_inline void hf_scale_m4f(m4f* matrix, v3f vec){
    matrix->m00 *= vec.x;
    matrix->m01 *= vec.x;
    matrix->m02 *= vec.x;
    matrix->m03 *= vec.x;
    matrix->m10 *= vec.y;
    matrix->m11 *= vec.y;
    matrix->m12 *= vec.y;
    matrix->m13 *= vec.y;
    matrix->m20 *= vec.z;
    matrix->m21 *= vec.z;
    matrix->m22 *= vec.z;
    matrix->m23 *= vec.z;
}

hf_inline m4f hf_mul_m4f(m4f a, m4f b){
    m4f mat = {};
    
    mat.m00 = a.m00 * b.m00 + a.m10 * b.m01 + a.m20 * b.m02 + a.m30 * b.m03;
    mat.m01 = a.m01 * b.m00 + a.m11 * b.m01 + a.m21 * b.m02 + a.m31 * b.m03;
    mat.m02 = a.m02 * b.m00 + a.m12 * b.m01 + a.m22 * b.m02 + a.m32 * b.m03;
    mat.m03 = a.m03 * b.m00 + a.m13 * b.m01 + a.m23 * b.m02 + a.m33 * b.m03;
    mat.m10 = a.m00 * b.m10 + a.m10 * b.m11 + a.m20 * b.m12 + a.m30 * b.m13;
    mat.m11 = a.m01 * b.m10 + a.m11 * b.m11 + a.m21 * b.m12 + a.m31 * b.m13;
    mat.m12 = a.m02 * b.m10 + a.m12 * b.m11 + a.m22 * b.m12 + a.m32 * b.m13;
    mat.m13 = a.m03 * b.m10 + a.m13 * b.m11 + a.m23 * b.m12 + a.m33 * b.m13;
    mat.m20 = a.m00 * b.m20 + a.m10 * b.m21 + a.m20 * b.m22 + a.m30 * b.m23;
    mat.m21 = a.m01 * b.m20 + a.m11 * b.m21 + a.m21 * b.m22 + a.m31 * b.m23;
    mat.m22 = a.m02 * b.m20 + a.m12 * b.m21 + a.m22 * b.m22 + a.m32 * b.m23;
    mat.m23 = a.m03 * b.m20 + a.m13 * b.m21 + a.m23 * b.m22 + a.m33 * b.m23;
    mat.m30 = a.m00 * b.m30 + a.m10 * b.m31 + a.m20 * b.m32 + a.m30 * b.m33;
    mat.m31 = a.m01 * b.m30 + a.m11 * b.m31 + a.m21 * b.m32 + a.m31 * b.m33;
    mat.m32 = a.m02 * b.m30 + a.m12 * b.m31 + a.m22 * b.m32 + a.m32 * b.m33;
    mat.m33 = a.m03 * b.m30 + a.m13 * b.m31 + a.m23 * b.m32 + a.m33 * b.m33;
    
    return mat;
}

/* 
hf_inline void hf_scale_m4f_v2f(m4f* matrix, v2f vec){
    matrix->m00 *= vec.x;
    matrix->m01 *= vec.x;
    matrix->m02 *= vec.x;
    matrix->m03 *= vec.x;
    matrix->m10 *= vec.y;
    matrix->m11 *= vec.y;
    matrix->m12 *= vec.y;
    matrix->m13 *= vec.y;
}
 */

void hf_rotate_m4f(m4f* matrix, f32 angle, v3f axis){
    f32 c = (f32)cos(angle);
    f32 s = (f32)sin(angle);
    f32 oneminusc = 1.0f - c;
    f32 xy = axis.x * axis.y;
    f32 yz = axis.y * axis.z;
    f32 xz = axis.x * axis.z;
    f32 xs = axis.x * s;
    f32 ys = axis.y * s;
    f32 zs = axis.z * s;
    
    f32 f00 = axis.x * axis.x * oneminusc + c;
    f32 f01 = xy * oneminusc + zs;
    f32 f02 = xz * oneminusc - ys;
    // n[3] not used
    f32 f10 = xy * oneminusc - zs;
    f32 f11 = axis.y * axis.y * oneminusc + c;
    f32 f12 = yz * oneminusc + xs;
    // n[7] not used
    f32 f20 = xz * oneminusc + ys;
    f32 f21 = yz * oneminusc - xs;
    f32 f22 = axis.z * axis.z * oneminusc + c;
    
    f32 t00 = matrix->m00 * f00 + matrix->m10 * f01 + matrix->m20 * f02;
    f32 t01 = matrix->m01 * f00 + matrix->m11 * f01 + matrix->m21 * f02;
    f32 t02 = matrix->m02 * f00 + matrix->m12 * f01 + matrix->m22 * f02;
    f32 t03 = matrix->m03 * f00 + matrix->m13 * f01 + matrix->m23 * f02;
    f32 t10 = matrix->m00 * f10 + matrix->m10 * f11 + matrix->m20 * f12;
    f32 t11 = matrix->m01 * f10 + matrix->m11 * f11 + matrix->m21 * f12;
    f32 t12 = matrix->m02 * f10 + matrix->m12 * f11 + matrix->m22 * f12;
    f32 t13 = matrix->m03 * f10 + matrix->m13 * f11 + matrix->m23 * f12;
    matrix->m20 = matrix->m00 * f20 + matrix->m10 * f21 + matrix->m20 * f22;
    matrix->m21 = matrix->m01 * f20 + matrix->m11 * f21 + matrix->m21 * f22;
    matrix->m22 = matrix->m02 * f20 + matrix->m12 * f21 + matrix->m22 * f22;
    matrix->m23 = matrix->m03 * f20 + matrix->m13 * f21 + matrix->m23 * f22;
    matrix->m00 = t00;
    matrix->m01 = t01;
    matrix->m02 = t02;
    matrix->m03 = t03;
    matrix->m10 = t10;
    matrix->m11 = t11;
    matrix->m12 = t12;
    matrix->m13 = t13;
}

hf_inline void hf_translate_m4f(m4f* matrix, v3f vec){
    matrix->m30 += matrix->m00 * vec.x + matrix->m10 * vec.y + matrix->m20 * vec.z;
    matrix->m31 += matrix->m01 * vec.x + matrix->m11 * vec.y + matrix->m21 * vec.z;
    matrix->m32 += matrix->m02 * vec.x + matrix->m12 * vec.y + matrix->m22 * vec.z;
    matrix->m33 += matrix->m03 * vec.x + matrix->m13 * vec.y + matrix->m23 * vec.z;
}

/* 
hf_inline void hf_translate_m4f_v2f(m4f* matrix, v2f vec){
    matrix->m30 += matrix->m00 * vec.x + matrix->m10 * vec.y;
    matrix->m31 += matrix->m01 * vec.x + matrix->m11 * vec.y;
    matrix->m32 += matrix->m02 * vec.x + matrix->m12 * vec.y;
    matrix->m33 += matrix->m03 * vec.x + matrix->m13 * vec.y;
}
 */

m4f hf_transformation_m4f(v3f translation, v3f rotation, v3f scale){
    m4f out = {};
    hf_identity_m4f(&out);
    hf_translate_m4f(&out, translation);
    hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.x), hf_v3f(1, 0, 0));
    hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.y), hf_v3f(0, 1, 0));
    hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.z), hf_v3f(0, 0, 1));
    hf_scale_m4f(&out, scale);
    
    return out;
}

m4f hf_transformation_m4f_2d(v2f translation, f32 rotation, v2f scale){
    m4f out = {};
    hf_identity_m4f(&out);
    hf_translate_m4f(&out, hf_v3f(translation.x, translation.y, 0));
    //hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.x), hf_v3f(1, 0, 0));
    //hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.y), hf_v3f(0, 1, 0));
    hf_rotate_m4f(&out, (f32)hf_to_radians(rotation), hf_v3f(0, 0, 1));
    hf_scale_m4f(&out, hf_v3f(scale.x, scale.y, 1));
    
    return out;
}

m4f hf_perspective_m4f(f32 screen_width, f32 screen_height, f32 fov, f32 near_plane, f32 far_plane){
    m4f out = {};
    f32 aspectRatio = screen_width / screen_height;
    f32 y_scale = (f32)((1 / tan(hf_to_radians(fov / 2))));
    f32 x_scale = y_scale / aspectRatio;
    f32 frustum_length = far_plane - near_plane;
    
    out.m00 = x_scale;
    out.m11 = y_scale;
    out.m22 = -((far_plane + near_plane) / frustum_length);
    out.m23 = -1;
    out.m32 = -((2 * near_plane * far_plane) / frustum_length);
    out.m33 = 0;
    return out;
}

m4f hf_ortho_m4f(f32 left, f32 right, f32 bottom, f32 top, f32 near_plane, f32 far_plane){
    m4f out = {};
    hf_identity_m4f(&out);
    out.m00 = 2 / (right - left);
    out.m11 = 2 / (top - bottom);
    out.m22 = -2 / (far_plane - near_plane);
    out.m30 = -(right + left) / (right - left);
    out.m31 = -(top + bottom) / (top - bottom);
    out.m32 = -(far_plane + near_plane) / (far_plane - near_plane);
    return out;
}

m4f hf_view_m4f(v3f position, v3f rotation){
    m4f out = {};
    hf_identity_m4f(&out);
    hf_rotate_m4f(&out, (f32)hf_to_radians(-rotation.x), hf_v3f(1, 0, 0));
    hf_rotate_m4f(&out, (f32)hf_to_radians(-rotation.y), hf_v3f(0, 1, 0));
    hf_rotate_m4f(&out, (f32)hf_to_radians(rotation.z), hf_v3f(0, 0, 1));
    hf_translate_m4f(&out, hf_v3f(-position.x, -position.y, -position.z));
    return out;
}

v3f hf_get_dir_from_rot(v3f rot){
    v3f vec = hf_v3f(sin((f32)hf_to_radians(rot.y)), tan((f32)hf_to_radians(rot.x)), cos((f32)hf_to_radians(rot.y)));
    vec = hf_normalize_v3f(vec);
    return vec;
}








// NOTE(salmoncatt): djb2 hash algorithm: http://www.cse.yorku.ca/~oz/hash.html
u32 hf_hash_str(const char* str){
    u32 out = 5381;
    i32 c;
    
    while ((c = *str++))
        out= ((out << 5) + out) + c;
    return out;
}


hf_inline f64 hf_to_radians(f64 degrees){
    return degrees * hf_PI / 180;
}

hf_inline f64 hf_to_degrees(f64 radians){
    return radians * 180 / hf_PI;
}

hf_inline f64 hf_lerp(f64 a, f64 b, f64 percentage){
    return a + percentage * (b - a);
}




hf_inline b8 hf_2d_aabb_intersect(u32 a_x, u32 a_y, u32 a_w, u32 a_h, u32 b_x, u32 b_y, u32 b_w, u32 b_h){
    return (a_x <= (b_x + b_w) && (a_x + a_w) >= b_x) && (a_y <= (b_y + b_h) && (a_y + a_h) >= b_y);
}