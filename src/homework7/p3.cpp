#include <cassert>
#include <iostream>

/// Facade for testing
template <typename T> class node {
public:
  T data;
  node *next;
};

/// Reverses the list in place changing the head_ptr to the new start of the
/// list. Does nothing if head_ptr is null. UB if list is cyclical.
void list_reverse(node<int> *&head_ptr) {
  node<int> *last = nullptr;
  node<int> *cur = head_ptr;
  while (cur != nullptr) {
    node<int> *next = cur->next;
    cur->next = last;
    last = cur;
    cur = next;
  }
  head_ptr = last;
}

/// Helper for debuging
void print(node<int> *node, bool first) {
  if (first)
    std::cout << "[";

  if (node != nullptr) {
    std::cout << node->data;
    if (node->next != nullptr)
      std::cout << ", ";

    print(node->next, false);
  } else {
    std::cout << "]" << std::endl;
  }
}

void list_free(node<int> *&head) {
  for (auto *p = head; p != nullptr; p = p->next) {
  }
}

void push(node<int> *&tail, int value) {
  assert(tail->next == nullptr);

  tail->next = new node<int>;
  tail = tail->next;
  tail->data = value;
  tail->next = nullptr;
}

int main(int argc, char **argv) {
  node<int> *head = new node<int>;
  node<int> *tail = head;
  for (int i = 0; i < 10; i++) {
    push(tail, i * 7 % 13);
  }

  print(head, true);
  list_reverse(head);
  print(head, true);

  node<int> *test = static_cast<node<int> *>(nullptr);
  list_reverse(test);

  return 0;
}
