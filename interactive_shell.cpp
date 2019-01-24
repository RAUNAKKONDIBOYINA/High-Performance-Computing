#include<iostream>
#include<thread>
#include<sys/types.h>
#include<unistd.h>
//#include<sys/sockets.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<bits/stdc++.h>
#include<stdlib.h>
using namespace std;


int main()
{
	

	int n=fork();

	if(n==0)
	{


		cout<<endl<<"child process"<<endl;
		cout<<"enter a command"<<endl;
		char c[100];
		cin>>c;
		int r=system(c);

		
		
		
	}

	
	return 0;
	
}