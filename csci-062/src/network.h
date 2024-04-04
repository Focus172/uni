#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <vector>

class Network {
private:
  std::vector<User *> users_;

public:
  Network();

  void addUser(User *);

  int addConnection(std::string s1, std::string s2);
  int deleteConnection(std::string s1, std::string s2);

  int getId(std::string name);

  int readUsers(char *fname);
  int writeUsers(char *fname);
  int numUsers();

  User *getUser(int id);
};

#endif // !NETWORK_H
