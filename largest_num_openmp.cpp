#include<iostream>
using namespace std;
#include<omp.h>

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
	int large[100]={0};

	#pragma omp parallel num_threads(4)
	{
		int t_id=omp_get_thread_num();
		for(int i=t_id;i<l;i+=omp_get_num_threads())
		{
			if(A[i]>large[t_id])
			{
				large[t_id]=A[i];
			}
			
		}
	}

	int largest=0;
	for(int i=0;i<=4;i++)
	{
		if(large[i]>largest)
		{
			largest=large[i];
		}
	}
	cout<<"largest number is="<<largest<<endl;


	return 0;
}