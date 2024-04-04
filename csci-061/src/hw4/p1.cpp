// Write a C++ program that uses search concepts discussed in class to find a
// 'Joey' element! What is a 'Joey' element you ask? A Joey element in an array
// of n integers (no duplicates) is an element X such that
// a[X] = X.
//
// For example:
//
// int a[] = {1,5,2,6,7,3}, a[2] = 2 --> 2 is a 'Joey' element! :)
//
// int b[] = {1,2,3,8,9} --> No 'Joey' element!

#include <cstddef>
#include <iostream>

#define SIZE(x) (sizeof(x) / sizeof((x)[0]))

void find_joey(int v[], size_t len);

void find_joey(int v[], size_t len) {
  for (int i = 0; i < len; i++) {
    if (i == v[i]) {
      std::cout << "2 is a 'Joey' element! :)" << std::endl;
      return;
    }
  }
  std::cout << "No 'Joey' element!" << std::endl;
  return;
}

#ifndef NO_MAIN
int main(int argc, char *argv[]) {
  std::cout << "Program was built as a binary. Running tests." << std::endl;

  int a[] = {1, 5, 2, 6, 7, 3};
  find_joey(a, 6);

  int b[] = {1, 2, 3, 8, 9};
  find_joey(b, 5);

  return 0;
}
#endif // !NO_MAIN
