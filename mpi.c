#include<stdio.h>
#include<mpi.h>

int main(int argc, char** argv)
{
	int ierr;
	ierr=MPI_Init(&argc,&argv);
	printf("hello world");
	ierr = MPI_Finalize();
	return 0;
}