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

  void addUser(User *);

  /// adds a link between 2 users.
  /// if either doenst returns -1
  int addConnection(std::string s1, std::string s2);
  int deleteConnection(std::string s1, std::string s2);

  int readUsers(char *fname);
  int writeUsers(char *fname);
  int numUsers();

  /// gets the id of the user from the name
  /// returns -1 if the user doesn't exists
  int getId(std::string name);
  User *getUser(int id);

  std::vector<User *> const &getUsers();
};

#endif // !NETWORK_H
