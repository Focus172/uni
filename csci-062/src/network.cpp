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
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <utility>

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

struct node {
  /// this nodes id
  int id;
  /// node that this came from
  int pr;
  /// number of step it took to get here
  int dp;
};

void debug_node(node *n, char const *name) {
  printf("%s {\n"
         "  id: %d\n"
         "  pr: %d\n"
         // "  dp: %d\n"
         "} node *;\n",
         name, n->id, n->pr
         // n->dp
  );
}

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
      return code;
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

/// TODO: better tests
std::vector<int> Network::shortestPath(int from, int to) {
  if (to == from) {
    return {to};
  }

  std::vector<node> seen = std::vector<node>{node{from, -1}};

  int i = 0;

  bool found = false;

  while (!found && i < seen.size()) {
    node &node = seen[i];
    int p_id = node.id;

    User *u = this->getUser(node.id);
    auto friends = u->getFriends();
    for (auto id : friends) {
      if (id == to) {
        struct node n = {id, p_id};
        seen.push_back(n);
        found = true;
        break;
      }
      if (id == u->getId()) {
        continue;
      }

      // check if the thing exists
      auto it = std::find_if(seen.begin(), seen.end(),
                             [id](struct node &n) { return n.id == id; });

      if (it == seen.end()) {
        struct node n = {.id = id, .pr = p_id};
        seen.push_back(n);
      }
    }

    i += 1;
  }

  if (found) {
    std::vector<int> ret = {};

    for (int nid = seen.back().id; nid != -1;) {
      auto it = std::find_if(seen.begin(), seen.end(),
                             [nid](struct node &n) { return n.id == nid; });

      node *n = &*it;
      // debug_node(n, "n");
      ret.push_back(n->id);
      nid = n->pr;
    }

    std::reverse(ret.begin(), ret.end());

    // printf("nodes := ");
    // int i = 0;
    // for (auto rn : ret) {
    //   if (i == 0) {
    //     i = 1;
    //   } else {
    //     printf(" -> ");
    //   }
    //   printf("%d", rn);
    // }
    // printf("\n");

    return ret;
  } else {
    return {};
  }
}

/// TODO: impl
std::vector<int> Network::distanceUser(int from, int &to, int distance) {
  std::vector<node> seen = std::vector<node>{node{from, -1, 0}};

  int i = 0;
  bool found = false;

  while (!found && i < seen.size()) {
    int p_id = seen[i].id;
    int dp = seen[i].dp;
    if (dp >= distance) {
      found = true;
      break;
    }

    User *u = this->getUser(p_id);
    auto friends = u->getFriends();
    for (auto id : friends) {
      // check if the thing exists
      auto it = std::find_if(seen.begin(), seen.end(),
                             [id](struct node &n) { return n.id == id; });

      if (it == seen.end()) {
        struct node n = {.id = id, .pr = p_id, .dp = dp + 1};
        seen.push_back(n);
      }
    }

    i += 1;
  }

  if (found) {
    node &last = seen[i];

    to = last.id;

    std::vector<int> ret = {};

    for (int nid = seen.back().id; nid != -1;) {
      auto it = std::find_if(seen.begin(), seen.end(),
                             [nid](struct node &n) { return n.id == nid; });

      node *n = &*it;
      // debug_node(n, "n");
      ret.push_back(n->id);
      nid = n->pr;
    }

    std::reverse(ret.begin(), ret.end());

    return ret;
  } else {
    to = -1;
    return {};
  }
}

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

void Network::addPost(int ownerId, std::string message, int likes,
                      bool isIncoming, std::string authorName, bool isPublic) {
  User *u = this->getUser(ownerId);

  if (u == nullptr)
    return;

  int id = u->getPosts().size() + 1;
  Post *p = new Post(id, ownerId, message, likes);
  u->addPost(p);
}

std::string Network::getPostsString(int ownerId, int howMany,
                                    bool showOnlyPublic) {

  User *u = this->getUser(ownerId);

  if (u == nullptr)
    return "";

  return u->getPostsString(howMany, showOnlyPublic);
}

#define handle_fscanf_err(ret)                                                 \
  switch (ret) {                                                               \
  case EOF:                                                                    \
    fprintf(stderr, "Unexpected EOF in stream.\n");                            \
    goto cleanup;                                                              \
  case 0:                                                                      \
    fprintf(stderr, "[%s:%d]: Ill formatted file.\n", __FILE__, __LINE__);     \
    goto cleanup;                                                              \
  }

#define scan_error(f)                                                          \
  if (!f) {                                                                    \
    fprintf(stderr, "[%s:%d]: Ill formatted file.\n", __FILE__, __LINE__);     \
    goto cleanup;                                                              \
  }

int Network::readPosts(char *fname) {
  std::ifstream f(fname);
  if (!f.is_open()) {
    printf("could not open file %s \n", fname);
    return -1;
  }

  // 1: single number representing how many posts are in the file
  int nusers;
  f >> nusers;
  scan_error(f);

  for (;;) {
    // 2: messageId_0
    int id;
    f >> id;
    if (f.eof()) {
      break;
    }
    scan_error(f);
    fprintf(stderr, "got id: %d\n", id);

    f.ignore(2);
    // 3: <TAB>message text
    std::string msg;
    std::getline(f, msg);
    scan_error(f);

    fprintf(stderr, "got msg: %s\n", msg.c_str());

    // 4: <TAB>ownerId
    int owner;

    // 5: <TAB>likes
    int likes;

    f >> owner >> likes;
    scan_error(f);

    fprintf(stderr, "got owner: %d\n", owner);
    fprintf(stderr, "got likes: %d\n", likes);

    f.ignore(1);

    // 6: <TAB>an empty line if the message is an owner Post OR the string
    // "public" or "private" if the message is an IncomingPost
    std::string type;
    std::getline(f, type);
    scan_error(f);

    fprintf(stderr, "got type: %s\n", type.c_str());

    // 7: <TAB>an empty line if the message is an owner Post OR an author
    // if the message is an IncomingPost
    std::string author;
    std::getline(f, author);
    scan_error(f);

    fprintf(stderr, "got author: %s\n", author.c_str());

    User *u = this->getUser(owner);
    if (u == nullptr) {
      continue;
    }

    if (type.size() == 0) {
      Post *p = new Post(id, owner, msg, likes);
      u->addPost(p);
    } else {

      bool publ;
      if (type == "\tprivate") {
        publ = false;
      } else if (type == "\tpublic") {
        publ = true;
      } else {
        fprintf(stderr, "unknown message publicity: %s\n", type.c_str());
        goto cleanup;
      }

      Post *p = new IncomingPost(id, owner, msg, likes, publ, author);
      u->addPost(p);
    }
  }

  f.close();
  return 0;

cleanup:
  f.close();
  return -1;
}

int Network::writePosts(char *fname) {
  // To implement writePosts, you should load all of the posts from all the
  // users into a single vector of Post pointers, sort the Posts by their
  // messageId using the STL sort methodLinks to an external site., and then
  // write the posts in that order to a file. To call sort function, you should
  // implement a comparison function for comparing two Post pointers.
  fprintf(stderr, "TODO: %s, %s:%d", __FUNCTION__, __FILE__, __LINE__);
  return -1;
}
