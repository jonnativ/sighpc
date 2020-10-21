#include <stdio.h>
#include <unistd.h>
#include <openacc.h>

void saxpy(int n, float a, float *x, float *restrict y) {
	#pragma acc parallel loop
	for(int i = 0; i < n; ++i)
		y[i] = a*x[i] + y[i];
		sleep(1);
}

int main() {
	float x[1<<15];
	float y[1<<15];
	int def= acc_get_device_num(acc_device_nvidia);
	acc_set_device_num(0, acc_device_nvidia);
	saxpy(1<<15, 2.0, x, y);
	printf("done %d\n", def);
}
