#include<mpi.h>
#define TRUE 1
#define FALSE 0

/* Run with 12 processes */

int main(int argc, char *argv[]) {
	int rank;
	MPI_Comm com2d;
	int dim[2],period[2],reorder;
	int coord[2],id;
	
	int up,down,right,left;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	dim[0]=4; dim[1]=3;
	period[0]=TRUE; period[1]=TRUE;
	reorder=FALSE;
	
	MPI_Cart_create(MPI_COMM_WORLD,2,dim,period,reorder,&com2d);
	
	if(rank==11){
		
		printf("\n 0  1  2\n 3  4  5\n 6  7  8\n 9 10 11\n\n");
		
		MPI_Cart_coords(com2d,rank,2,coord);
		printf("My rank is %d; My coordinates are %d %d\n",rank,coord[0],coord[1]);
		
		MPI_Cart_shift(com2d,0,1,&up,&down);
		MPI_Cart_shift(com2d,1,1,&left,&right);
		
		printf("My neighbors are left: %d right:%d up:%d down:%d\n",left,right, up, down);
	}	
	
	MPI_Finalize();
}
