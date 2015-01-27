 /**
 * numberofcomparisons.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 * Compute the total number of comparisons used to sort the given input file by QuickSort,
 * using three different pivoting rules (first element, last element and median betwean first, middle and last element). 
 *
 */
 
 #include <iostream>
 #include <fstream>
using namespace std;

const int SIZE = 10000;
long long count = 0;

int partition(int *A, int start, int end);
void quickSort(int *A, int start, int end); 

int main() {
  int A[SIZE] = {0};
  int number;
  int position = 0;  
  ifstream fin("QuickSort.txt");  
  if (fin.is_open()) {
  cout << "File Opened successfully!!!. Reading data from file into array" << endl;
    while (fin >> number) {
      A[position++] = number;
    }
  } 
  quickSort(A, 0, SIZE - 1);
  cout << count << endl;
  fin.close();
} 

// pivot - first element in the array
int partition(int *A, int start, int end) {
  int pivot = A[start];
  int p_index = start + 1;
  for (int i = start + 1; i <= end; ++i) {
    if(A[i] < pivot) { 
      swap(A[i], A[p_index++]);
    }
  }
  swap(A[start], A[--p_index]);
  count += end - start;
  return p_index;
}

// pivot - last element in the array
int partition(int *A, int start, int end) {
  swap(A[end], A[start]);
  int pivot = A[start];
  int p_index = start + 1;
  for (int i = start + 1; i <= end; ++i) {
    if(A[i] < pivot) { 
      swap(A[i], A[p_index++]);
    }
  }
  swap(A[start], A[--p_index]);
  count += end - start;
  return p_index;
}

// pivot - median from first, middle and last element in the array
int partition(int *A, int start, int end) {
  int mid = (start + end) / 2;
  int pivot_s = A[start];
  int pivot_e = A[end];
  int pivot_m = A[mid];
  if ((pivot_e < pivot_s && pivot_e > pivot_m) || (pivot_e < pivot_m && pivot_e > pivot_s))
    swap(A[start], A[end]);
  else if ((pivot_m < pivot_e && pivot_m > pivot_s) || (pivot_m < pivot_s && pivot_m > pivot_e))
    swap(A[start], A[mid]);
  int pivot = A[start];
  int p_index = start + 1;
  for (int i = start + 1; i <= end; i++) {
    if(A[i] < pivot) { 
      swap(A[i], A[p_index++]);
    }
  }
  swap(A[start], A[--p_index]);
  count += end - start;
  return p_index;
}

void quickSort(int *A, int start, int end) {
  if (start < end) {
    int p_index = partition(A, start, end);
    quickSort(A, start, p_index - 1);
    quickSort(A, p_index + 1, end);
  }
}
