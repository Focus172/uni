// You are given an array of sorted integers. Find the N closest
// (difference is minimum) numbers to a given integer X. Assume X is always
// given in the array.
//
// For example:
//
// CASE_1: Input: N = 4, X = 35
//                arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
//                Output: 30 39 42 45
//
// CASE_2: Input: N = 3, X = 16
//                arr[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56}
//                Output: 12 22 30
//
//
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <vector>

class slice {
public:
  int *str;
  int *end;

  slice(int *str, int *end) {
    this->str = str;
    this->end = end;
  }
};

void p2(slice arr, int x, size_t n) {
  int *value;
  int *low;
  int *hii;

  // find the value and point value to it.
  // then point low and high to it.
  //
  // while the difference in point length is less than
  value = std::find(arr.str, arr.end, x);

  if (value == nullptr) {
    std::cout << "invaiants failed";
    exit(1);
  }

  low = value;
  hii = value;

  // match 1 more beacuse the value itself is ignored
  while (hii - low < n + 1) {
    if (low - 1 < arr.str) {
      // if there are no more nodes at the start
      if (hii + 1 > arr.end) {
        // there are no more nodes any where.
        // this should be a panic but we just break out instead
        break;
      } else {
        hii += 1;
      }
    } else {
      // if there are nodes at the start
      if (hii + 1 > arr.end) {
        // there are no nodes at the end
        low -= 1;
      } else {
        // there are nodes at the start and end. Most likely path
        if (x - *(low - 1) < *(hii + 1) - x) {
          // low is closer than high
          low -= 1;
        } else {
          // high is closer than low or they are equal
          hii += 1;
        }
      }
    }
  }
  slice res{low, hii};

  for (auto p = res.str; p != res.end; p++) {
    if (*p != x) {
      std::cout << *p << " ";
    }
  }
  std::cout << "\n";
}

#ifndef NO_MAIN
int main(int argc, char *argv[]) {
  std::cout << "Program was built as a binary. Running tests." << std::endl;

  // CASE_1: Input: N = 4, X = 35
  int arr1[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
  // Output: 30 39 42 45
  p2(slice{arr1, arr1 + 13}, 35, 4);

  // CASE_2: Input: N = 3, X = 16
  int arr2[] = {12, 16, 22, 30, 35, 39, 42, 45, 48, 50, 53, 55, 56};
  // Output: 12 22 30
  p2(slice{arr2, arr2 + 13}, 16, 3);

  return 0;
}
#endif // !NO_MAIN
