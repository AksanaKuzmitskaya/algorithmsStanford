/**
 * inversions.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 * Compute the number of inversions in the given array  with the 100,000 integers 
 * between 1 and 100,000 (inclusive) in some order, with no integer repeated, 
 * where the ith row of the file indicates the ith entry of an array.
 *
 */
 
#include <iostream>
#include <fstream>
using namespace std;

const int SIZE = 100000;
int temp[SIZE] = {0};
long long count = 0;

void sortAndCount(int A[],int start,int end);
void mergeAndCount(int A[], int s1, int e1, int s2, int e2);

int main() {
  int A[SIZE] = {0};
  int number;
  int position = 0;
  
  ifstream fin("IntegerArray.txt");
  
  if (fin.is_open()) {
  cout << "File Opened successfully!!!. Reading data from file into array" << endl;
    while (fin >> number) {
      A[position++] = number;
    }
  } 
  sortAndCount(A, 0, SIZE - 1);
  cout << "Number of inversions - " << count << endl;
  fin.close();
}

void sortAndCount(int A[],int start,int end) {
  int mid;
  if (end > start) {
    mid = (start + end) / 2;
    sortAndCount(A, start, mid);
    sortAndCount(A, mid + 1, end);
    mergeAndCount(A, start, mid, mid + 1, end);
  }
}

void mergeAndCount(int A[], int s1, int e1, int s2, int e2) {
  int index = s1;
  int i = s1;
  int j = s2;
  while (i <= e1 && j <= e2) {
    if (A[i] < A[j]) {
      temp[index++] = A[i++];
    } else {
      temp[index++] = A[j++];
      count += e1 - i + 1;
    }
  }
  while (i <= e1) {
    temp[index++] = A[i++];
  }
  while (j <= e2) {
    temp[index++] = A[j++];
  }
  for (int i = s1; i < index; i++) {
    A[i] = temp[i];
  } 
}
