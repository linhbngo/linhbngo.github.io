#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <limits.h>

int main (int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int nthreads = atoi(argv[2]);
    int m = INT_MIN;

    omp_set_num_threads(nthreads);
    #pragma omp parallel reduction(max: m)
    {   
        srand(time(NULL) + omp_get_thread_num());
        int v1 = rand() % 100 + 1;
        int v2 = rand() % 100 + 1;
        int tid = omp_get_thread_num();
        printf("Thread %d processed two values: %d and %d\n",tid,v1,v2);
        if (v1 > v2) {
            m = v1;
        } else m = v2;
    }
    printf("The final max is: %d\n",m);
    return 0;
}