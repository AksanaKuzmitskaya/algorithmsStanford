/**
 * closestpair.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 *O(n log n) Algorithm for Closest Pair
 *
 */
 
#include <math.h>
#include <cmath>
#include <iostream>
#include <float.h>
using namespace std;

const int SIZE = 6;

struct Point {
  int x, y;
};

Point temp[SIZE] = {{0, 0}};

float p_distance(Point p1, Point p2) {

  return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}

bool isLess(const Point &p1, const Point &p2, bool useX) {
  if (useX)
    return p1.x < p2.x;
  else 
    return p1.y < p2.y;
}

void sort(Point points[], int start, int end, bool useX);
void merge(Point points[], int s1, int e1, int s2, int e2, bool useX);
float closestPair(Point pointsX[], Point pointsY[], int size);
float min(float d1, float d2);
float closest(Point points[], int size);
float bruteForce(Point points[], int size);
float closestSplitPair(Point points[], int size, float d);

int main() {
  Point points[SIZE] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
  float minDistance = closest(points, SIZE);
  cout << "The smallest distance is - " << minDistance << endl;
}

void sort(Point points[], int start, int end, bool useX) {
  if (start < end) {
     int mid = (start + end) / 2;
     sort(points, start, mid, useX);
     sort(points, mid + 1, end, useX);
     merge(points, start, mid, mid + 1, end, useX);
  }
}

void merge(Point points[], int s1, int e1, int s2, int e2, bool useX) {
  int index = s1;
  int i = s1;
  int j = s2;  
  while (i <= e1 && j <= e2) {
    if (isLess(points[i], points[j], useX)) {
      temp[index] = points[i];
      ++i;
    }
    else {
      temp[index] = points[j];
      ++j;
    }
    ++index;
  }
  while (i <= e1) {
    temp[index] = points[i];
    ++i;
    ++index;
  }
  while (j <= e1) {
    temp[index] = points[i];
    ++j;
    ++index;
  }
  for (int i = s1; i < index; ++i) {
    points[i] = temp[i];
  }
}

float closestPair(Point pointsX[], Point pointsY[], int size) {
  if (size <= 3)
    return bruteForce(pointsX, size);
    
  int mid = size / 2; 
  Point midPoint = pointsX[mid];
  
  Point pointsYLeft[mid + 1];
  Point pointsYRight[size - mid - 1];
  int index_l = 0, index_r = 0;  
  for (int i = 0; i < size; ++i) {
    if (pointsY[i].x <= midPoint.x) {
      pointsYLeft[index_l] = pointsY[i];
      ++index_l;
    }
    else {
      pointsYRight[index_r] = pointsY[i];
      ++index_r;
    }
  }
  
  float d_l = closestPair(pointsX, pointsYLeft, mid);
  float d_r = closestPair(pointsX + mid, pointsYRight, size - mid);
  
  float d = min(d_l, d_r);
  
  Point points[size];
  int index = 0;
  for (int i = 0; i < size; ++i) {
    if (abs(pointsY[i].x - midPoint.x) < d) {
     points[index] = pointsY[i];
     ++index;
   }
  }
  
  return min(d, closestSplitPair(points, index, d));
}

float min(float d1, float d2) {
  if (d1 < d2)
    return d1;
  else
    return d2;
}

float closest(Point points[], int size) {
  Point pointsX[size];
  Point pointsY[size];
  for (int i = 0; i < size; ++i) {
    pointsX[i] = points[i];
    pointsY[i] = points[i];
  }
  sort(pointsX, 0, size - 1, true);
  sort(pointsY, 0, size - 1, false);
  
  return closestPair(pointsX, pointsY, size);
}

float bruteForce(Point points[], int size) {
  float min = FLT_MAX;
  float dist; 
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size; ++j) {
      dist = p_distance(points[i], points[j]);
      if (min > dist)
        min = dist;
    }
  }
  
  return min;
}

float closestSplitPair(Point points[], int size, float d) {
  float min = d;
  int dist;
  for (int i = 0; i < size; ++i) {
    for (int j = i + 1; j < size && (points[j].y - points[i].y) < min; ++j) {
      dist = p_distance(points[i], points[j]);
      if (min > dist)
        min = dist;
    }
  }
  
  return min;
} 
