#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define root 0
#define cols 4

int numnodes, myrank, elt;

int main(int argc,char **argv){
	
	MPI_Init(&argc,&argv);
	
	MPI_Comm_size( MPI_COMM_WORLD, &numnodes );
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	int rows = numnodes;
	int send_array[rows][cols]; //2D array
	int receive_array[cols];    //1D Array
		 
	int count=rows * cols;
	
	if(myrank == root){
		printf("\nThe elements are:\n");
		for(int i=0;i<rows;i++){
			for(int j=0;j<cols;j++){
				elt = cols * i + j;
				send_array[i][j]= elt;
				printf("%4d  ",elt);
			}
			printf("\n");
		}	
		printf("\n");			
	}
	
	MPI_Scatter( send_array, cols, MPI_INT, receive_array, cols, MPI_INT, root, MPI_COMM_WORLD);
	
	int row_sum=0;
	for(int i=0;i<cols;i++)
		row_sum += receive_array[i]; 
	printf("process %d: row sum = %d \n",myrank, row_sum);
	
	MPI_Finalize();
}
