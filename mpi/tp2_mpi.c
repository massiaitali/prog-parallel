#include <stdlib.h>
#include <stdio.h>
#include "mpi.h"

double f(double x) {
	double res;
	return (4./(1.+(x*x)));
}
long ms_time(void) {
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return(tv.tv_sec*1000 + tv.tv_usec/1000);
}

int main(int argc, char **argv)
{
	int rank, size, recu, message;
	MPI_Status statut;

	MPI_Init ( &argc, &argv );
	MPI_Comm_rank ( MPI_COMM_WORLD, &rank );
	MPI_Comm_size ( MPI_COMM_WORLD, &size );

	double a,b;
	double pi=0.;
	int n,i;
	double sum, res;
	
	n = 10000;
	a = 0;
	b = 1;

	double nbproc = n / size;

	sum = 0.;
	double s = (b-a)/n;

	long start = ms_time();
	for (i = rank * nbproc ; i < rank * nbproc + nbproc ; i++) {	
		sum = sum + s * ((f(i*s) + f((i+1)*s))/2);

	}

	MPI_Allreduce (&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	long end = ms_time();

	long duration = end - start;
	
	if (rank == 0)
	{
		printf("pi = %f  [%ld ms] \n", pi, duration);
	}
	


	MPI_Finalize ();

	return 0;
}