#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
// Retrieve Time
long ms_time()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}
double f(double x)
{
	return 4 / (1 + x * x);
}
int main(int argc, char* argv[])
{
	if (argc == 2) {
		int nbSplit = atoi(argv[1]); // Number of split
		double s = 1. / nbSplit; // Step
		double pi = 0.; // Aproximation of PI
		long startTime = ms_time();
		int i; // Loop Iterator
		#pragma omp parallel for reduction (+:pi)
		for (i=0; i<nbSplit; i++) {
			pi = pi + s * ((f(i*s) + f((i+1) * s)) / 2);
		}
		long cTime = ms_time() - startTime;
		printf("%lf [%ldms]\n", pi, cTime);
	}
	else {
		printf("Please add number of splitting in command line\n");
	}
	return 0;
}