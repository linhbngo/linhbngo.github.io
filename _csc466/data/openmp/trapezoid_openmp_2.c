#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  //init parameters and evaluators
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  int N = atoi(argv[3]);
  int nthreads = atoi(argv[4]);
  double partial_sum[nthreads];
  double h = ((b - a) / nthreads);    

  omp_set_num_threads(nthreads);
  #pragma omp parallel 
  {
    int tid = omp_get_thread_num();
    /* number of trapezoids per thread */
    int partial_n = N / nthreads;
    double delta = (b - a)/N;
    double local_a = a + h * tid;
    double local_b = local_a + delta;
    for (int i = 0; i < partial_n; i++) {
      partial_sum[tid] += (local_a * local_a + local_b * local_b) * delta / 2;
      local_a = local_b;
      local_b += delta;
    }
    printf("Thread %d calculate a partial sum of %.4f from %.4f to %.4f\n", tid, partial_sum[tid], a + h*tid, local_a);
  } 
  double sum = 0;
  for (int i = 0; i < nthreads; i++) {
    sum += partial_sum[i];
  }
  printf("The integral is: %.4f\n", sum);
  return 0;
}