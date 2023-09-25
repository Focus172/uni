/// ----------------------- BEGIN HEADER FILE ----------------------------- ///

#include <cmath>
#include <cstdio>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>
#include <thread>

int main(int argc, char **argv);

void print_multiplication_table(int);
std::optional<int> as_int(std::string *);

#define ASCII_0 48
#define ASCII_9 57

/// ------------------------- END HEADER FILE ----------------------------- ///

int main(int argc, char *argv[]) {
  std::string buf;

  printf("This program prints out multiplication tables with the width you input.\n");

  while (true) {
    std::cout << "Enter a number (# or 'exit'): ";
    std::cin >> buf;
    if (buf == "exit") {
      return 0;
    } else {
      std::optional<int> i = as_int(&buf);
      if (i.has_value()) {
        print_multiplication_table(i.value());
      } else {
        printf("Invalid Input: %s\n", buf.c_str());
      }
    }
  }
  return 0;
}

void print_multiplication_table(int i) {

  /// Returns the amount of character that the max value in the multiplication
  /// table takes up in base 10 notation
  int prod = i * i;
  int max_len = 0;
  while (prod != 0) {
    max_len++;
    prod /= 10;
  }

  for (int r = 1; r <= i; r++) {
    for (int c = 1; c <= i; c++) {
      // HACK: uses max len as the spaces inserted within 1 format
      printf("%*d ", max_len, r * c);
    }
      printf("\n");
  }
}

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
