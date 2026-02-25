#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int nthreads = atoi(argv[2]);

    omp_set_num_threads(nthreads);
    #pragma omp parallel
    {   
        int total_sleep = 0;
        int portions = 0;
        srand(time(NULL));
        int tid = omp_get_thread_num();
        #pragma omp for schedule(static,2)
            for (int i = 0; i <  N; i++) {
                int sleep_time = rand() % 10 + 1;
                total_sleep += sleep_time;
                portions += 1;
                sleep(sleep_time);
            }
        printf("Thread %d processed %d portions during %d seconds\n",tid,portions,total_sleep);
    }
      
    return 0;
}