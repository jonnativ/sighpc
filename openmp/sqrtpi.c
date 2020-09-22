#include<stdio.h>

static long num_steps = 1000000000;
double step;
int main() {
	double x, pi, sum = 0.0;
	
	step = 1.0/(double) num_steps;
	
	int i;	
	for(i = 0; i < num_steps; ++i) {
		x = (i + 0.5) * step;
		sum = sum + 4.0/(1.0 + x*x);
	}
	
	pi = step * sum;
	printf("pi = (%f)\n", pi);
}
