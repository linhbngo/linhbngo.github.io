#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int nthreads = atoi(argv[2]);

    omp_set_num_threads(nthreads);
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        #pragma omp for collapse(2)
            for (int i = 0; i <  N; i++) {
                for (int j = 0; j < N; j++) {
                    printf("Thread %d is processing outer loop %d and inner loop %d\n",tid,i,j);
                }
            }
    }
      
    return 0;
}