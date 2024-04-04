// Write a C++ Program to design an efficient way for the following scenario:
//
// Ross is grading papers this quarter. Each student can have either one or
// multiple answer sheets. So Ross records the following:
//
// X and Y, which indicates that the marks Y is to be added to the student
// whose name is X. X is a string representing name of the student followed by
// the first initial of their last name. Y is an integer representing the
// score. (See example below)
//
// Each X and Y pair is taken as input from user. For simplicity you can assume
// the number of entries to be any value greater than 2.
//
// Finally after all the records have been entered, Ross wants to view the
// scores and the student names sorted *lowest to highest by score*. [Assume
// that two students can have the same score].

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

using std::map;
using std::pair;
using std::string;
using std::vector;

// comparator function
struct comp {
  bool operator()(const pair<string, uint32_t> &lhs,
                  const pair<string, uint32_t> &rhs) const {
    return lhs.second < rhs.second;
  }
};

int main(int argc, char *argv[]) {
  // TODO: vector is likely fast for small inputs, which is expected for this
  // problem
  map<string, uint32_t> m;
  // vector<pair<string, uint32_t>> m;

  string buf;
  while (std::cin >> buf) {
    uint32_t val;
    std::cin >> val;

    auto ref = m.find(buf);

    if (ref != m.end()) {
      ref->second += val;
    } else {
      m[buf] = val;
    }
  }

  vector<pair<string, uint32_t>> scores;
  for (auto iter = m.begin(); iter != m.end(); ++iter) {
    scores.push_back(*iter);
  }

  std::sort(scores.begin(), scores.end(), comp());

  for (auto iter = scores.begin(); iter != scores.end(); ++iter) {
    std::cout << iter->first << " - " << iter->second << std::endl;
  }

  return 0;
}
