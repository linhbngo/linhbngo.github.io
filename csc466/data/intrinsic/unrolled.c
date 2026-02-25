#include <stdio.h>
#include <stdlib.h>

int main() {
  int i = 0;
  float a[10] ={1,2,3,4,5,6,7,8,9,10};
  float b[10] ={0,0,0,0,0,0,0,0,0,0};

  int n = 10;
  int unroll = (n/4)*4;
  for (i = 0; i < unroll; i+=4) {
    b[i] = a[i]*2;
    b[i+1] = a[i+1]*2;
    b[i+2] = a[i+2]*2;
    b[i+3] = a[i+3]*2;
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