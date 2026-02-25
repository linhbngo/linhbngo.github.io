#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]) {
  double x = atof(argv[1]);
  int nthreads = atoi(argv[2]);
  double terms[4];
  int i;
  
  omp_set_num_threads(nthreads);
  #pragma omp parallel sections
  {
    #pragma omp section
    {
      terms[0] = pow(x, 4);
    }
    #pragma omp section
    {
      terms[1] = 15 * pow(x, 3);
    }
    #pragma omp section
    {
      terms[2] = 10 * pow(x, 2);
    }
    #pragma omp section
    {
      terms[3] = 2 * x;
    }
  }
  double sum = 0;
  for (int i = 0; i < 4; i++) {
    sum += terms[i];
  }
  printf("The value for the polynomial is: %f\n", sum);
  return 0;
}