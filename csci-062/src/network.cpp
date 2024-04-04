
#include "network.h"
#include "user.h"

#include <algorithm>
#include <vector>

Network::Network() {
    // this->users_ = {};
}

void Network::addUser(User *user) {
  // TODO: update links in graph
  this->users_.push_back(user);
}

// TODO:
int Network::addConnection(std::string s1, std::string s2) { return 0; }
// TODO:
int Network::deleteConnection(std::string s1, std::string s2) { return 0; }

// TODO:
int Network::getId(std::string name) { 
    return 0; 
}

// TODO:
int Network::readUsers(char *fname) { return 0; }
// TODO:
int Network::writeUsers(char *fname) { return 0; }

int Network::numUsers() { return this->users_.size(); }

User *Network::getUser(int id) {
  auto pred = [id](User *u) { return u->getId() == id; };

  auto it = std::find_if(this->users_.begin(), this->users_.end(), pred);
  if (it == this->users_.end()) {
    return nullptr;
  } else {
    return *it;
  }
}
