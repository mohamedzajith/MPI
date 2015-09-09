#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
 
/*
compiling: mpicxx Calculate_sum.cpp -o Calculate_sum
executing: mpiexec -n 5 Calculate_sum 2 12
*/
 
int main(int argc, char *argv[])
{
    int rank, np, i,result=0,start,stop;
    int buffer;
    MPI_Status status;
    MPI_Init(&argc, &argv);
	
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(argc!=3){
            if (rank == 0) printf("\n\nPlease give starting and ending numbers as parameters. Argument count should be 3 instead of %d. For example, \n\n  mpiexec -n 5 ./Calculate_sum 2 12\n\n",argc);
            MPI_Finalize();
            return 1;
    }
    start = atoi(argv[1]);
    stop = atoi(argv[2]);
    if(stop-start<=0){
            printf("Starting number should be smaller than the ending number");
            MPI_Finalize();
            return 1;
    }
    if (rank == 0)
    {
        for (i=1; i<np; i++){
            MPI_Recv(&buffer, 1, MPI_INT, i, 123, MPI_COMM_WORLD, &status);
            result += buffer;
        }
            printf("Result : %d\n",result);
    }
    else
    {
        buffer =  0;
        for (i=rank-1; i<=stop-start; i+=np-1){
                buffer += start+i;
        }
        printf("Slave %d: %d\n",rank,buffer);
        MPI_Send(&buffer, 1, MPI_INT, 0, 123, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}

