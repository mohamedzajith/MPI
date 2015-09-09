#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "math.h"
#include "mpi.h"


int val=3;


int proc_map(int i, int size)
{
    size = size - 1;
    int r = (int) ceil( (double)val / (double)size);
    int proc = i / r;
    return proc + 1;
}


int main(int argc, char** argv)
{
    int size, rank;
    MPI_Status Stat;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
 
    if (rank == 0)
    {
        int a[val];
        int b[val];
        int c[val];
 
        srand(time(NULL));
        for (int i=0;i<val;i++)
        {
            
                a[i]= rand() % 10;
		b[i]= rand() % 10;
            
        }
 
 
        printf("Vector A :\n");
        for (int i=0;i<val;i++)
        {
            
                printf("%d ", a[i]);
            
            printf("\n");
        }
        printf("\nVector B :\n");
        for (int i=0;i<val;i++)
        {
            printf("%d ", b[i]);
        }
        printf("\n\n");
 
       
        for (int j=1;j<size;j++)
        {
            MPI_Send(b, val, MPI_INTEGER, j, 99, MPI_COMM_WORLD);
        }
 
        
        for (int i=0;i<val;i++)
        {
            int pro = proc_map(i, size);
            MPI_Send(&a[i], val, MPI_INTEGER, pro, (100*(i+1)), MPI_COMM_WORLD);
        }
 
        
        for (int i=0;i<1;i++)
        {
            int source_process = proc_map(i, size);
            MPI_Recv(&c[i], 1, MPI_INTEGER, source_process, i, MPI_COMM_WORLD, &Stat);
            printf("sum is %d\n", c[i]);
        }
    }
    else
    {
        int b[val];
 
       	MPI_Recv(b, val, MPI_INTEGER, 0, 99, MPI_COMM_WORLD, &Stat);
 
        for (int i=0;i<val;i++)
        {
            int pro = proc_map(i, size);
            if (rank == pro)
            {
                int temp[val];
                MPI_Recv(temp, val, MPI_INTEGER, 0, (100*(i+1)), MPI_COMM_WORLD, &Stat);
                int sum = 0;
                for (int j=0;j<val;j++)
                {
                    sum = sum + (temp[j] * b[j] );
                }
                MPI_Send(&sum, 1, MPI_INTEGER, 0, i, MPI_COMM_WORLD);
            }
        }
    }
 
    MPI_Finalize();
    return 0;
}



