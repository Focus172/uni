#include "network.h"
#include "user.h"

#include <algorithm>
#include <bits/types/FILE.h>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

Network::Network() {}

Network::~Network() {
  for (auto user : this->users_) {
    delete user;
  }
}

void Network::addUser(User *user) {
  // TODO: update links in graph
  this->users_.push_back(user);
}

int Network::addConnection(std::string s1, std::string s2) {
  auto pred1 = [s1](User *u) { return u->getName() == s1; };
  auto it1 = std::find_if(this->users_.begin(), this->users_.end(), pred1);

  if (it1 == this->users_.end())
    return -1;

  auto pred2 = [s2](User *u) { return u->getName() == s2; };
  auto it2 = std::find_if(this->users_.begin(), this->users_.end(), pred2);

  if (it2 == this->users_.end())
    return -1;

  User *u1 = *it1;
  User *u2 = *it2;

  u1->addFriend(u2->getId());
  u2->addFriend(u1->getId());

  return 0;
}

int Network::deleteConnection(std::string s1, std::string s2) {
  auto pred1 = [s1](User *u) { return u->getName() == s1; };
  auto it1 = std::find_if(this->users_.begin(), this->users_.end(), pred1);

  if (it1 == this->users_.end())
    return -1;

  auto pred2 = [s2](User *u) { return u->getName() == s2; };
  auto it2 = std::find_if(this->users_.begin(), this->users_.end(), pred2);

  if (it2 == this->users_.end())
    return -1;

  User *u1 = *it1;
  User *u2 = *it2;

  u1->deleteFriend(u2->getId());
  u2->deleteFriend(u1->getId());

  return 0;
}

int Network::getId(std::string name) {
  auto pred = [name](User *u) { return u->getName() == name; };
  auto it = std::find_if(this->users_.begin(), this->users_.end(), pred);

  if (it == this->users_.end())
    return -1;

  User *u = *it;
  return u->getId();
}

// void debug_user(User *u) {
//   std::cout << "User { \n";
//   std::cout << "\tname: " << u->getName() << "\n";
//   std::cout << "\tid: " << u->getId() << "\n";
//   std::cout << "\tzip: " << u->getZip() << "\n";
//   std::cout << "\tyear: " << u->getYear() << "\n";
//   std::cout << "\tlinks: ";
//   for (auto link : u->getFriends()) {
//     std::cout << link << " ";
//   }
//   std::cout << "\n";
//   std::cout << "}" << std::endl;
// }

#define ASCII_ZERO 48

int read_links(FILE *f, std::set<int> &set) {
  bool val_undefined = true;
  int val = 0;
  bool reading_links = true;

  while (reading_links) {
    char c = fgetc(f);
    switch (c) {
    case EOF:
      if (!val_undefined) {
        set.insert(val);
      }
      return EOF;
    case '\n':
      if (!val_undefined) {
        set.insert(val);
      }
      return 1;
    case ' ':
      if (!val_undefined) {
        set.insert(val);
      }
      val = 0;
      val_undefined = true;
      break;
    default:
      int v = c - ASCII_ZERO;
      if (v < 0 || v > 9) {
        // std::cout << "bad part of int literal: " << c << "\n";
        // std::cout << "parsed as literal: " << v << "\n";
        return 0;
      }

      val_undefined = false;
      val *= 10; // 0 * 10 = 0
      val += v;
    }
  }
  return 1;
}

int Network::readUsers(char *fname) {
  int code = EXIT_SUCCESS;

  FILE *f = fopen(fname, "r");
  if (f == NULL) {
    printf("could not open file %s \n", fname);
    return -1;
  }

  int nusers;
  int ret = fscanf(f, "%d", &nusers);
  switch (ret) {
  case EOF:
    code = -1;
    // std::cout << "expected an int found EOF\n";
    goto cleanup;
  case 0:
    code = -1;
    // std::cout << "expected an int found other\n";
    goto cleanup;
  default:
    break;
  }
  this->users_.reserve(nusers + 1);

  for (;;) {
    int id;
    switch (fscanf(f, "%d", &id)) {
    case EOF:
      goto cleanup;
    case 0:
      code = -1;
      goto cleanup;
    }

    char *name = new char[32];
    char *last = new char[32];
    int year;
    int zip;

    int ret = fscanf(f, "\t%31s %31s\n\t%d\n\t%d\n\t", name, last, &year, &zip);

    switch (ret) {
    case EOF:
      // std::cout << "Unexpected EOF in stream.\n";
      code = -1;
      delete[] name;
      delete[] last;
      goto cleanup;
    case 0:
      // std::cout << "Ill formatted file.\n";
      code = -1;
      delete[] name;
      delete[] last;
      goto cleanup;
    }

    std::set<int> links;

    switch (read_links(f, links)) {
    case EOF:
      delete[] name;
      delete[] last;
      goto cleanup;
    case 0:
      delete[] name;
      delete[] last;
      goto cleanup;
    }

    std::string n = std::string(name);
    std::string l = std::string(last);
    User *u = new User(id, n + " " + l, year, zip, links);
    // debug_user(u);
    this->addUser(u);

    delete[] name;
    delete[] last;
  }

cleanup:
  fclose(f);
  return code;
}

int Network::writeUsers(char *fname) {
  std::ofstream f = std::ofstream();
  f.open(fname);
  if (!f.is_open()) {
    return -1;
  }

  f << this->numUsers() << "\n";
  auto users = this->getUsers();
  for (auto user : users) {
    f << user->getId() << "\n";
    f << "\t" << user->getName() << "\n";
    f << "\t" << user->getYear() << "\n";
    f << "\t" << user->getZip() << "\n";
    auto fre = user->getFriends();
    f << "\t";
    for (auto fr : fre) {
      // TODO: this has a trailing white space on last thing
      f << fr << " ";
    }
    f << "\n";
  }

  f.close();
  return 0;
}

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

std::vector<User *> const &Network::getUsers() { return this->users_; }
