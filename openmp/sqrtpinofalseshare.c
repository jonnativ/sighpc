#include<stdio.h>
#include<omp.h>

#define NUM_THREADS 40

static long num_steps = 1000000000;
double step;
int main() {
	double x, pi, sum = 0.0;
	
	step = 1.0/(double) num_steps;

	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		double thread_sum = 0.0;
		int i;
		for(i = ID; i < num_steps; i += NUM_THREADS) {
			x = (i + 0.5) * step;
			thread_sum = thread_sum + 4.0/(1.0 + x * x);
		}
		#pragma omp critical
			pi += thread_sum * step;
	}
	printf("pi = (%f)\n", pi);
}
