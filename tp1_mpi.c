#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv)
{
	int rank, size, recu, message;
	MPI_Status statut;

	MPI_Init ( &argc, &argv );
	MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
	MPI_Comm_size ( MPI_COMM_WORLD, &size );

	if(rank % 2 == 0){
		if (rank + 1 < size)
		{
			MPI_Send(&rank, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
			MPI_Recv(&message, 1, MPI_INT, rank + 1, 2, MPI_COMM_WORLD, &statut);
			printf("Process %d pair [%d]\n", rank, message);
		}
		else printf("Sans ami [%d]\n", rank);

	}
	else {
		MPI_Recv(&recu, 1, MPI_INT, rank - 1, 1, MPI_COMM_WORLD, &statut);
		recu += 10*rank;
		MPI_Send(&recu, 1, MPI_INT, rank - 1, 2, MPI_COMM_WORLD);
	}

	MPI_Finalize ();

	return 0;
}