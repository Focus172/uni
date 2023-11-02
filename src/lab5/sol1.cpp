// Week 5 - Assignment
// Write a program that does the following:
// - Reads data from a file “input.txt”.
// - Stores the data into a vector.
// - Writes it to a file “output.txt” with the order of the lines is reversed.

// As extra:
// - The order of the words within each line is also reversed.

#include <fstream>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using std::vector;

int main() {
  std::ifstream f;
  // Open a file for reading
  f.open("src/lab5/input.txt");
  if (f.fail()) {
    std::cout << "Failed to open the input file." << std::endl;
    return 1;
  }
  // Read data from the input file one line at a time
  std::string line;
  std::vector<std::string> fileContents;

  while (getline(f, line)) {
    // Write each line to the output file
    // Write each line to the output file
    fileContents.push_back(line);
  }

  f.close();

  std::ofstream out;
  // Open a file for writing
  out.open("src/lab5/output.txt");
  if (out.fail()) {
    std::cout << "Failed to open the output file." << std::endl;
    return 2;
  }

  while (fileContents.size() > 0) {
    auto l = fileContents.back();
    out << l << std::endl;
    fileContents.pop_back();
  }

  out.close();
  return 0;
}
