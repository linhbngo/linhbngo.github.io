#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int nthreads = atoi(argv[1]);

  omp_set_num_threads(nthreads);
  #pragma omp parallel
  {
    int tid = omp_get_thread_num();  
    printf("Starting the hello program ...\n");
    #pragma omp sections
    {
      #pragma omp section
      {
        printf("Thread %d is doing work in section A \n", tid);
      }
      #pragma omp section
      {
        printf("Thread %d is doing work in section B \n", tid);
      }
      #pragma omp section
      {
        printf("Thread %d is doing work in section C \n", tid);
      }
    }
  }    
  return 0;
}