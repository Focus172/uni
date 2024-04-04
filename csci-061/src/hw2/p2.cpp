#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// Monica, Chandler and Joey are hosting a party. There are currently N guests
// at the party. Each guest was given a placard with a number as they arrived.
// Monica being the organizer that she is, arranged all the guests analogous to
// a binary search tree with each of its nodes as a guest holding a placard.
// There are still M more guests to come. As one of the M guests arrive, they
// choose an arbitrary integer X, and they wish to be seated with a guest who
// has number X on their placard. Joey who is acting as a gatekeeper either
// lets a guest in if a guest with X on their placard exists in the party or
// sends the guest away if no one in the party has X on their placard. Every
// time, Joey asks Chandler to go look for the guest with X on their placard
// and shout YES or NO. Write a C++ program that helps Chandler to look for the
// guest in the most efficient way possible.
// Possible Input:
// ```
// 45 27 14 23 48 46 52 50
// 9 11 45 14 23 34
// ````
// Possible Output:
// ```
// No No Yes Yes Yes No
// ```
// First line of input contains the numbers on placards of N guests in the
// party. Second line of input represents the numbers that the M guests have
// picked. Here N is 8 and M is 6. Output is the corresponding Yes or No for
// each input of M.
int main(int argc, char *argv[]) {
  std::string file;
  if (argc <= 1) {
    std::cout << "No input file. Using hard coded path." << std::endl;
    file = "/home/focus/dox/School/13/wntr/csci-061/hw/src/hw2/p2";
  } else {
    file = argv[1];
  }
  std::fstream f;
  std::vector<int> guests;
  std::vector<int> placards;
  f.open(file);

  if (f.is_open()) {
    // -- Get Placards -- //
    std::string buf1;
    std::getline(f, buf1);
    std::istringstream iss1(buf1);

    int x1;
    while (iss1 >> x1) {
      placards.push_back(x1);
    }
    std::sort(placards.begin(), placards.end());
    // ----------------- //

    // -- Get Placards -- //
    std::string buf2;
    std::getline(f, buf2);
    std::istringstream iss2(buf2);
    int x2;
    while (iss2 >> x2) {
      guests.push_back(x2);
    }
    // ----------------- //
  } else {
    std::cout << "Input file (" << file
              << ") failed to open. Using hard coded variables instead."
              << std::endl;
    placards = {45, 27, 14, 23, 48, 46, 52, 50};
    std::sort(placards.begin(), placards.end());
    guests = {9, 11, 45, 14, 23, 34};
  }

  for (auto g : guests) {
    if (std::binary_search(placards.begin(), placards.end(), g)) {
      std::cout << "Yes ";
    } else {
      std::cout << "No ";
    }
  }

  std::cout << std::endl;
  return 0;
}
