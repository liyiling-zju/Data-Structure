#include <iostream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono>
#include <cmath>
#include <fstream>
using namespace std;

// Define a class to encapsulating the index and value of a number.
class DATA
{
public:
  int index;
  double val;
};


int partition(DATA *arr, int n);

int quicksort(DATA *arr, int n);

int opti_quicksort(DATA *arr, int n);


// Define a print function.
void print(DATA a[], std::string name, int size) {
  std::cout << name << " = [ ";
  for (int i = 0; i < size; i++)
    std::cout << a[i].index << ":" << a[i].val << ", ";
  std::cout << "\b\b]" << std::endl;
}

// 
int stable_opti_quicksort(DATA *arr, int n)
{
  opti_quicksort(arr, n);
  DATA tmp;
  for(int i = 0; i < n-1; i++){
    if(arr[i].val == arr[i+1].val && arr[i].index > arr[i+1].index){
      tmp = arr[i];
      arr[i] =arr[i+1];
      arr[i+1] = tmp;
    }
  }
  return 0;
}



int opti_quicksort(DATA *arr, int n)
{
    if (n > 3)
    {
	int p = partition(arr, n);
	quicksort(arr, p);
	quicksort(arr + p + 1, n - p - 1);
	return 0;
    }
    else
    {
	if (n == 0 || n == 1)
	    return 0;
	else if (n == 2)
	{
	    if (arr[0].val > arr[1].val)
	    {
		DATA tmp = arr[0];
		arr[0] = arr[1];
		arr[1] = tmp;
	    }
	    return 0;
	}
	else if (n == 3)
	{
	    DATA tmp;
	    if (arr[1].val <= arr[0].val && arr[1].val <= arr[2].val)
	    {
		if (arr[0].val <= arr[2].val)
		{
		    tmp = arr[1];
		    arr[1] = arr[0];
		    arr[0] = tmp;
		}
		else
		{
		    tmp = arr[2];
		    arr[2] = arr[0];
		    arr[0] = arr[1];
		    arr[1] = tmp;
		}
	    }
	    else if (arr[2].val <= arr[0].val && arr[2].val <= arr[1].val)
	    {
		if (arr[0].val <= arr[1].val)
		{
		    tmp = arr[0];
		    arr[0] = arr[2];
		    arr[2] = arr[1];
		    arr[1] = tmp;
		}
		else
		{
		    tmp = arr[2];
		    arr[2] = arr[0];
		    arr[0] = tmp;
		}
	    }
	    return 0;
	}
	return -1;
    }
};

int quicksort(DATA *arr, int n)
{
    if (n > 0)
    {
	int p = partition(arr, n);
	quicksort(arr, p);
	quicksort(arr + p + 1, n - p - 1);
    }
    return 0;
};

int partition(DATA *arr, int n)
{
    if (n <= 0)
	return 0;
    int left = 0;
    int right = n - 1;
    DATA pivot = arr[0];
    while (left != right)
    {
	while (arr[right].val >= pivot.val && right > left)
	    right--;
	while (arr[left].val <= pivot.val && right > left)
	    left++;
	if (right > left)
	{
	    DATA tmp = arr[left];
	    arr[left] = arr[right];
	    arr[right] = tmp;
	    right--;
	}
    }
    arr[0] = arr[left];
    arr[left] = pivot;
    return left;
};





#define PI (std::atan(1.0) * 4.0)
#define E (std::exp(1))

int main(int argc, char *argv[])
{
  // A simple test.
  int n1 = 5;
  DATA A[n1];
  //// Assign values to A.
  for(int i = 0; i < n1; i++){
    A[i].index = i;
  }
  A[0].val = PI;
  A[1].val = PI;
  A[2].val = E;
  A[3].val = 0.0;
  A[4].val = 1.0;
  std::cout << "Before: ";
  print(A, "A", n1);
  ////
  stable_opti_quicksort(A, 5);
  std::cout << "After_stable_opti_quicksort: ";
  print(A, "A", n1);
  
  
  /* Generate random sequences 100 times for sorting.
     The rules are:
     1.In every sequence, every random number repeat 10 times;
     2.Generate 100 random sequences to attain average time for every n;
     3.repeat these steps for 10 different n's.
  */
  
  int N[10];
  int n = 100;
  double t[10][100];
  for(int j = 0; j < 10; j++){ // Change the n 10 times
    N[j] = 10*n;
    for(int i = 0; i < 100; i++){
      typedef std::chrono::high_resolution_clock myclock;
      myclock::time_point beginning = myclock::now();
      // Just do something ...
      DATA A[10*n];
      // obtain a seed from the timer
      myclock::duration d = myclock::now() - beginning;
      unsigned seed = d.count();
      std::default_random_engine generator(seed);
      std::uniform_real_distribution<double> dist(0.0, 1.0);
      for(int i1 = 0; i1 < 10*n; i1++){
	A[i1].index = i1;
      }
      for (int j1 = 0; j1 < 10*n; j1 += 10){
	A[j1].val = dist(generator);
	for(int k1 = 1; k1 < 10; k1++)
	  A[j1 + k1].val = A[j1].val;
      }
      //
      myclock::time_point t1 = myclock::now();
      stable_opti_quicksort(A, 10*n);
      myclock::duration t2 = myclock::now() - t1;
      t[j][i] = t2.count();
    }
    n += 100;
  }

  // Compute average time.
  double avt[10];
  for(int i = 0; i < 10; i++){
    for(int j = 0; j< 100; j++)
      avt[i] += t[i][j];
    avt[i] = avt[i]/100;
  }
  // Output average time.
  ofstream outfile1("./data.avt");
  for(int i = 0; i < 10; i++){
    outfile1 << avt[i] << endl;
  }
  outfile1.close();
  // Output n.
  ofstream outfile2("./data.n");
  for(int i = 0; i < 10; i++){
    outfile2 << N[i] << endl;
  }
  outfile2.close();
  
  return 0;
};
