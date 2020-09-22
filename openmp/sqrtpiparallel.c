#include<stdio.h>
#include<omp.h>

#define NUM_THREADS 40

static long num_steps = 1000000000;
double step;
int main() {
	int i;
	double x, pi, sum = 0.0;
	
	step = 1.0/(double) num_steps;

	double tsum[NUM_THREADS];
	omp_set_num_threads(NUM_THREADS);
	#pragma omp parallel
	{
		int ID = omp_get_thread_num();
		double thread_sum = 0.0;
		int i;
		for(i = ID; i < num_steps; i += NUM_THREADS) {
			x = (i + 0.5) * step;
			tsum[ID] = tsum[ID] + 4.0/(1.0 + x * x);
		}
		//tsum[ID] = thread_sum;
	}
	for(i = 0; i < NUM_THREADS; ++i) {
		sum += tsum[i];
	}
	pi = step * sum;
	printf("pi = (%f)\n", pi);
}
