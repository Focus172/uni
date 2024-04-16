#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <sstream>
#include "user.h"
#include "network.h"

using namespace std;

int main() {
  char fname[] = "example/users.txt";
  Network network;
  network.readUsers(fname);
  assert(network.numUsers() == 148);
}
