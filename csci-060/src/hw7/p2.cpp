#include "../node.h"
#include <iostream>

using namespace std;

int main() {
  // create a new list with one node whose value is 4
  node *head = new node(4, nullptr);
  // makes a tail pointer that corretluy points to the head
  node *tail(head);
  node *temp;

  // allocates a new node with value 1
  temp = new node(1, nullptr);
  // places the 1 after the 4 in the list
  tail->set_link(temp);
  // updates the tail to the new end of list
  tail = temp;
  // list now looks like:
  // 4 -> 1

  // makes a new node that points to the head and reassings the head to that
  // this in effect adds it to the start of the list keeping head up to date.
  // list now looks like:
  // 1 -> 4 -> 1
  head = new node(1, head);
  // same as above
  // list now looks like:
  // 3 -> 1 -> 4 -> 1
  head = new node(3, head);

  // makes a new node with value 5
  temp = new node(5, nullptr);
  // adds it to the end of the list
  // list now looks like:
  // 3 -> 1 -> 4 -> 1 -> 5
  tail->set_link(temp);
  // updates the tail to the new end of the list
  tail = temp;

  // walks over the list
  for (node *p = head; p != nullptr; p = p->link())
    // prints each value spaces sperated
    cout << p->data() << " ";

  // adds a new line
  cout << endl;

  // output is:
  // "3 1 4 1 5 \n"

  return 0;
}
