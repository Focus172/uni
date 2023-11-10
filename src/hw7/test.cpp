#include "../node.h"
#include "p3.h"
#include <cstdlib>
#include <iostream>

/// Helper for debuging
void list_pprint(node *head) {
  std::cout << "[";

  // unroll the first loop to do one less check within it
  if (head) {
    std::cout << head->data();
    head = head->link();
  }

  while (head) {
    std::cout << ", " << head->data();
    head = head->link();
  }
  std::cout << "]" << std::endl;
}

int main(int argc, char **argv) {
  node *head = new node(0, nullptr);
  node *tail = head;

  // node *a = (node *)std::malloc(sizeof(node));
  // a->set_link(nullptr);
  // a->set_data(0);
  // list_pprint(a);
  // free(a);

  for (int i = 0; i < 10; i++) {
    list_insert(tail, i * 7 % 13);
    tail = tail->link();
  }

  list_pprint(head);

  list_reverse(head);

  list_pprint(head);

  node *null = static_cast<node *>(nullptr);
  list_reverse(null);

  list_clear(head);
  return 0;
}
