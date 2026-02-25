#include <stdio.h>
#include <stdlib.h>
#include "mpi.h"

int main(int argc, char *argv[]) {
  int rank, size;
  int swap[3];
  int final_swap[3];
  MPI_Status status;
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
    swap[0] = 5;
    swap[1] = 1; 
    swap[2] = 2;
    MPI_Alltoall(swap, 1, MPI_INT, final_swap, 1, MPI_INT, MPI_COMM_WORLD);  
    MPI_Bcast(final_swap + 2, 1, MPI_INT, 0, MPI_COMM_WORLD);  
    MPI_Send(final_swap + 2, 1, MPI_INT, 2, 43, MPI_COMM_WORLD);
    MPI_Recv(final_swap, 1, MPI_INT, 1, 43, MPI_COMM_WORLD, &status);
    MPI_Reduce(final_swap + 1, final_swap + 2, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
  }

  if (rank == 1) {
    swap[0] = 3;
    swap[1] = 4;
    swap[2] = 5;
    MPI_Alltoall(swap, 1, MPI_INT, final_swap, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Bcast(final_swap + 2, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Send(final_swap + 2, 1, MPI_INT, 0, 43, MPI_COMM_WORLD);
    MPI_Reduce(final_swap + 1, final_swap + 2, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);  
  }

  if (rank == 2) {
    swap[0] = 6;
    swap[1] = 7;
    swap[2] = 8;
    MPI_Alltoall(swap, 1, MPI_INT, final_swap, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Bcast(final_swap + 2, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Recv(final_swap, 1, MPI_INT, 0, 43, MPI_COMM_WORLD, &status);
    MPI_Reduce(final_swap + 1, final_swap + 2, 1, MPI_INT, MPI_SUM, 1, MPI_COMM_WORLD);
  }

  for (int i = 0; i < size; i++) {
    printf ("For rank %d, final swap at %d is %d \n", rank, i, final_swap[i]);
  }

  MPI_Finalize();

  return 0;
}
