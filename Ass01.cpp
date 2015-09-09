#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
int numnodes, myid;
#define root 0
int main(int argc,char **argv)
{
    int *local_array,*send_array,*receive_array;
    int count, size, mysize, i, k, j, total,sum;

    MPI_Init(&argc,&argv);
    MPI_Comm_size( MPI_COMM_WORLD, &numnodes );
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    count=4;

    local_array=(int*)malloc(count*sizeof(int));
    if(myid == root){
        size=count*numnodes;
        send_array=(int*)malloc(size*sizeof(int));
        receive_array=(int*)malloc(numnodes*sizeof(int));
        for(i=0;i<size;i++)
        send_array[i]=i;
    }

    MPI_Scatter( send_array, count,MPI_INT,local_array,count,MPI_INT,root,MPI_COMM_WORLD);
    total=0;
    for(i=0;i<count;i++)
        total=total+local_array[i];
    printf("myid= %d ; my total= %d\n",myid,total);


    MPI_Gather( &total,1,MPI_INT,receive_array,1,MPI_INT,root,MPI_COMM_WORLD);
    if(myid == root){
        sum=0;
        for(i=0;i<numnodes;i++)
            sum=sum+receive_array[i];
        printf("total sum = %d\n",sum);
    }

    MPI_Finalize();
}
