
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
