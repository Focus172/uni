#include "dnode.h"
#include <iostream>

dnode::size_type dlist_length(const dnode *head) {
  dnode::size_type ans(0);

  for (const dnode *p = head->forward(); p != head; p = p->forward()) {
    ++ans;
  }
  return ans;
}

void dlist_insert(dnode *head, const dnode::value_type &entry) {
  dnode *oldfirst = head->forward();
  dnode *newfirst = new dnode(entry, oldfirst, head);

  head->set_forward(newfirst);
  oldfirst->set_backward(newfirst);
}

void dlist_print(const dnode *head) {
  for (const dnode *p = head->forward(); p != head; p = p->forward())
    std::cout << p->data() << " ";
  std::cout << std::endl;
}

void dlist_clear(dnode *&head) {

  dnode *p = head->forward();
  while (p != head) {
    dnode *temp = p;
    p = p->forward();
    delete temp;
  }
  delete head;
  head = nullptr;
}
