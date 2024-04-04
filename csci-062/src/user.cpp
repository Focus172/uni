#include <set>
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

void User::addFriend(int id) { this->friends_.insert(id); }
void User::deleteFriend(int id) { this->friends_.erase(id); }

int User::getId() { return this->id_; }
std::string User::getName() { return this->name_; }
int User::getYear() { return this->year_; }
int User::getZip() { return this->zip_; }
std::set<int> &User::getFriends() { return this->friends_; }
