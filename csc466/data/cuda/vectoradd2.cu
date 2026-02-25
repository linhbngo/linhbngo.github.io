#include <stdio.h>
#include <cuda.h>
#include <cuda_runtime.h>
#include <curand_kernel.h>
#define N 64
#define T 8 // max threads per block

__global__ void add(int *a, int *b, int *c){
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if (i < N) {
    c[i] = a[i] + b[i];
  }
}

int main() {
  int a[N], b[N], c[N], i;
  int *dev_a, *dev_b, *dev_c;
  size_t size = N * sizeof(int);
  cudaMalloc((void**)&dev_c, size);
  cudaMalloc((void**)&dev_b, size);
  cudaMalloc((void**)&dev_a, size);
  for(i=0; i < N; i++) {
    a[i] = i;
    b[i] = i;
  }
  cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
  cudaMemcpy(dev_b, b, size, cudaMemcpyHostToDevice);
  add <<<(int)ceil(N/T), T>>>(dev_a, dev_b, dev_c);
  cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);

  for(i=0; i < N; i++)
    printf("%d + %d = %d\n", a[i], b[i], c[i]);
  cudaFree(dev_c);
  cudaFree(dev_b);
  cudaFree(dev_a);
  return 0;
}