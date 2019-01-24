#include<iostream>
using namespace std;
#include<omp.h>
#include <cstdio>
#include <ctime>


void bitonic_sort(int A[],int l,int A2[])
{
	int k=0;
	for(int i=0;i<l;i+=2)
	{
		A2[i]=A[k];
		k++;
	}
	for(int i=1;i<l;i+=2)
	{
		A2[i]=A[k];
		k++;
	}

	#pragma omp parallel num_threads(4)
	{
		clock_t start;
    	double duration;

    	start = std::clock();

    
		int t_id=omp_get_thread_num();
		
		for(int i=(t_id-1)*2;i<l;i+=4)
		{
			if(A2[i]>A2[i+1])
			{
				int temp=A2[i];
				A2[i]=A2[i+1];
				A2[i+1]=temp;
			}
			
		}
		
		duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    	//cout<<"thread"<<t_id<<"took "<<duration <<" seconds"<<endl;
		
	}

	for(int i=0;i<l;i++)
	{
		A[i]=A2[i];
	}
	return;

}

void bitonic(int A[], int l)
{
	int A2[100]={0};
	for(int i=0;i<l/2;i++)
	{
		bitonic_sort(A,l,A2);
	}

}


int main()
{
	int A[100]={0};
	int l;
	cout<<"enter length of array in powers of 2"<<endl;
	cin>>l;
	cout<<"enter elements"<<endl;
	for(int i=0;i<l;i++)
	{
		cin>>A[i];
	}
	int t=4;
	cout<<"enter no of processors"<<endl;
	cin>>t;

	bitonic(A,l);

		
	for(int i=0;i<l;i++)
	{
		cout<<A[i]<<" ";
	}
	


	return 0;
}