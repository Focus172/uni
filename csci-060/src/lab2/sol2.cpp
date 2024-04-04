#include <iostream>

/// Program outputs the product of all integers between 1 and 100 inclusive
/// that are divisible by 3, or divisible by 5, but not by both.
int main(int argc, char **argv) {
  int x = 1;

  for (int i = 1; i <= 50; i++) {
    if (i % 5 == 0) {
      if (i % 3 != 0) {
        x = x * i;
      }
    } else if (i % 3 == 0) {
      x = x * i;
    }
  }
  std::cout << x << std::endl;
  return EXIT_SUCCESS;
}
