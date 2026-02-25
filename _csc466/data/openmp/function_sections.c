#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main (int argc, char *argv[]) {
  double x = atof(argv[1]);
  int nthreads = atoi(argv[2]);
  double y = 0.0;
  int i;
  
  omp_set_num_threads(nthreads);
  #pragma omp parallel sections reduction(+:y)
  {
    #pragma omp section
    {
      y += pow(x, 4);
    }
    #pragma omp section
    {
      y += 15 * pow(x, 3);
    }
    #pragma omp section
    {
      y += 10 * pow(x, 2);
    }
    #pragma omp section
    {
      y += 2 * x;
    }
  }
  
  printf("The value for the polynomial is: %f\n", y);
  return 0;
}