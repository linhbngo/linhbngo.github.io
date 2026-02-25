#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int sum(int N, int nthreads, int tid) {
  int count = N / nthreads;  
  int start = count * tid + 1;
  int p_sum = 0;
  for (int i = start; i < start + count; i++) {
    p_sum += i;
  }
  return p_sum;
}

int main (int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int nthreads = atoi(argv[2]);
  int partial_sum[nthreads];
   
  omp_set_num_threads(nthreads);
  #pragma omp parallel 
  {
    int tid = omp_get_thread_num();
    partial_sum[tid] = sum(N, nthreads, tid) ;
  } 
  int sum = 0;
  for (int i = 0; i < nthreads; i++) {
    sum += partial_sum[i];
  }
  printf("The sum of series is: %.4f\n", sum);
  return 0;
}