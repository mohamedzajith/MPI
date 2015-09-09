#include <mpi.h> 
main(int argc, char *argv[]) 
{ 
	int send_val, rec_val, source, dest, npes, myrank; 
	MPI_Init(&argc, &argv); 

	MPI_Status status;

	MPI_Comm_size(MPI_COMM_WORLD, &npes); 
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank); 

	send_val = myrank;
	source = (myrank-1 + npes) % npes;
	dest = (myrank + 1) % npes;
	
	MPI_Send(&send_val, 1, MPI_INT, dest, 1, MPI_COMM_WORLD);
	MPI_Recv(&rec_val, 1, MPI_INT, source, 1, MPI_COMM_WORLD, &status);
	
	printf("Process %d receiced from %d \n", myrank, rec_val); 
	
	MPI_Finalize(); 
} 
