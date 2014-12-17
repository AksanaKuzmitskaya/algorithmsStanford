#include <iostream>
using namespace std;

int num_of_1(long long x) {
  int sum = 0;
  long long y;
  while (x != 0) {
    y = x & ~(x - 1);
    x ^= y;
    sum++;
  }
  return sum;
}

short parity(long long x) {
  return (num_of_1(x) & 1);
}

int main() {
  long long y = 9223372036854775806;
  cout << parity(y) << endl;
}
