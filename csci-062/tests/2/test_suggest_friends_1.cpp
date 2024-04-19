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
  net.readUsers("example/cycle5.txt");

  for (int i = 0; i < 5; i++) {
    int score;
    vector<int> suggestions = net.suggestFriends(i, score);
    // cout << suggestions.size() << " " << score << endl;
    for (auto v : suggestions) {
      // cout << v << endl;
      return 0;
    }
    assert(suggestions.size() == 2);
    return 0;
  }
  return 0;
}
