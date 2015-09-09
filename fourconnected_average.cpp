#include<mpi.h>
#define TRUE 1
#define FALSE 0

/* Run with 24 processes */

int main(int argc, char *argv[]) {
	
	MPI_Status status;
	MPI_Comm com2d;
	int coord[2], dim[2],period[2],reorder;
	int lval = 0, rval = 0,uval = 0,dval = 0, sendval;
	int up,down,right,left, rank;
	
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	dim[0]=4; dim[1]=6;
	period[0]=TRUE; period[1]=TRUE;
	reorder=FALSE;
	
	MPI_Cart_create(MPI_COMM_WORLD,2,dim,period,reorder,&com2d);
	MPI_Cart_coords(com2d,rank,2,coord);
		
	MPI_Cart_shift(com2d,0,1,&up,&down);
	MPI_Cart_shift(com2d,1,1,&left,&right);
	
	sendval = rank;
	
	if (coord[0] % 2 == 1) {
		MPI_Sendrecv(&sendval, 1, MPI_INT, up, 1, &uval, 1, MPI_INT, up, 1, com2d, &status); 
		MPI_Sendrecv(&sendval, 1, MPI_INT, down, 1, &dval, 1, MPI_INT, down, 1, com2d, &status);
	}
	else {
		MPI_Sendrecv(&sendval, 1, MPI_INT, down, 1, &dval, 1, MPI_INT, down, 1, com2d, &status);
		MPI_Sendrecv(&sendval, 1, MPI_INT, up, 1, &uval, 1, MPI_INT, up, 1, com2d, &status); 
	}
	
	if (coord[1] % 2 == 1) {
		MPI_Sendrecv(&sendval, 1, MPI_INT, left, 1, &lval, 1, MPI_INT, left, 1, com2d, &status); 
		MPI_Sendrecv(&sendval, 1, MPI_INT, right, 1, &rval, 1, MPI_INT, right, 1, com2d, &status);
	}
	else {
		MPI_Sendrecv(&sendval, 1, MPI_INT, right, 1, &rval, 1, MPI_INT, right, 1, com2d, &status);
		MPI_Sendrecv(&sendval, 1, MPI_INT, left, 1, &lval, 1, MPI_INT, left, 1, com2d, &status); 
	}
	
	if(rank==9) {
		printf("\n\t 0  1  2  3  4  5\n\t 6  7  8  9 10 11\n\t12 13 14 15 16 17\n\t18 19 20 21 22 23\n\n");		
		
		printf("My rank is %d; My position is (%d, %d)\n",rank,coord[0],coord[1]);
		
		printf("dval = %d, uval = %d, lval = %d, rval = %d\n", dval, uval,lval,rval );
		
		float avg = (float)(uval + dval + lval + rval)/4;
		
		printf("Four connected neighbour average is: %.2f \n\n",avg);
	}	
	
	MPI_Finalize();
}
