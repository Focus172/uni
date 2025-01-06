#include "network.h"
#include "post.h"
#include "user.h"

#include <algorithm>
#include <assert.h>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>

/*
void debug_user(User *u) {
  std::cout << "User { \n";
  std::cout << "\tname: " << u->getName() << "\n";
  std::cout << "\tid: " << u->getId() << "\n";
  std::cout << "\tzip: " << u->getZip() << "\n";
  std::cout << "\tyear: " << u->getYear() << "\n";
  std::cout << "\tlinks: ";
  for (auto link : u->getFriends()) {
    std::cout << link << " ";
  }
  std::cout << "\n";
  std::cout << "}" << std::endl;
}
*/

Network::Network() {}

Network::~Network() {
  for (auto user : this->users_) {
    delete user;
  }
}

void Network::addUser(User *user) { this->users_.push_back(user); }

int Network::addConnection(std::string s1, std::string s2) {
  auto it1 = std::find_if(this->users_.begin(), this->users_.end(),
                          [&](User *u) { return u->getName() == s1; });

  if (it1 == this->users_.end())
    return -1;
  User *u1 = *it1;

  auto it2 = std::find_if(this->users_.begin(), this->users_.end(),
                          [&](User *u) { return u->getName() == s2; });

  if (it2 == this->users_.end())
    return -1;
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

/* ******************** READ HELPERS *********************** */
#define ASCII_ZERO 48

int read_csv_int(FILE *f, int &val) {
  val = 0;
  for (;;) {
    char c = fgetc(f);
    switch (c) {
    case EOF:
      return EOF;
    case ',':
      return 1;
    default:
      int v = c - ASCII_ZERO;
      if (v < 0 || v > 9) {
        printf("bad int literal: '%c'\n"
               "parsed as: %d\n",
               c, v);
        return 0;
      }

      val *= 10; // 0 * 10 = 0
      val += v;
    }
  }
}

int read_csv_name(FILE *f, std::string &val) {
  for (;;) {
    char c = fgetc(f);
    switch (c) {
    case EOF:
      return EOF;
    case ',':
    case '\n':
      return 1;
    default:
      val.push_back(c);
      break;
    }
  }
}

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
/* ********* END READ HELPERS *********************** */

int Network::read_users_csv(const char *fname) {
  auto f = fopen(fname, "r");
  if (!f) {
    printf("cant open file: %s\n", fname);
    return -1;
  }

  for (;;) {
    int r;
    int id = 0;
    r = read_csv_int(f, id);
    if (r == EOF)
      return 0;
    if (r == 0)
      return -1;
    // printf("got id: %d\n", id);

    std::string name;
    if (!read_csv_name(f, name))
      return -1;
    // printf("got name: %s\n", name.c_str());

    int year;
    if (!read_csv_int(f, year))
      return -1;
    // printf("got year: %d\n", year);

    int zip;
    if (!read_csv_int(f, zip))
      return -1;
    // printf("got zip: %d\n", zip);

    std::set<int> links;
    if (!read_links(f, links))
      return -1;
    // printf("got links: ");
    // for (auto l : links) { printf("%d ", l); }
    // printf("\n");
    //
    User *u = new User(id, name, year, zip, links);
    this->addUser(u);
  }

  return 0;
}

int Network::write_users_csv(const char *fname) {
  std::ofstream f = std::ofstream();
  f.open(fname);
  if (!f.is_open()) {
    printf("cant open file: %s\n", fname);
    return -1;
  }

  for (auto u : this->users_) {
    f << u->getId() << ",";
    f << u->getName() << ",";
    f << u->getYear() << ",";
    f << u->getZip() << ",";
    auto friends = u->getFriends();
    for (auto fr : friends) {
      f << fr << " ";
    }
    f << "\n";
  }
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

/// TODO: impl
std::vector<int> Network::suggestFriends(int who, int &score) {
  User *u = this->getUser(who);
  if (!u) {
    score = -1;
    return {};
  }

  auto friends = u->getFriends();

  std::vector<int> ret = {};

  auto users = this->getUsers();
  for (User *user : users) {
    if (user->getId() == who || friends.find(user->getId()) != friends.end()) {
      continue;
    }

    auto fr = user->getFriends();
    int c = std::count_if(fr.begin(), fr.end(), [&](int id) {
      return friends.find(id) != friends.end();
    });

    if (c >= score) {
      if (c > score) {
        score = c;
        ret.clear();
      }
      ret.push_back(user->getId());
    }
  }

  return ret;
}

/// TODO: more test
std::vector<std::vector<int>> Network::groups() {
  // a list of people who have already been checked
  std::set<int> social = {};
  std::vector<std::vector<int>> groups = {};

  auto us = this->getUsers();
  for (User *u : us) {
    int this_id = u->getId();

    if (social.find(this_id) != social.end()) {
      continue;
    }

    auto fr = u->getFriends();
    bool is_group = std::all_of(fr.begin(), fr.end(), [&](int friend_id) {
      User *f = this->getUser(friend_id);
      if (!f) {
        return false;
      }

      // check that all of the friends of friends are also friends of this user
      auto fof = f->getFriends();
      return std::all_of(fof.begin(), fof.end(), [&](int id) {
        return std::find(fr.begin(), fr.end(), id) != fr.end() || id == this_id;
      });
    });

    // if it is a group add it to the list
    if (is_group) {
      std::vector<int> v(fr.begin(), fr.end());
      groups.push_back(v);
      groups.back().push_back(this_id);
    }

    // either way, add them all to the seen
    for (auto dfghj : fr) {
      social.insert(dfghj);
    }
    social.insert(this_id);
  }

  // printf("=== groups\n");
  // int i = 1;
  // for (auto g : groups) {
  //   printf("group %d: ", i);
  //   for (int id : g) {
  //     printf("%d ", id);
  //   }
  //   printf("\n");
  //   i += 1;
  // }

  return groups;
}

std::string Network::getPostsString(int ownerId, int howMany,
                                    bool showOnlyPublic) {
  User *u = this->getUser(ownerId);

  if (u == nullptr)
    return "";

  return u->getPostsString(howMany, showOnlyPublic);
}

int Network::read_posts_csv(const char *fname) {
  auto f = fopen(fname, "r");
  if (!f) {
    printf("cant open file: %s\n", fname);
    return -1;
  }

  for (;;) {
    // 2: messageId_0
    // in
    int id;
    int ret = read_csv_int(f, id);
    if (ret == EOF)
      break;
    // printf("got id: %d\n", id);

    std::string msg = "";
    read_csv_name(f, msg);
    // printf("got msg: %s\n", msg.c_str());

    int owner;
    read_csv_int(f, owner);
    // printf("got owner: %d\n", owner);

    int likes;
    read_csv_int(f, likes);
    // printf("got likes: %d\n", likes);

    int pub = -1;
    read_csv_int(f, pub);
    // printf("got pub: %d\n", pub);

    std::string sender = "";
    read_csv_name(f, sender);
    // printf("got sender: %s\n", sender.c_str());

    User *u = this->getUser(owner);
    if (u == nullptr) {
      continue;
    }
    if (pub < 0) {
      Post *p = new Post(id, owner, msg, likes);
      u->addPost(p);
    } else {
      bool publ = pub == 1 ? true : false;
      Post *p = new IncomingPost(id, owner, msg, likes, publ, sender);
      u->addPost(p);
    }
  }

  fclose(f);
  return 0;
}

int Network::write_posts_csv(const char *fname) {
  return 0;
  std::ofstream f = std::ofstream();
  f.open(fname);
  if (!f.is_open()) {
    printf("cant open file: %s\n", fname);
    return -1;
  }

  for (User *user : this->users_) {
    for (Post *post : user->getPosts()) {
      f << post->getMessageId() << ",";
      f << post->getMessage() << ",";
      f << post->getOwnerId() << ",";
      for (auto id : post->getLiked()) {
        f << id << " ";
      }
      f << ",";

      IncomingPost *ip = dynamic_cast<IncomingPost *>(post);
      if (ip == nullptr) {
        f << ",";
      } else {
        f << ip->getIsPublic() << ",";
        f << ip->getAuthor();
      }
      f << "\n";
      // f << "\n";
    }
  }
  return 0;
}
