#include <mpi.h> 
main(int argc, char *argv[]) 
{ 
	int send_val1 = 10, send_val2 = 20, rec_val1, rec_val2, npes, myrank; 
	MPI_Init(&argc, &argv); 

	MPI_Status status;

	MPI_Comm_size(MPI_COMM_WORLD, &npes); 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 

	if (myrank == 0) {
		MPI_Send(&send_val1, 1, MPI_INT, 1, 1, MPI_COMM_WORLD);
		MPI_Send(&send_val2, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
		printf("Process %d sent %d and %d \n", myrank, send_val1, send_val2); 
	}
	else 
	if (myrank == 1) {
		MPI_Recv(&rec_val2, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, &status); 
		MPI_Recv(&rec_val1, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
		printf("Process %d receiced %d and %d \n", myrank, rec_val2, rec_val1); 
	}

	MPI_Finalize(); 
} 
