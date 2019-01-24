#include<iostream>
using namespace std;
#include<thread>

int sum[4]={0};
int a[20]={0};
int threadno=0;

int fun()
{
	int current=threadno++;

	for(int j=current*(20/4);j<(current+1)*(20/4);j++)
	{
		sum[current]+=a[j];
	}
}


int main()
{
	
	int l;
	cout<<"enter array size"<<endl;
	cin>>l;
	cout<<"enter array elements"<<endl;
	for(int i=0;i<l;i++)
	{
		cin>>a[i];
	}

	thread t1(fun);
	thread t2(fun);
	thread t3(fun);
	thread t4(fun);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	int final=0;
	for(int i=0;i<4;i++)
	{
		final+=sum[i];
	}
	cout<<final<<endl;
}