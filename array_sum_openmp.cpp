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
	int sum=0;

	#pragma omp parallel num_threads(4) reduction(+: sum)
	{
		int t_id=omp_get_thread_num();
		for(int i=t_id;i<l;i+=omp_get_num_threads())
		{
			//#pragma omp critical
			sum+=A[i];
		}
		cout<<sum<<endl;
	}

	cout<<sum<<endl;

	return 0;
}