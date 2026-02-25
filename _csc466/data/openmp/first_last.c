#include <stdio.h>
#include <omp.h>

#define N 5

int main() {
    int i, last = -1;

    #pragma omp parallel for firstprivate(last) lastprivate(last)
    for (i = 0; i < N; i++) {
        last = i;
        printf("Thread %d: last = %d\n", omp_get_thread_num(), last);
    }

    printf("Final value of last: %d\n", last);
    return 0;
}
