#include<iostream>
#include<thread>
using namespace std;


void fun()
{
	cout<<"hello"<<endl;
}

int main(int argc,char* argv[])
{
	thread t1(fun);
	
	cout<<"main thread"<<endl;
	t1.join();
	return 0;
}