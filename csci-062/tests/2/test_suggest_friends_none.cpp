#include "network.h"
#include "user.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  Network net;
  net.readUsers("example/k4.txt");

  int score;
  vector<int> suggestions = net.suggestFriends(1, score);
  // cout << suggestions.size() << " " << score << endl;
  for (auto v : suggestions) {
    // cout << v << endl;
    return 0;
  }
  assert(suggestions.size() == 0);
  return 0;
}
