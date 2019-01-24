//mpi can be called only once and finalized only once
//the current attempted code cannot be executed as
//the entire code is duplicated instead of just a function using mpi
//for such program openmp performs better



#include<bits/stdc++.h> 
#include<iostream>
using namespace std; 
#include<omp.h>
#include <cstdio>
#include <ctime>
#include <stdio.h>
#include <mpi.h>

#define max_rows 100000
#define send_data_tag 2001
#define return_data_tag 2002
int N;

int array[max_rows];
int array2[max_rows];
  
/*The parameter dir indicates the sorting direction, ASCENDING 
   or DESCENDING; if (a[i] > a[j]) agrees with the direction, 
   then a[i] and a[j] are interchanged.*/
void compAndSwap(int a[], int i, int j, int dir) 
{ 
    if (dir==(a[i]>a[j])) 
        swap(a[i],a[j]); 
} 
  
/*It recursively sorts a bitonic sequence in ascending order, 
  if dir = 1, and in descending order otherwise (means dir=0). 
  The sequence to be sorted starts at index position low, 
  the parameter cnt is the number of elements to be sorted.*/
void bitonicMerge(int a[], int low, int cnt, int dir,int argc,char** argv) 
{ 
    if (cnt>1) 
    { 
        int k = cnt/2; 
        /*for (int i=low; i<low+k; i++) 
            compAndSwap(a, i, i+k, dir); */
        MPI_Status status;
        int my_id, root_process, ierr, i, num_rows, num_procs,
         an_id, num_rows_to_receive, avg_rows_per_process, 
         sender, num_rows_received, start_row, end_row, num_rows_to_send;

         ierr = MPI_Init(&argc, &argv);
         
         root_process = 0;
      
        /* find out MY process ID, and how many processes were started. */
      
        ierr = MPI_Comm_rank(MPI_COMM_WORLD, &my_id);
        ierr = MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

        if(my_id == root_process) {


        for(an_id = 1; an_id < num_procs; an_id++) {

            //start_row = an_id*avg_rows_per_process + 1;
            start_row=low+an_id-1;
            //end_row   = (an_id + 1)*avg_rows_per_process;
            end_row=low+k;

            /*if((num_rows - end_row) < avg_rows_per_process)
               end_row = num_rows - 1;*/

            //num_rows_to_send = end_row - start_row + 1;
            num_rows_to_send=N-start_row+1;

            ierr = MPI_Send( &num_rows_to_send, 1 , MPI_INT,
                  an_id, send_data_tag, MPI_COMM_WORLD);

            ierr = MPI_Send( &a[start_row], num_rows_to_send, MPI_INT,
                  an_id, send_data_tag, MPI_COMM_WORLD);

            ierr = MPI_Send( &dir, 1 , MPI_INT,
                  an_id, send_data_tag, MPI_COMM_WORLD);
         }


         for(an_id = 1; an_id < num_procs; an_id++) {
            
            ierr = MPI_Recv( &a, num_rows_to_receive, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);
  
            sender = status.MPI_SOURCE;

            //printf("Partial sum %d returned from process %d\n", partial_sum, sender);
     
         }

        }
        else {

         /* I must be a slave process, so I must receive my array segment,
          * storing it in a "local" array, array1. */

         ierr = MPI_Recv( &num_rows_to_receive, 1, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);
          
         ierr = MPI_Recv( &array2, num_rows_to_receive, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);

         ierr = MPI_Recv( &dir, 1, MPI_INT, 
               root_process, send_data_tag, MPI_COMM_WORLD, &status);

         num_rows_received = num_rows_to_receive;

         /* Calculate the sum of my portion of the array */

         for (int i=0; i<num_rows_received; i+=4) 
            {
                if (dir==(array2[i]>array2[i+k])) 
                    swap(array2[i],array2[i+k]); 
            }  

         /* and finally, send my partial sum to hte root process */

         ierr = MPI_Send( &array2, num_rows_received, MPI_INT, root_process, 
               return_data_tag, MPI_COMM_WORLD);
      }
      ierr = MPI_Finalize();


        /*#pragma omp parallel num_threads(4)
        {
            
            int t_id=omp_get_thread_num();
            
            
            for (int i=low+t_id-1; i<low+k; i+=4) 
            {
                if (dir==(a[i]>a[i+k])) 
                    swap(a[i],a[i+k]); 
            }               
            
             
        
        }*/



        bitonicMerge(a, low, k, dir,argc,argv); 
        bitonicMerge(a, low+k, k, dir,argc,argv); 
    } 
} 
  
/* This function first produces a bitonic sequence by recursively 
    sorting its two halves in opposite sorting orders, and then 
    calls bitonicMerge to make them in the same order */
void bitonicSort(int a[],int low, int cnt, int dir,int argc,char** argv) 
{ 
    if (cnt>1) 
    { 
        int k = cnt/2; 
  
        // sort in ascending order since dir here is 1 
        bitonicSort(a, low, k, 1,argc,argv); 
  
        // sort in descending order since dir here is 0 
        bitonicSort(a, low+k, k, 0,argc,argv); 
  
        // Will merge wole sequence in ascending order 
        // since dir=1. 
        bitonicMerge(a,low, cnt, dir,argc,argv); 
    } 
} 
  
/* Caller of bitonicSort for sorting the entire array of 
   length N in ASCENDING order */
void sort(int a[], int N, int up,int argc, char** argv) 
{ 
    bitonicSort(a,0, N, up,argc,argv); 
} 
  
// Driver code 
int main(int argc, char **argv) 
{ 

    int a[100];//= {3, 7, 4, 8, 6, 2, 1, 5}; 
    cout<<"enter length in powers of 2"<<endl;
    
    cin>>N;

    for(int i=0;i<N;i++)
        cin>>a[i];
    //int N = sizeof(a)/sizeof(a[0]); 
  
  
    int up = 1;   // means sort in ascending order 
    sort(a, N, up,argc,argv); 
  
    cout<<"sorted array is"<<endl;
    for (int i=0; i<N; i++) 
        cout<<a[i]<<" ";
    return 0; 
} 

