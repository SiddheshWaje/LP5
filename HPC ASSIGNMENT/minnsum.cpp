#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;

void min_reduction(int arr[], int n) {
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];
	}
  }
  cout << "Minimum value: " << min_value << endl;
}

void average_reduction(int arr[], int n) {
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Average: " << (double)sum / n << endl;
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
  min_reduction(arr, n);
  double endTime = omp_get_wtime();
  printf("This task took %f seconds\n\n", endTime - startTime);
 

  startTime = omp_get_wtime();
  average_reduction(arr, n);
  endTime = omp_get_wtime();
  printf("This task took %f seconds\n\n", endTime - startTime);
  
}