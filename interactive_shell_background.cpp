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


		cout<<"child process"<<endl;
		cout<<"enter a background command"<<endl;
		char s[100];
		cin.getline(s,100);
		int v=system(s);
		int t=system("jobs");

		
		
		
	}

	
	return 0;
	
}



