#include <algorithm>
#include <iterator>
#include <set>
#include <sstream>
#include <string>

#include "user.h"

User::User() { *this = User(0, "", 0, 0, {}); }

User::User(int id, std::string name, int year, int zip, std::set<int> friends) {
  this->id_ = id;
  this->name_ = name;
  this->year_ = year;
  this->zip_ = zip;
  this->friends_ = friends;
}

User::~User() {
  for (Post *post : this->messages_) {
    delete post;
  }
}

void User::addFriend(int id) { this->friends_.insert(id); }
void User::deleteFriend(int id) { this->friends_.erase(id); }

int User::getId() { return this->id_; }
std::string User::getName() { return this->name_; }
int User::getYear() { return this->year_; }
int User::getZip() { return this->zip_; }
std::set<int> &User::getFriends() { return this->friends_; }

void User::addPost(Post *post) { this->messages_.push_back(post); }
std::vector<Post *> User::getPosts() { return this->messages_; }

std::string User::getPostsString(int howMany, bool showOnlyPublic) {
  std::stringstream buf;

  int i = 0;
  for (auto it = this->messages_.rbegin(); it != this->messages_.rend(); it++) {
    if (i == howMany)
      break;

    Post *msg = *it;

    if (showOnlyPublic && !msg->getIsPublic()) {
      continue;
    }

    if (i != 0) {
      buf << "\n\n";
    }

    buf << msg->toString();

    i += 1;
  }

  return buf.str();
}
