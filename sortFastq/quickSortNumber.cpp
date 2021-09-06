#include <stdio.h>
#include <limits.h>
#include <string.h>

// functions
// hoare
int partition(int arr[], int left, int right)
{
	 // take the first one as pivot
     int pivot = arr[left];
     int l = left;
     int r = right;
     while (l <= r)
     {
         while (arr[l] < pivot)
           l++;
	 while (arr[r] > pivot)
		 r--;
	//check if ending case first
	if (l>=r) return r;

	 // if not the ending case, you two should go to the other's group
	 int tmp = arr[l];
	arr[l] = arr[r];
	arr[r] = tmp;
     }
 }
// recursion function for quickSort process
 void quickSort(int arr[], int low, int high)
 {
     if (low < high)
     {
         // we are gonna have the higher one as partitioning index
	     int pi = partition(arr, low, high);
     // use recursion to deal with the two sub array and so on
         quickSort(arr, low, pi - 1);
         quickSort(arr, pi + 1, high);
     }

 }

int main()
{
int arr[] = {10,3,5,2,656,222};
int n= sizeof(arr)/sizeof(arr[0]);
quickSort(arr, 0,n-1);
for (int i =0;i<n;i++){
	printf("%i\n", arr[i]);
}
     	return 0;
}
