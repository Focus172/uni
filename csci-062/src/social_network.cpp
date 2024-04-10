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

// User *get_user_by_name(Network &n, std::string first, std::string last) {
//   int id = n.getId(first + " " + last);
//   return n.getUser(id);
// }

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
    std::cout << "TODO: imporve this error. user didnt exsits\n";

    // auto u1 = get_user_by_name(network, name1, last1);
    // if (u1 == nullptr) {
    //   std::cout << "user (" << name1 << " " << last1 << ") doesn't exists
    //   \n.";
    // }
    // auto u2 = get_user_by_name(network, name2, last2);
    //
    // if (u2 == nullptr) {
    //   std::cout << "user (" << name2 << " " << last2 << ") doesn't exists
    //   \n.";
    // }
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
    std::cout << "TODO: imporve this error. user didnt exsits\n";

    // auto u1 = get_user_by_name(network, name1, last1);
    // if (u1 == nullptr) {
    //   std::cout << "user (" << name1 << " " << last1 << ") doesn't exists
    //   \n.";
    // }
    // auto u2 = get_user_by_name(network, name2, last2);
    //
    // if (u2 == nullptr) {
    //   std::cout << "user (" << name2 << " " << last2 << ") doesn't exists
    //   \n.";
    // }
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
    std::cout << "unreachable";
    return;
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
    std::cout << "could not write to file." << std::endl;
  }
}

int main(int argc, char *argv[]) {
  Network network;
  if (argc > 1) {
    network.readUsers(argv[1]);
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
      break;
    } else {
      std::cerr << "unknown option: " << option << std::endl;
      code = EXIT_FAILURE;
      break;
    }
  }

  // this is needed for some reason to properly return the errcode
  exit(code);
  return code;
}
