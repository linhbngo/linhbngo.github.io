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
        #pragma omp for schedule(dynamic,2)
            for (int i = 0; i <  N; i++) {
                printf("Thread %d is processing number %d\n",tid,i);
            }
    }
      
    return 0;
}