#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

void max_reduction(int arr[], int n) {
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i];
	}
  }
  cout << "Maximum value: " << max_value << endl;
}


void sum_reduction(int arr[], int n) {
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
}


int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    arr=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>arr[i];
    }

 
  double startTime = omp_get_wtime();
  max_reduction(arr, n);
  double endTime = omp_get_wtime();
  printf("This task took %f seconds\n\n", endTime - startTime);
 
  startTime = omp_get_wtime();
  sum_reduction(arr, n);
  endTime = omp_get_wtime();
  printf("This task took %f seconds\n\n", endTime - startTime);
  
}
