#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<errno.h>
#include<semaphore.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>

int main()
{
	int i;
	key_t shmkey;
	int shmid;
	sem_t *sem;
	pid_t pid;
	int *p;
	unsigned int n;
	unsigned int values;
	shmkey=ftok("/Documents/HPC/semaphore.c",5);
	shmid=shmget(shmkey,sizeof(int),0644|IPC_CREAT);
	if(shmid<0)
	{
		perror("shmget\n");
		exit(1);
	}
	p=(int*)shmat(shmid,NULL,0);
	*p=0;
	printf("p=%d is allocated in shared memory\n",*p);

	printf("enter no of children");
	scanf("%u",&n);
	printf("semaphore value?");
	scanf("%u",&values);

	sem=sem_open("sem_here",O_CREAT|O_EXCL, 0644,values);

	sem_unlink("sem_here");

	printf("semaphore initialized\n");

	for(i=0;i<n;i++)
	{
		pid=fork();
		if(pid<0)
		{
			printf("fork error");

		}
		else if(pid==0)
		{
			break;
		}
	
	}
	if(pid!=0)
	{
			while(pid=waitpid(-1,NULL,0))
			{
				if(errno==ECHILD)
					break;
			}
		

		printf("all children exited\n");

		shmdt(p);
		shmctl(shmid,IPC_RMID,0);
		sem_destroy(sem);
		exit(0);
	}
	else
	{
		sem_wait(sem);
		printf("child %d is in critical section\n",i);
		sleep(1);
		*p+=i%3;
		printf("child %d new value of *p=%d\n",i,*p);
		sem_post(sem);
		exit(0);



	}






}
