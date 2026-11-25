#include <stdio.h> 
#include <stdint.h> 
#include "include/linalg.h" 


void _test_mat_mult(); 

void _test_mat_transpose(mat *out, mat *mat){ 
  mat_transpose(out, mat);  
} 

void _test_mat_exists(mat *mat){ 
  _print_mat(mat);
} 

void _input_mat(mat *mat){ 
  for (u32 i = 0; i < mat->rows; ++i){ 
    for (u32 j = 0; j < mat->cols; ++j){ 
      mat->data[j + i * mat->cols] = i * j * 2; 
    }
  } 
} 

int main() { 
  printf("Hello\n");
  u32 rows = 4; 
  u32 cols = 5; 
  mat* test_mat = mat_create(rows, cols); 

  // _test_mat_exists(test_mat);
  _input_mat(test_mat);  
  _test_mat_exists(test_mat);

  mat *test_mat_2 = mat_create(cols, rows); 
  //
  _test_mat_transpose(test_mat_2, test_mat); 
  //
  _test_mat_exists(test_mat_2); 
  //
  mat_free(test_mat); 
  mat_free(test_mat_2); 

  return 0; 
} 
