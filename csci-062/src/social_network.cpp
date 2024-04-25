#include "network.h"
#include "user.h"

#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <utility>

void debug_error_non_empty_stream(std::stringstream &ss) {
  // ss.str().substr()
  if (ss.eof())
    return;

  std::cout << "ignoring rest of stream: ";
  while (!ss.eof()) {
    char c = ss.get();
    std::cout << c;
  }
  std::cout << "\n";
}

// 1
/// TODO: error handling
void add_user(std::stringstream &ss, Network &network) {
  std::string frst_name;
  std::string last_name;
  int year;
  int zip;

  ss >> frst_name;
  ss >> last_name;
  ss >> year;
  ss >> zip;

  debug_error_non_empty_stream(ss);

  int id = rand() / 10000;
  std::string name = frst_name + " " + last_name;

  User *u = new User(id, name, year, zip, {});
  network.addUser(u);
}

// 2
void add_friend(std::stringstream &ss, Network &network) {
  std::string name1;
  std::string last1;
  std::string name2;
  std::string last2;

  ss >> name1 >> last1 >> name2 >> last2;

  debug_error_non_empty_stream(ss);

  int res = network.addConnection(name1 + " " + last1, name2 + " " + last2);
  if (res < 0) {
    std::cout << "Could not add a connection between those users.\n";
  }
}

// 3
void delete_friend(std::stringstream &ss, Network &network) {
  std::string name1;
  std::string last1;
  std::string name2;
  std::string last2;

  ss >> name1 >> last1 >> name2 >> last2;

  debug_error_non_empty_stream(ss);

  int res = network.deleteConnection(name1 + " " + last1, name2 + " " + last2);
  if (res < 0) {
    std::cout << "Could not find a connection between those users.\n";
  }
}

// 4
void print_users(std::stringstream &ss, Network &network) {
  debug_error_non_empty_stream(ss);

  auto users = network.getUsers();
  for (auto user : users) {
    std::cout << user->getId() << " " << user->getName() << "\n";
  }
}

// 5
void print_links(std::stringstream &ss, Network &network) {
  std::string name;
  std::string last;
  ss >> name;
  ss >> last;

  debug_error_non_empty_stream(ss);

  int id = network.getId(name + " " + last);
  if (id < 0) {
    std::cout << "no user with name: " << name << " " << last << "\n";
    return;
  }
  auto user = network.getUser(id);

  if (user == nullptr) {
    std::cerr << "unreachable code" << std::endl;
    abort();
  }

  auto friends = user->getFriends();
  for (int freind_id : friends) {
    auto f = network.getUser(freind_id);

    if (f == nullptr) {
      continue;
    }

    std::cout << f->getId() << " " << f->getName() << "\n";
  }
}

// 6
void write_file(std::stringstream &ss, Network &network) {
  std::string path;
  ss >> path;

  debug_error_non_empty_stream(ss);

  int ret = network.writeUsers((char *)path.c_str());

  if (ret < 0) {
    std::cout << "Could not write to file." << std::endl;
  }
}

// 7
// TODO:
void print_path(std::stringstream &ss, Network &network) {
  std::string name1;
  std::string last1;
  std::string name2;
  std::string last2;

  ss >> name1 >> last1 >> name2 >> last2;

  debug_error_non_empty_stream(ss);
  int id1 = network.getId(name1 + " " + last1);
  if (id1 < 0) {
    std::cerr << "unknown user: " << name1 << " " << last1 << ".\n";
    return;
  }

  int id2 = network.getId(name2 + " " + last2);
  if (id2 < 0) {
    std::cerr << "unknown user: " << name2 << " " << last2 << ".\n";
    return;
  }

  auto path = network.shortestPath(id1, id2);
  if (path.size() == 0) {
    std::cout << "no path between user\n";
    return;
  }

  std::cout << "Distance: " << path.size() << "\n";
  bool f = true;
  for (int id : path) {
    User *u = network.getUser(id);
    if (!f) {
      std::cout << " -> ";
    } else {
      f = false;
    }
    std::cout << u->getName();
  }
  std::cout << std::endl;
}

