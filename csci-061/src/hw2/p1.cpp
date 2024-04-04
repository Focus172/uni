#include <algorithm>
#include <iostream>
#include <sys/types.h>
#include <vector>

void __inorder(char *list, int size, int index) {
  // dont run if node doesn't exist
  if (index >= size) {
    return;
  }

  // order left -> root -> right
  __inorder(list, size, index * 2 + 1);
  std::cout << list[index];
  __inorder(list, size, index * 2 + 2);
}

/// Print the list out in inorder
void inorder(std::vector<char> &list) {
  __inorder(&list.front(), list.size(), 0);
  std::cout << "\n";
}

void __postorder(char *list, int size, int index) {
  // dont run if node doesn't exist
  if (index >= size) {
    return;
  }

  // order left -> right -> root
  __postorder(list, size, index * 2 + 1);
  __postorder(list, size, index * 2 + 2);
  std::cout << list[index];
}

/// Print the list out in postorder
void postorder(std::vector<char> &list) {
  __postorder(&list.front(), list.size(), 0);
  std::cout << "\n";
}

/// Consider the following binary tree
///       A
///    L     G
///  O   R I   T
/// H M S
///
/// Write a C++ program to traverse and output the heap in inorder as well as
/// postorder.
int main(int argc, char *argv[]) {
  std::vector<char> v{'A', 'L', 'G', 'O', 'R', 'I', 'T', 'H', 'M', 'S'};

  // this does nothing but you said to make it a heap but didn't want it sorted
  // so this is what you get.
  std::make_heap(v.begin(), v.end(), [](char &_lhs, char &_rhs) { return -1; });

  inorder(v);
  postorder(v);

  return 0;
}
