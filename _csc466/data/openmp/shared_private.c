#include <stdio.h>
#include <omp.h>

#define N 8

int main() {
    int i, j;
    int a[N];

    for (i = 0; i < N; i++) 
        a[i] = 0;

    #pragma omp parallel for shared(a) private(j)
    for (i = 0; i < N; i++) {
        int thread_id = omp_get_thread_num();
        a[i] = thread_id; // Each element gets assigned the thread ID
        j ++;
        printf("Thread %d processing a[%d] at %d times\n", thread_id, i, j);
    }

    printf("Final array values: ");
    for (i = 0; i < N; i++)
        printf("%d ", a[i]);
    
    printf("\n");
    return 0;
}
