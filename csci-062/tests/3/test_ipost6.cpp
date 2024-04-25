#include "post.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  IncomingPost p1(0, 1, "hi", 2, true, "Lillie Cain");
  // cout <<p1.toString()   << endl;
  // cout <<p1.toString().substr(0,18)   << endl;
  assert(p1.toString().substr(0, 18) == "Lillie Cain wrote:");

  IncomingPost p2(0, 1, "hi", 2, false, "Lillie Cain");
  assert(p2.toString().find("(private)") != std::string::npos);
}
