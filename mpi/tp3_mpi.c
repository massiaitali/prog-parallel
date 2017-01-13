#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mpi.h"


// Retrieve Time
long ms_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);

  return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void displayMatrix(unsigned long M, unsigned long N, unsigned long* matrix)
{
  int m, n;

  for (m=0; m<M; m++) {
    for (n=0; n<N; n++) {
      printf("%ld ", matrix[m * N + n]);
    }

    printf("\n"); 
  }
}


int main(int argc, char* argv[])
{
  if (argc == 3) {
    unsigned long M = strtol(argv[1], NULL, 10);
    unsigned long N = strtol(argv[2], NULL, 10);
    unsigned long matrix[M][N];
    unsigned long vector[N];
    unsigned long result_local[M];
    unsigned long result[M];
    int m, n;

    // MPI Init
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Initialize Matrix & Vector
    unsigned long eltProc = M / size;

    if (rank == 0) {
      for (n=0; n<N; n++) {
        for (m=0; m<M; m++) {
          matrix[m][n] = (m+1) * (n+1);

          if (result[m] != 0) {
            result_local[m] = 0;
            result[m] = 0;
          }
        }

        vector[n] = n + 1;
      }

      // Show Matrix & Vector
//      printf("Matrix:\n");
//      displayMatrix(M, N, (unsigned long*) matrix);
//      printf("\nVector:\n");
//      displayMatrix(N, 1, vector);
    }

    MPI_Bcast(&result_local, N, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&matrix, M*N, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);
    MPI_Bcast(&vector, N, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

    // Calculate
    long startTime = ms_time();

    for (m=rank*eltProc; m<rank*eltProc + eltProc; m++) {
      for (n=0; n<N; n++) {
        result_local[m] = result_local[m] + matrix[m][n] * vector[n];
      }
    }

    MPI_Reduce(&result_local, &result, M, MPI_UNSIGNED_LONG, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
      long cTime = ms_time() - startTime;

      // Show result
      printf("\nResult calculated in %ldms\n", cTime);
//      displayMatrix(M, 1, result);
    }

    MPI_Finalize();
  }
  else {
    printf("Please Enter the Matrix Size (eq: ./mulMatVec 10 5)");
  }

  return 0;
}