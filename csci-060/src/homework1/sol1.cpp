/// ----------------------- BEGIN HEADER FILE ----------------------------- ///

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <thread>

int main(int argc, char **argv);
int collatz_conjecture(int);


/// ------------------------- END HEADER FILE ----------------------------- ///

/// ------------------------- BEGIN AS_INT.H ------------------------------ ///

#include <cmath>
#include <optional>
#include <string>
#define ASCII_0 48
#define ASCII_9 57

std::optional<int> as_int(std::string *buf) {
  int ret = 0;
  int len = buf->length();
  // HACK: I dont know how to copy in cpp so just make a deref copy
  int pow = *&len - 1;
  for (int i = 0; i < len; i++) {
    char c = buf->at(i);
    if (c < ASCII_0 || c > ASCII_9) {
      return std::nullopt;
    } else {
      ret += (c - ASCII_0) * std::pow(10, pow--);
    }
  }
  return std::optional<int>(ret);
}

/// -------------------------- END AS_INT.H ------------------------------- ///

int main(int argc, char **argv) {
  std::string buf;

  printf("This program is a demonstration of the Collatz conjecture\n");

  while (true) {
    printf("Enter a number (# or 'exit'): ");
    std::cin >> buf;
    if (buf == "exit") {
      return 0;
    } else {
      std::optional<int> i = as_int(&buf);
      if (i.has_value()) {
        collatz_conjecture(i.value());
      } else {
        printf("Invalid Input: %s\n", buf.c_str());
      }
    }
  }
  return 0;
}

int collatz_conjecture(int i) {
  printf("%d ", i);

  if (i <= 0) {
    fprintf(stderr, "\n\nColatz conjecure doesn't converge for x <= 0.\n");
    std::abort();
  } else if (i == 1) {
    printf("\n");
    return 0;
  } else if (i % 2 == 0) {
    return collatz_conjecture(i / 2);
  } else {
    return collatz_conjecture(3 * i + 1);
  }
}

