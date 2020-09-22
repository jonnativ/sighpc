#include <stdio.h>
#include <omp.h>

int main() {
	printf("BEFORE PARALLEL REGION\n");
	#pragma omp parallel
	{	
		int ID = omp_get_thread_num();
		printf("hello world(%d)\n", ID);
	}
	printf("BEFORE PARALLEL REGION\n");
}
