#include "types.h" 

typedef struct { 
  float x; 
  float y; 
} vec2f; 

typedef struct { 
  u32 rows, cols; 
  f32* data; 
} mat; 

mat* mat_create(u32 rows, u32 cols);
void mat_free(mat *mat);

b32 mat_copy(mat* src, mat* dst); 
void mat_clear(mat* mat); 
void mat_fill(mat* mat, f32 x); 
void mat_scale(mat* mat, f32 x); 
f32 mat_sum(mat* mat); 

b32 mat_add(mat* out, const mat* a, const mat* b); 
b32 mat_sub(mat* out, const mat* a, const mat* b); 
b32 mat_mult(mat* out, const mat* a, const mat* b, b32 zero_out, b32 tranpose_a, b32 transpose_b);
f32 mat_eigen(const mat* mat);
b32 mat_transpose(mat* out, const mat* mat);
b32 mat_inverse(mat* out, const mat* mat); 

void _print_mat(mat* mat); 
// theta = degree 
f32 vec_dot_(const vec2f* a, const vec2f* b, f32 theta);

// b32 vec_cross(vec2f* out, const vec2f* a, const vec2f* b); 


