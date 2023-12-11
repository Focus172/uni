#ifndef DNODE_H
#define DNODE_H

#include <cstdlib>

class dnode {
public:
  // TYPES & CONSTS
  typedef std::size_t size_type;
  typedef int value_type;

  // pre: none
  // post: this dnode has been initalized with given data and link values
  dnode(const value_type &data = value_type(), dnode *forward = nullptr,
        dnode *backward = nullptr) {
    _data = data;
    _forward = forward;
    _backward = backward;
  }

  // pre: none
  // post: returns data value
  value_type data() const { return _data; }

  // pre: none
  // post: returns forward link
  dnode *forward() { return _forward; }

  const dnode *forward() const { return _forward; }

  // pre: none
  // post: returns backward link
  dnode *backward() { return _backward; }
  const dnode *backward() const { return _backward; }

  // pre: none
  // post: set _data to data
  void set_data(const value_type &data) { _data = data; }

  // pre: none
  // post: set _forward to forward
  void set_forward(dnode *forward) { _forward = forward; }

  // pre: none
  // post: set _backward to backward
  void set_backward(dnode *backward) { _backward = backward; }

private:
  value_type _data;
  dnode *_forward;
  dnode *_backward;

  // CLASS INVARIANTS
  // 1. _data holds the item in this node
  // 2. _forward points to the next node in a linked list
  // 3. _backward points to the previous node in a linked list
};

// TOOLKIT FUNCTIONS to create and manipulate DOUBLY-LINKED, CIRCULAR LISTS with
// a HEAD NODE
//   1.  each node in these lists point to the next and previous nodes
//   2.  there is a special HEAD node that does not store any value
//   3.  the first node in the list points back to HEAD
//   4.  the last node in the list points forward to HEAD
//   5.  when the list is empty there is only one node, the HEAD node

dnode::size_type dlist_length(const dnode *);
void dlist_print(const dnode *);
void dlist_insert(dnode *, const dnode::value_type &entry);
void dlist_clear(dnode *&);

#endif // DNODE_H
