#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]) {
  int N = atoi(argv[1]);
  int nthreads = atoi(argv[2]);
  int sum;
  clock_t start, end;

  omp_set_num_threads(nthreads);
  start = clock();

  #pragma omp declare reduction( \
    sumop : int : omp_out = omp_out + omp_in) \
    initializer (omp_priv = 0)

  #pragma omp parallel 
  {
    #pragma omp for reduction(sumop:sum)
    for (int i = 0; i <  N; i++) {
      sum += i;
    }
  }
  end = clock();

  printf("The sum is: %d\n", sum);
  printf("The run time is: %.4f\n", ((double) (end - start)) / CLOCKS_PER_SEC);
  return 0;
}