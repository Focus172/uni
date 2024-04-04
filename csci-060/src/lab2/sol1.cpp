// --------------- #include "../as_int.h" -----------------------//

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

// --------------- end header "../as_int.h" ---------------------//

#include <iostream>

/// Reads an integer between 1 and 4 inclusive and outputs First Year, Sophomore,
/// Junior, or Senior respectively, or Error if the input is out of range.
int main(int argc, char *argv[]) {
  std::string buf;
  printf("Enter a number 1-4: ");
  std::cin >> buf;

  auto option = as_int(&buf);
  if (option.has_value()) {
    int i = option.value();

    switch (i) {
    case 1:
      printf("First Year\n");
      break;
    case 2:
      printf("Sophomore\n");
      break;
    case 3:
      printf("Sophomore\n");
      break;
    case 4:
      printf("Senior\n");
      break;
    default:
      printf("Error!\n");
      break;
    }
  } else {
    printf("Error!\n");
  }
  return 0;
}
