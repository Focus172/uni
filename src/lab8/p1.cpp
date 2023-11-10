#include "../node.h"
#include <iostream>
#include <vector>

using namespace std;

/// checks if the content in the linked list is a palindrome
bool palindrome(node *head) {
  vector<int> data{};

  for (node *p = head; p != nullptr; p = p->link()) {
    data.push_back(p->data());
  }

  int offset = 0;
  while (data.size() > offset + 1) {
    if (data.back() == data.at(offset)) {
      data.pop_back();
      offset += 1;
    } else {
      return false;
    }
  }
  // list contains 0 or 1 unknown element
  return true;
  // return (data.size() - offset <= 1);
}

/// checks if the content in the two linked lists is equal
bool equivalent(node *head1, node *head2) {
  node *left = head1;
  node *right = head2;

  while (left != nullptr && right != nullptr) {
    if (left->data() == right->data()) {
      left = left->link();
      right = right->link();
    } else {
      return false;
    }
  }
  // require them to be the same length
  return (left == nullptr && right == nullptr);
}

int main() {
  // initializing head and tail of the first linked list
  vector<int> content1 = {1, 2, 3, 4, 5, 6};
  node *head1 = new node(content1[0], nullptr);
  node *tail1(head1);
  node *temp1;

  // adding more nodes to the first linked list
  for (int i = 1; i < content1.size(); i++) {
    temp1 = new node(content1[i], nullptr);
    tail1->set_link(temp1);
    tail1 = tail1->link();
  }
  // initializing head and tail of the second linked list
  vector<int> content2 = {1, 2, 3, 4, 3, 2, 1};
  node *head2 = new node(content2[0], nullptr);
  node *tail2(head2);
  node *temp2;
  // adding more nodes to the second linked list
  for (int i = 1; i < content2.size(); i++) {
    temp2 = new node(content2[i], nullptr);
    tail2->set_link(temp2);
    tail2 = tail2->link();
  }
  // printing data within the first linked list
  for (node *p1 = head1; p1 != nullptr; p1 = p1->link())
    cout << p1->data() << " ";
  cout << endl;
  // printing data within the second linked list
  for (node *p2 = head2; p2 != nullptr; p2 = p2->link())
    cout << p2->data() << " ";
  cout << endl;
  // checking if the first linkedlist is a palindrome
  cout << palindrome(head1) << endl;
  // checking if the second linkedlist is a palindrome
  cout << palindrome(head2) << endl;
  // checking if the two linkedlists are equivalent
  cout << equivalent(head1, head2) << endl;
  return 0;
}
