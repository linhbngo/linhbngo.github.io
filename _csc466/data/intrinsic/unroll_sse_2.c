#include <immintrin.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int i = 0, j = 0;
  float a[10] ={1,2,3,4,5,6,7,8,9,10};
  float b[10] ={0,0,0,0,0,0,0,0,0,0};

  int n = 10;
  int unroll = (n/4)*4;
  for (i = 0; i < unroll; i+=4) {
    __m128 ai_v = _mm_loadu_ps(&a[i]);
    __m128 two_v = _mm_set1_ps(2);
    __m128 ai2_v = _mm_mul_ps(ai_v,two_v);
    _mm_storeu_ps(&b[i],ai2_v);

    printf("%d \n", j);
    for (j = 0; j < unroll; j++) {
      printf("%2.0f\t", b[j]);
    }
    printf("\n");
  }

  for (; i<n; i++) {
    b[i] = a[i]*2;
  }

  for (i = 0; i < 10; i++)
    printf("%2.0f\t", a[i]);
  printf("\n");
  for (i = 0; i < 10; i++)
    printf("%2.0f\t", b[i]);
  printf("\n");

  return 0;
}