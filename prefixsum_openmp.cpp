#include<iostream>
using namespace std;
#include<omp.h>
#include <cstdio>
#include <ctime>

int main()
{
	int A[100];
	int l;
	cout<<"enter length of array"<<endl;
	cin>>l;
	cout<<"enter elements"<<endl;
	for(int i=0;i<l;i++)
	{
		cin>>A[i];
	}
	int t=4;
	cout<<"enter no of processors"<<endl;
	cin>>t;

	#pragma omp parallel num_threads(t)
	{
		clock_t start;
    	double duration;

    	start = std::clock();

    
		int t_id=omp_get_thread_num();
		if(t_id==t-1)
		{
			for(int i=t_id*4;i<l;i+=2)
			{
				A[i+1]=A[i]+A[i+1];
			
			}
		}
		else
		{
			for(int i=t_id*4;i<(t_id+1)*4 && i<l;i+=2)
			{
				A[i+1]=A[i]+A[i+1];
			
			}
		}
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    	cout<<"thread"<<t_id<<"took "<<duration <<" seconds"<<endl;
		
	}

	for(int i=1;i<l;i+=2)
	{
		A[i+2]=A[i+2]+A[i];
	}

	for(int i=1;i<l;i+=2)
	{
		A[i+1]=A[i+1]+A[i];
	}
	


	
	for(int i=0;i<l;i++)
	{
		cout<<A[i]<<" ";
	}
	


	return 0;
}