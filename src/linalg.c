#include "../include/linalg.h"
#include <math.h>
#include <stdio.h>

#define PI 3.141592653589793

mat *mat_create(u32 rows, u32 cols) {
  printf("hello\n");
  mat *out = malloc((u32)rows * (u32)cols * sizeof(mat));

  out->rows = rows;
  out->cols = cols;
  out->data = malloc((size_t)rows * cols * sizeof(*out->data));

  return out;
}

void mat_free(mat *mat) {
  if (mat != NULL) {
    free(mat->data);
    free(mat);
  }
}

b32 mat_copy(mat *src, mat *dst) {
  if (dst->rows != src->rows || dst->cols != src->cols) {
    return false;
  }

  memcpy(dst->data, src->data, sizeof(f32) * (u32)dst->rows * (u32)dst->cols);

  return true;
}

void clear(mat *mat) {
  memset(mat->data, 0, sizeof(f32) * (u32)mat->rows * (u32)mat->cols);
}

void mat_fill(mat *mat, f32 x) {
  printf("debug\n");
  u32 size = (u32)mat->rows * mat->cols;
  for (u32 i = 0; i < size; ++i) {
    // printf("%d\n", i);
    mat->data[i] = x;
  }
}

void mat_scale(mat *mat, f32 x) {
  u32 size = (u32)mat->cols * mat->rows;

  for (u32 i = 0; i < size; ++i) {
    mat->data[i] *= x;
  }
}

u32 mat_sum(mat *mat) {
  u32 sum = 0;

  u32 size = (u32)mat->cols * mat->rows;
  for (u32 i = 0; i < size; ++i) {
    sum += mat->data[i];
  }

  return sum;
}

b32 mat_add(mat *out, const mat *a, const mat *b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    return false;
  }

  if (a->rows != out->rows || a->cols != out->cols) {
    return false;
  }

  u32 size = (u64)out->rows * out->cols;
  for (u32 i = 0; i < size; ++i) {
    out->data[i] = a->data[i] + b->data[i];
  }

  return true;
}

b32 mat_sub(mat *out, const mat *a, const mat *b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    return false;
  }

  if (a->rows != out->rows || a->cols != out->cols) {
    return false;
  }

  u32 size = (u32)out->rows * out->cols;
  for (u32 i = 0; i < size; ++i) {
    out->data[i] = a->data[i] - b->data[i];
  }

  return true;
}

b32 _mat_mult_nn(mat *out, const mat *a, const mat *b) {
  for (u32 i = 0; i < out->rows; ++i) {
    for (u32 j = 0; j < out->cols; ++i) {
      for (u32 k = 0; k < a->cols; ++i) {
        out->data[j + i * out->cols] +=
            a->data[k + i * a->cols] * b->data[j + k * b->cols];
      }
    }
  }

  return true;
}
b32 _mat_mult_tn(mat *out, const mat *a, const mat *b) {
  for (u32 i = 0; i < out->rows; ++i) {
    for (u32 j = 0; j < out->cols; ++i) {
      for (u32 k = 0; k < a->cols; ++i) {

        out->data[j + i * out->cols] +=
            a->data[i + k * a->cols] * b->data[j + k * b->cols];
      }
    }
  }

  return true;
}
b32 _mat_mult_nt(mat *out, const mat *a, const mat *b) {
  for (u32 i = 0; i < out->rows; ++i) {
    for (u32 j = 0; j < out->cols; ++i) {
      for (u32 k = 0; k < a->cols; ++i) {
        out->data[j + i * out->cols] +=
            a->data[k + i * a->cols] * b->data[k + j * b->cols];
      }
    }
  }

  return true;
}

b32 _mat_mult_tt(mat *out, const mat *a, const mat *b) {
  for (u32 i = 0; i < out->rows; ++i) {
    for (u32 j = 0; j < out->cols; ++i) {
      for (u32 k = 0; k < a->cols; ++i) {
        out->data[j + i * out->cols] +=
            a->data[i + k * a->cols] * b->data[k + j * b->cols];
      }
    }
  }

  return true;
}

b32 mat_mult(mat *out, const mat *a, const mat *b, b32 zero_out, b32 tranpose_a,
             b32 transpose_b) {
  if (a->rows != b->rows || a->cols != b->cols) {
    return false;
  }

  if (a->rows != out->rows || a->cols != out->cols) {
    return false;
  }

  u32 a_rows = tranpose_a ? a->cols : a->rows;
  u32 a_cols = tranpose_a ? a->rows : a->cols;
  u32 b_rows = transpose_b ? b->cols : b->rows;
  u32 b_cols = transpose_b ? b->cols : b->rows;

  b32 transpose = (tranpose_a << 1) | transpose_b;

  switch (transpose) {
  case 0b00: {
    _mat_mult_nn(out, a, b);
  } break;
  case 0b01: {
    _mat_mult_tn(out, a, b);
  } break;
  case 0b10: {
    _mat_mult_nt(out, a, b);
  } break;
  case 0b11: {
    _mat_mult_tt(out, a, b);
  } break;
  }

  return true;
}

b32 mat_transpose(mat *out, const mat *mat) {
  if (out->rows != mat->cols || out->cols != mat->rows) {
    return false;
  }
  puts("debug transpose\n");
  for (u32 i = 0; i < mat->rows; ++i) {
    for (u32 j = 0; j < mat->cols; ++j) {
      out->data[i + j * out->cols] = 
        mat->data[i * mat->cols + j];
    }
  }

  return true;
}

void _print_mat(mat *mat) {
  for (u32 i = 0; i < mat->rows; ++i) {
    for (u32 j = 0; j < mat->cols; ++j) {
      printf("[%f] ", mat->data[j + i * mat->cols]);
    }
    printf("\n");
  }
}

f32 cos_theta_(f32 theta) {
  double radians = theta * (PI / 180.0);
  return cos(radians);
}

f32 sin_theta_(f32 theta) {
  double radians = theta * (PI / 180.0);
  return sin(radians);
}

f32 vec_norm_(const vec2f *a) { return sqrt(pow(a->x, 2) + pow(a->y, 2)); }

f32 vec_dot_(const vec2f *a, const vec2f *b, f32 theta) {
  f32 result = vec_norm_(a) * vec_norm_(b) * cos_theta_(theta);

  return result;
}
