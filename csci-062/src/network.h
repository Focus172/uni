#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>

class Network {
private:
  std::vector<User *> users_;

public:
  Network();
  ~Network();

  /// pre: pointer is non-null and unique
  /// post: the user is added
  void addUser(User *);

  /// pre: none
  /// post: a link between 2 users is added if either doesn't returns -1
  int addConnection(std::string s1, std::string s2);
  /// pre: none
  /// post: a link between 2 users is deleted if either doesn't returns -1
  int deleteConnection(std::string s1, std::string s2);

  /// pre: fname is a non-null string
  /// post: the network reads in users from the file. returns -1 if file
  ///       doesnt exists or is ill formatted
  int readUsers(char *fname);
  /// pre: fname is a non-null string
  /// post: attempts to write users to the given file name creating it if needed
  ///       returns -1 if file could not be opened
  int writeUsers(char *fname);
  /// pre: none
  /// post: returns the number user
  int numUsers();

  /// pre: none
  /// post: gets the id of the user by name. returns -1 if the user doesn't
  ///       exists
  int getId(std::string name);
  /// pre: none
  /// post: gets pointer to a user from a given id. returns null if there is no
  ///       such user. pointer is valid until next call to `addUser` or
  ///       `readUsers`
  User *getUser(int id);

  /// pre: none
  /// post: gets an inmutable reference to the users of this network
  std::vector<User *> const &getUsers();

  /// TODO: DOCS
  std::vector<int> shortestPath(int from, int to);

  /// TODO: DOCS
  std::vector<int> distanceUser(int from, int &to, int distance);

  /// TODO: DOCS
  std::vector<int> suggestFriends(int who, int &score);

  /// TODO: DOCS
  std::vector<std::vector<int>> groups();
};

#endif // !NETWORK_H
