#ifndef USER_H
#define USER_H

#include <set>
#include <string>

class User {
private:
  int id_;
  std::string name_;
  int year_;
  int zip_;
  std::set<int> friends_;

public:
  /// pre: none
  /// post: a user is constructed
  User();
  /// pre: id is unique and friends only contains other valid id
  /// post: a user is constructed
  User(int id, std::string name, int year, int zip, std::set<int> friends);

  /// pre: id represents a valid user
  /// post: the friend is added
  void addFriend(int id);
  /// pre: none
  /// post: the friend is deleted if it exists
  void deleteFriend(int id);

  /// pre: none
  /// post: returns this users id
  int getId();
  /// pre: none
  /// post: returns this users name
  std::string getName();
  /// pre: none
  /// post: returns this users year
  int getYear();
  /// pre: none
  /// post: returns this users zip
  int getZip();
  /// pre: none
  /// post: returns this users friends
  std::set<int> &getFriends();
};

#endif // USER_H