// 8
void print_distance_user(std::stringstream &ss, Network &network) {
  std::string name;
  std::string last;
  int dist;
  ss >> name;
  ss >> last;
  ss >> dist;

  debug_error_non_empty_stream(ss);

  int from = network.getId(name + " " + last);
  if (from < 0) {
    std::cerr << "unknown user: " << name << " " << last << ".\n";
    return;
  }

  int to;
  auto path = network.distanceUser(from, to, dist);

  std::cout << name << " " << last << " : ";
  bool f = true;
  for (int id : path) {
    User *u = network.getUser(id);
    if (!f) {
      std::cout << " -> ";
    } else {
      f = false;
    }
    std::cout << u->getName();
  }
  std::cout << std::endl;
}

// 9
void print_suggestions(std::stringstream &ss, Network &network) {
  std::string name;
  std::string last;
  ss >> name;
  ss >> last;

  debug_error_non_empty_stream(ss);
  int who = network.getId(name + " " + last);

  if (who < 0) {
    std::cerr << "unknown user: " << name << " " << last << ".\n";
    return;
  }

  int score = 0;
  auto suggest = network.suggestFriends(who, score);

  if (score < 0) {
    std::cout << "Can't find any suggestions for you.";
  } else {
    std::cout << "The suggested friend(s) is/are:";

    for (auto s : suggest) {
      std::cout << "\n";
      auto u = network.getUser(s);
      if (!u)
        return;
      std::cout << u->getName() << " Score: " << score;
    }
  }

  std::cout << std::endl;
}

// 10
void print_groups(std::stringstream &ss, Network &network) {
  debug_error_non_empty_stream(ss);
  auto groups = network.groups();

  int i = 1;
  for (auto group : groups) {
    if (i != 1) {
      std::cout << "\n";
    }

    std::cout << "Set " << i << " => ";

    bool f = true;
    for (auto id : group) {
      User *u = network.getUser(id);
      if (!u)
        return;

      if (f) {
        f = false;
      } else {
        std::cout << ", ";
      }
      std::cout << u->getName();
    }
    i += 1;
  }
  std::cout << std::endl;
}

void print_recent_posts(std::stringstream &ss, Network &network) {
  std::string name;
  std::string last;
  ss >> name;
  ss >> last;

  int count;
  ss >> count;

  debug_error_non_empty_stream(ss);

  int id = network.getId(name + " " + last);
  if (id < 0) {
    fprintf(stderr, "unknown user: %s %s\n", name.c_str(), last.c_str());
    return;
  }

  std::cout << network.getPostsString(id, count, false) << "\n";
}

int main(int argc, char *argv[]) {
  Network network;
  if (argc > 1) {
    int ret = network.readUsers(argv[1]);
    if (ret < 0) {
      fprintf(stderr, "Could not read from file: %s\n", argv[2]);
      return -1;
    }
  }
  if (argc > 2) {
    int ret = network.readPosts(argv[2]);
    if (ret < 0) {
      fprintf(stderr, "Could not read from file: %s\n", argv[2]);
      return -1;
    }
  }

  srand(time(nullptr));

  int code = EXIT_SUCCESS;

  for (;;) {
    std::cout << "> ";
    std::cout.flush();

    std::string line;
    std::getline(std::cin, line);

    if (line == "") {
      continue;
    }

    std::stringstream ss = std::stringstream(line);

    std::string option;
    ss >> option;

    if (option == "1") {
      add_user(ss, network);
    } else if (option == "2") {
      add_friend(ss, network);
    } else if (option == "3") {
      delete_friend(ss, network);
    } else if (option == "4") {
      print_users(ss, network);
    } else if (option == "5") {
      print_links(ss, network);
    } else if (option == "6") {
      write_file(ss, network);
    } else if (option == "7") {
      print_path(ss, network);
    } else if (option == "8") {
      print_distance_user(ss, network);
    } else if (option == "9") {
      print_suggestions(ss, network);
    } else if (option == "10") {
      print_groups(ss, network);
    } else if (option == "11") {
      print_recent_posts(ss, network);
    } else if (option == "12") {
      // exit option
      break;
    } else {
      std::cerr << "unknown option: " << option << std::endl;
      code = EXIT_FAILURE;
      break;
    }

    // debug_error_non_empty_stream(ss);
  }

  // this is needed for some reason to properly return the errcode
  exit(code);
  return code;
}
