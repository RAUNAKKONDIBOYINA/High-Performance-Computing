#include<iostream>
#include<thread>
#include<bits/stdc++.h>
using namespace std;

bool isSorted = false;
int arr[] = {34, 2, 10, -9, 4, 0, 14, 15};
int n = sizeof(arr)/sizeof(arr[0]); 

void fun()
{
    for (int i=1; i<=n-2; i=i+4) 
    { 
        if (arr[i] > arr[i+1]) 
        { 
            swap(arr[i], arr[i+1]); 
            isSorted = false; 
        } 
    }
}
void fun1()
{
    for (int i=3; i<=n-2; i=i+4) 
    { 
        if (arr[i] > arr[i+1]) 
        { 
            swap(arr[i], arr[i+1]); 
            isSorted = false; 
        } 
    }
}

void fun2()
{
    for (int i=0; i<=n-2; i=i+4) 
        { 
            if (arr[i] > arr[i+1]) 
            { 
                swap(arr[i], arr[i+1]); 
                isSorted = false; 
            } 
        } 
}
void fun3()
{
    for (int i=2; i<=n-2; i=i+4) 
        { 
            if (arr[i] > arr[i+1]) 
            { 
                swap(arr[i], arr[i+1]); 
                isSorted = false; 
            } 
        } 
}

void oddEvenSort(int arr[], int n) 
{ 
     // Initially array is unsorted 
  
    while (!isSorted) 
    { 
        isSorted = true; 
  
        thread t1(fun);
        thread t2(fun1);
        /*for (int i=1; i<=n-2; i=i+2) 
        { 
            if (arr[i] > arr[i+1]) 
             { 
                swap(arr[i], arr[i+1]); 
                isSorted = false; 
              } 
        } */
              t1.join();
              t2.join();
  
        thread t3(fun2);
        thread t4(fun3);
        t3.join();
        t4.join();

        // Perform Bubble sort on even indexed element 
        /*for (int i=0; i<=n-2; i=i+2) 
        { 
            if (arr[i] > arr[i+1]) 
            { 
                swap(arr[i], arr[i+1]); 
                isSorted = false; 
            } 
        } */
    } 
  
    return; 
} 
  
// A utility function ot print an array of size n 
void printArray(int arr[], int n) 
{ 
   for (int i=0; i < n; i++) 
       cout << arr[i] << " "; 
   cout << "\n"; 
} 
  
// Driver program to test above functions. 
int main() 
{ 
    
    
  
    oddEvenSort(arr, n); 
    printArray(arr, n); 
  
    return (0); 
} 

