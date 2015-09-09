#include <mpi.h> 
main(int argc, char *argv[]) 
{ 
	int send_val = 10, rec_val, npes, myrank; 
	MPI_Init(&argc, &argv); 

	MPI_Status status;

	MPI_Comm_size(MPI_COMM_WORLD, &npes); 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 

	if (myrank == 0) {
		MPI_Send(&send_val, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		printf("Process %d sent %d\n", myrank, send_val); 
	}
	else 
	if (myrank == 1) {
		MPI_Recv(&rec_val, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status); 
		printf("Process %d receiced %d\n", myrank, rec_val); 
	}

	MPI_Finalize(); 
} 
