# Lab 7

### First
The first thing prints out the value the p points to. p is a ref to x which is
10 but changed to 11. So this outputs 11.

### Second
q is a ref to the same data as p (x) so it also outputs x when
derefed.

### Third
This statement outputs x, which is incremented once through a ref then
has y (21) added to it through a ref. The value of x is 33 which is what is
printed.

### Fourth
p still points to the same data so it outputs 33 when derefed.

### Fifth
The same as the above holds of q so it also outputs 33.

### 6th
x has 30 added to it and then 1 is added. After leaking some memory for fun, p
is set back to ref to x. p is printed then incremented. The value of x
is output or 64

## 7th
y has only incremented by one since it was last used so it is printed as 22.

### 8th
q is still a reference to x but the incremented from p has resolved no so it
prints 65.

### 9th
z is set to 3 and then is subtracted from 3 times in the line before it is
printed. Therefore, it prints 0.

### 10th
The right hand side of the equation is evaluated first so z is made 2 and it is
returned and is assigned to the address of A offset by 1 twice. This means that
when it A\[2\] is assigned to 2.

# Code
```cpp
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
```
