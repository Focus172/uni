// Explain the output of the 10 cout statements in the code given below:
#include <iostream>
using namespace std;
int main() {
  int x(10), y(20), *p, *q;
  p = &x;
  x++;
  q = p;
  cout << "*p = " << *p << endl;
  cout << "*q = " << *q << endl;
  (*q)++;
  y++;
  *q += y;
  y++;
  cout << "x = " << x << endl;
  cout << "*p = " << *p << endl;
  cout << "*q = " << *q << endl;
  p = new int;
  *p = 30;
  ++(*q) += *p;
  p = &x;
  cout << "*p = " << (*p)++ << endl;
  cout << "y = " << y << endl;
  cout << "*q = " << *q << endl;
  int *A = new int[5];
  int z = 3;
  *(A + --z + z--) = --z;
  cout << "z = " << z << endl;
  cout << "A[2] = " << A[2] << endl;
  return 0;
}
