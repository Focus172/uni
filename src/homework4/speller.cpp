// Write a C++ program to implement a speller. Your program must read two disk
// file names from the keyboard, load a dictionary from the first file into a
// string vector valid, output to the screen the first 20 words (ignoring
// trailing punctuation marks) in the second file that does not appear in the
// dict, without repetition.

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>

void strip_punct(std::string &);
bool is_ascii_character(char);

int main(int argc, char **argv) {
  std::string dict_file;
  std::string inpt_file;

  printf("Choose the file to use as input: \n");
  std::cin >> inpt_file;

  printf("Choose the file to use as dictionary: \n");
  std::cin >> dict_file;

  std::ifstream f;
  f.open(dict_file);
  if (f.fail()) {
    printf("Failed to open dictionary file (%s).\n", dict_file.c_str());
    return EXIT_FAILURE;
  }

  std::unordered_set<std::string> dict{};

  std::string buf;
  while (getline(f, buf)) {
    // strip_punct(buf);
    dict.insert(buf);
    buf.clear();
  }
  f.close();

  std::unordered_set<std::string> found{};

  f.open(inpt_file);
  if (f.fail()) {
    printf("Failed to open dictionary file (%s).", dict_file.c_str());
    return EXIT_FAILURE;
  }

  while (f.is_open()) {
    f >> buf;
    strip_punct(buf);
    if (dict.count(buf) == 1) {
      if (found.count(buf) == 0) {
        std::cout << buf << std::endl;
        found.insert(buf);
      }

      if (found.size() >= 20) {
        break;
      }
    }
  }
  f.close();

  return EXIT_SUCCESS;
}

void strip_punct(std::string &buf) {
  while (buf.size() > 0) {
    if (!is_ascii_character(buf.back())) {
      buf.pop_back();
    } else {
      return;
    }
  }
}
#define ASCII_UPPER_A 65
#define ASCII_UPPER_Z 90
#define ASCII_LOWER_A 97
#define ASCII_LOWER_Z 122

bool is_ascii_character(char c) {
  return (c >= ASCII_LOWER_A && c <= ASCII_LOWER_Z) ||
         (c >= ASCII_UPPER_A && c <= ASCII_UPPER_Z);
}
