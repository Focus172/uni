#include <iostream>
using namespace std;

int main() {
  // allocates memory with uninitialized data
  int *pa = new int[5];
  // a pointer offset of 2 from the start of the array
  int *pm = pa + 2;
  // index 1 and 3 are initalized 1
  *(pm - 1) = *(pm + 1) = 1;
  // index 0 is initalized to 3
  *pa = 3;
  // index 2 is set to the value at index 0 (3) plus 1 also known as 4
  *pm = *pa + 1;
  // the value at index 4 is set to 5
  pa[4] = 5;

  // the array is iterated over and the values printed
  for (int i = 0; i < 5; ++i)
    cout << pa[i] << " ";
  cout << endl;
  // outputs:
  // '3 1 4 1 5 '

  // the memory allocated is freed
  delete[] pa;

  return 0;
}
