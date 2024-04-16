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

  std::cout << "TODO: print path.\n";
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
      print_path(ss, network);
    } else if (option == "8") {
      // 3. User at a given Distance
      // Menu 8
      // Given a user and a distance, find a user whose relational distance from
      // the given user exactly matches the distance given. You should also give
      // the path travelled.  To do this, add a public method std::vector<int>
      // Network::distanceUser(int from, int& to, int distance) to your Network
      // class.  The call by reference parameterLinks to an external site. "int
      // & to" should be the id of the user found, and the method should return
      // a vector of the IDs of the users on the path.  If no such user exists,
      // the function should return an empty vector and set the "to" parameter
      // to -1.
    } else if (option == "9") {
      // 4. Friend Suggestions
      // Menu 9
      // Search only 2 links (or friends of friends).
      // The score of a potential new friend is the number of common friends
      // they would share with the specified user. To do this, you will need to
      // add a public method vector<int> Network::suggestFriends(int who, int&
      // score) to your Network class. The call by reference parameter score
      // should hold the highest score found, and the method should return a
      // list of the ids of Users who have that score. If no suggestions exists,
      // return the empty vector and set score to 0.

    } else if (option == "10") {
      // 5. Groups with DFS
      // Menu 10
      // Compute how many connected components of users are present in the
      // network. A connected component is a group of users who all have paths
      // to one another but have no edges to all other uses. Use DFS to compute
      // the connected components of the network. The output should be a list of
      // lists, where each list contains the ids of the users in one connected
      // component.  To do this you will need to add the following public method
      // to Network that returns a list of the connected components of the
      // network:  vector<vector<int> > Network::groups()  You should do all the
      // computation in the function but do any I/O (printing) in your main. You
      // may add other private helper functions to your network class.
      //
      // For example, if the network only had four users and Isaac Boone and
      // Jason Chen were each other’s only friends while Asia Kane and Jasmine
      // Clements were friends, the result of selecting this feature should be:
      //
      // Set 1 => Isaac Boone, Jason Chen
      // Set 2 => Asia Kane, Jasmine Clements
      // To include this, make this menu option 10. The user shall simply input
      // the command number (i.e. 8) to execute this feature.
    } else if (option == "11") {
      // exit option
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
