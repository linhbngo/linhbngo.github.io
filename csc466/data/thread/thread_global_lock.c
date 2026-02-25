#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct arg_data {
  int tid;
  int start;
  int end;
  int* arr;
};

long sum;
pthread_mutex_t lock;

void* partial_sum(void* arg) {
  struct arg_data* k = (struct arg_data *) arg;
  printf("Current thread no is : %d and calculate sum of index range %d to %d\n", k->tid, k->start, k->end - 1);
  for (int i = k->start; i < k->end; i++) {
    pthread_mutex_lock(&lock);
    sum += k->arr[i];
    pthread_mutex_unlock(&lock);
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  int n = atoi(argv[1]);
  int t = atoi(argv[2]);
  int i = 0, tid = 0; sum = 0;
  clock_t start, end;
  double cpu_time;

  int *arr = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    arr[i] = i + 1;
  }

  pthread_t* id = malloc(sizeof(pthread_t) * t);
  start = clock();
  for (tid = 0; tid < t; tid++) {
    struct arg_data *k = malloc(sizeof(struct arg_data));
    k->tid = tid;
    k->start = tid * (n / t);
    k->end = k->start + (n / t);
    k->arr = arr;
    pthread_create(&id[tid], NULL, partial_sum, k);
  }

  for (tid = 0; tid < t; tid++)
    pthread_join(id[tid], NULL);

  end = clock();
  cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Total sum: %ld\n", sum);
  printf("Time taken to sum all the numbers are %lf\n", cpu_time);

  return 0;
}