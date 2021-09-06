#include <stdio.h>
#include <limits.h>
#include <string.h>

// functions
// hoare
int partition(char *arr[], int left, int right)
{
	 // take the first one as pivot
     char pivot[sizeof(arr[left])];
     //pivot = arr[left];
     strcpy(pivot, arr[left]);
     char tmp[sizeof(arr[left])];
     int l = left;
     int r = right;
     while (l <= r)
     {
         while (strcmp(arr[l], pivot)<0)
           l++;
	 while (strcmp(pivot, arr[r])<0)
		 r--;
	//check if ending case first
	if (l>=r) return r;

	 // if not the ending case, you two should go to the other's group
	strcpy(tmp, arr[l]);
	strcpy(arr[l], arr[r]);
	strcpy(arr[r], tmp);
     }
 }
// recursion function for quickSort process
 void quickSort(char arr[], int low, int high)
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
char arr[][6] = {
"Alice",
"Bobby",
"Beast",
"Flora",
"Elisa"
};

int n= sizeof(arr)/sizeof(arr[0]);
int aux[n];
for (int i=0;i<n;i++){
aux[i] = i;
}	
quickSort(arr, 0,n-1);
for (int i =0;i<n;i++){
	printf("%s\n", arr[i]);
}
     	return 0;
	}
