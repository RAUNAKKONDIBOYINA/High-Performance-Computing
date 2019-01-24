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
using namespace std;

bool isSorted = false;
int arr2[] = {8,7,6,5,4,3,2,1};
int n = sizeof(arr2)/sizeof(arr2[0]); 
int* arr[8];


void fun(int j,int n)
{

   
    for (int i=j; i<=n-2; i=i+4) 
    { 
         
        if ((*arr)[i] > (*arr)[i+1]) 
        { 
            //cout<<"hello"<<endl;
            int t=(*arr)[i];
            (*arr)[i]=(*arr)[i+1];
            (*arr)[i+1]=t;
            //swap(*arr[i], *arr[i+1]); 
            //(*arr)[i]=-1;
            isSorted = false; 
        } 
    }
}
void fun1(int j,int n)
{
    for (int i=j; i<=n-2; i=i+4) 
    { 
         
        if ((*arr[i]) > (*arr)[i+1]) 
        { 
            //cout<<"hello"<<endl;
            int t=(*arr)[i];
            (*arr)[i]=(*arr)[i+1];
            (*arr)[i+1]=t;
            //swap(*arr[i], *arr[i+1]); 
            isSorted = false; 
        } 
    }
}

void fun2(int j,int n)
{
    for (int i=j; i<=n-2; i=i+4) 
        { 
            if ((*arr)[i] > (*arr)[i+1]) 
            { 
                int t=(*arr)[i];
            (*arr)[i]=(*arr)[i+1];
            (*arr)[i+1]=t;
                //swap(*arr[i], *arr[i+1]); 
                isSorted = false; 
            } 
        } 
}
void fun3(int j,int n)
{
    for (int i=j; i<=n-2; i=i+4) 
        { 
            if ((*arr)[i] > (*arr)[i+1]) 
            { 
                int t=(*arr)[i];
            (*arr)[i]=(*arr)[i+1];
            (*arr)[i+1]=t;
                //swap(*arr[i], *arr[i+1]); 
                isSorted = false; 
            } 
        } 
}

void oddEvenSort(int k, int n) 
{ 
     // Initially array is unsorted 
  
    while (!isSorted) 
    { 
        //cout<<"inside"<<endl;
        isSorted = true; 
  
        thread t1(fun,k,n);
        thread t2(fun1,k+2,n);
        
              t1.join();
              t2.join();
  
        thread t3(fun2,k-1,n);
        thread t4(fun3,k+1,n);
        t3.join();
        t4.join();

    } 
  
    return; 
} 
  
// A utility function ot print an array of size n 
void printArray(int* arr, int n) 
{ 
   for (int i=0; i < n; i++) 
       cout << arr[i] << " "; 
   cout << "\n"; 
} 
  
void gun()//int *arr
{
    int f=fork();
    if(f==0)
    {
        oddEvenSort(1,n/2); 
        /*for(int i=0;i<8;i++)
    {
        cout<<(*arr)[i]<<" ";
    }*/
    }
    else
    {
        oddEvenSort(n/2+1,n);
        /*for(int i=0;i<8;i++)
    {
        cout<<(*arr)[i]<<" ";
    }*/
    }
    return;
}
// Driver program to test above functions. 
int main() 
{ 
    int temp_array[10]={0};
    key_t key=9876;
    int shmid;
    shmid=shmget(key,1024, 0664 | IPC_CREAT);
    *arr=(int *)shmat(shmid, (void *) 0 ,0);
    for(int i=0;i<8;i++)
    {
        (*arr)[i]=arr2[i];
        temp_array[i]=arr2[i];
    }

    thread tr(gun);
    tr.join();
    
    

    /*for(int j=0;j<8;j++);
    {
        temp_array[j]=(*arr)[j];
    }*/

    sort(temp_array,temp_array+8);

    //*arr first and second half are sorted independently
    //use merging of 2 sorted array here
    for(int i=0;i<8;i++)
    {
        //cout<<(*arr)[i]<<" ";
        cout<<temp_array[i]<<" ";
    }
    //printArray(arr, n); 
  
    return (0); 
} 

