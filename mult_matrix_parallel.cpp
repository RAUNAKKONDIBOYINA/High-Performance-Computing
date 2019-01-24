#include<iostream>
using namespace std;
#include<thread>



int a[5][2]={0};
int b[2][3]={0};
int c[5][3]={0};
int threadno=0;



int fun()
{
	int current=threadno++;

	for(int j=0;j<3;j++)
	{
		int s=0;
		for(int i=0;i<2;i++)
		{
			
						s+=a[current][i]*b[i][j];
			
		}
		c[current][j]=s;
	}
	
}


int main()
{
	
	
	cout<<"enter 5x2 matrix"<<endl;
	
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<2;j++)
		{
			cin>>a[i][j];
		}
	}

	cout<<"enter 2x3 matrix"<<endl;
	
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;j++)
		{
			cin>>b[i][j];
		}
	}


	thread t1(fun);
	thread t2(fun);
	thread t3(fun);
	thread t4(fun);
	thread t5(fun);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	cout<<"output array"<<endl;
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<3;j++)
		{
			cout<<c[i][j]<<" ";
		}
		cout<<endl;
	}
	
}