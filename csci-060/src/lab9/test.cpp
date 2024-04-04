#include "dnode.h"
#include <iostream>
#include <vector>

// Complete the two functions “palindrome” and “delete_node” in the following
// code.
using namespace std;

/// checks if the list is a palindrome without using extra memory
bool palindrome(dnode *head) {
  dnode *back = head->backward();
  dnode *forw = head->forward();

  // if they point to the same node or they have steped past each other
  while (back != forw && back->forward() != forw) {
    if (back->data() != forw->data()) {
      return false;
    }
    back = back->backward();
    forw = forw->forward();
  }
  return true;
}

/// delete the node "to_delete" from the list
void delete_node(dnode *head, dnode *to_delete) {
  dnode *prev = head;
  for (dnode *p = head->forward(); p != head; p = p->forward()) {
    if (p == to_delete) {
      dnode *forw = p->forward();
      prev->set_forward(forw);
      forw->set_backward(prev);
      delete p;
      return;
    } else {
      prev = p;
    }
  }
}

int main() {
  dnode *head = new dnode();
  head->set_backward(head);
  head->set_forward(head);

  vector<int> rev_contents = {1, 2, 2, 1};
  for (int i = 0; i < rev_contents.size(); i++)
    dlist_insert(head, rev_contents[i]);
  dlist_print(head);
  // check if the list is a palindrome
  if (palindrome(head))
    cout << "List is a palindrome." << endl;
  else
    cout << "List is not a palindrome." << endl;
  // delete a non-head node from the list
  delete_node(head, head->forward());
  dlist_print(head);
  return 0;
}
