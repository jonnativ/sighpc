#include "mpi.h"
#include <stdio.h>
#define SIZE 8

int main(int argc, char *argv[])  {
	int numtasks, rank, sendcount, recvcount, source, dest;
	int startbuf[SIZE][SIZE] = {
		{1, 2, 3, 4, 5, 6, 7, 8},
		{9, 10, 11, 12, 13, 14, 15, 16},
		{17, 18, 19, 20, 21, 22, 23, 24},
		{25, 26, 27, 28, 29, 30, 31, 32},
		{33, 34, 35, 36, 37, 38, 39, 40},
		{41, 42, 43, 44, 45, 46, 47, 48},
		{49, 50, 51, 52, 53, 54, 55, 56},
		{57, 58, 59, 60, 61, 62, 63, 64} };
	int sendbuf[SIZE];
	int recvbuf[SIZE];


	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (numtasks == SIZE) {
		// Scatter
		if (rank == 0) printf("SCATTER\n");
		source = 0;
		sendcount = SIZE;
		recvcount = SIZE;
		MPI_Scatter(startbuf, sendcount, MPI_INT, sendbuf, recvcount, MPI_INT, source, MPI_COMM_WORLD);
		printf("rank=%d  Results: %d %d %d %d %d %d %d %d\n", rank, sendbuf[0], sendbuf[1], sendbuf[2],
				sendbuf[3], sendbuf[4], sendbuf[5], sendbuf[6], sendbuf[7]);

		MPI_Barrier(MPI_COMM_WORLD);
		if (rank == 0) printf("=========================================\n");

		// AllGather
		if (rank == 0) printf("ALLGATHER\n");
		dest = 2;
		sendcount = 1;
		recvcount = 1;
		MPI_Allgather(sendbuf, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, MPI_COMM_WORLD);
		printf("rank=%d  Results: %d %d %d %d %d %d %d %d\n", rank, recvbuf[0], recvbuf[1], recvbuf[2],
				recvbuf[3], recvbuf[4], recvbuf[5], recvbuf[6], recvbuf[7]);

		MPI_Barrier(MPI_COMM_WORLD);
		if (rank == 0) printf("=========================================\n");
		
		// AlltoAll
		if (rank == 0) printf("ALLTOALL\n");
		sendcount = 1;
		recvcount = 1;
		MPI_Alltoall(sendbuf, sendcount, MPI_INT, recvbuf, recvcount, MPI_INT, MPI_COMM_WORLD);
		printf("rank=%d  Results: %d %d %d %d %d %d %d %d\n", rank, recvbuf[0], recvbuf[1], recvbuf[2],
				recvbuf[3], recvbuf[4], recvbuf[5], recvbuf[6], recvbuf[7]);

		MPI_Barrier(MPI_COMM_WORLD);
		if (rank == 0) printf("=========================================\n");
	
		// Reduce_scatter
		if (rank == 0) printf("REDUCE_SCATTER\n");
		int recvcounts[SIZE] = {1, 1, 1, 1, 1, 1, 1, 1};

		MPI_Reduce_scatter(sendbuf, recvbuf, recvcounts, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
		printf("rank=%d  Results: %d\n", rank, recvbuf[0]); 

	} else {
	       	if (rank == 0) printf("Must specify %d processors. Terminating.\n", SIZE);
	}

	MPI_Finalize();
}
