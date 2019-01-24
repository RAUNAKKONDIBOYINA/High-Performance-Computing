#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>


int main(int argc,int* argv[])
{
	printf("i am %d\n",(int)getpid());

	pid_t pid=fork();

	printf("fork returned %d\n", (int) pid);

	if(pid<0)
	{
		perror("fork error");
	}
	if(pid!=0)
	{
		printf("i am parent \n");
		//wait(NULL);  //wait for child to join
		
	}
	else
	{
		
		printf("i am child with pid %d\n", (int) getpid());

		execl("/bin/echo","echo","hello world",NULL);
	}

	return 0;
}
