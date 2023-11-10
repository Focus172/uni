#include "p3.h"
#include "../node.h"

/// Reverses the list in place changing the head_ptr to the new start of the
/// list. Does nothing if head_ptr is null. UB if list is cyclical.
void list_reverse(node *&head_ptr) {
  node *last = nullptr;
  node *cur = head_ptr;
  while (cur != nullptr) {
    node *next = cur->link();
    cur->set_link(last);
    last = cur;
    cur = next;
  }
  head_ptr = last;
}
