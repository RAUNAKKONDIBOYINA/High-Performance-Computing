#include<stdio.h>
#include<iostream>
using namespace std;
#include<mpi.h>

int main(int argc, char** argv)
{
	int ierr;
	ierr=MPI_Init(&argc,&argv);
	cout<<"hello world"<<endl;
	ierr = MPI_Finalize();
	return 0;
}