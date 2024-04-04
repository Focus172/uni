#include "BIGUINT.h"
#include "../node.h"
#include <algorithm>
#include <cstddef>
#include <cstdlib>

class llist {
private:
  size_t _size;

public:
  node *head;
  node *tail;

  llist(node *new_head = nullptr) {
    _size = 0;
    if (new_head == nullptr) {
      head = nullptr;
      tail = nullptr;
    } else {
      head = new_head;
      node *t;
      for (t = head; t->link() != nullptr; t = t->link())
        _size += 1;
      tail = t;
    }
  }

  void push(node::value_type v) {
    if (head == nullptr) {
      head = new node(v);
      tail = head;
    } else {
      list_insert(tail, v);
      tail = tail->link();
      _size += 1;
    }
  }

  size_t len() { return _size; }
};

BIGUINT::BIGUINT(std::size_t n) { this->_data = new node(n); }

#define ASCII_ZERO 48

BIGUINT::BIGUINT(const std::string &s) {
  llist l = llist();

  for (auto p = s.end(); p != s.begin(); p--) {
    l.push(*p - ASCII_ZERO);
  }
  _data = l.head;
}

BIGUINT::BIGUINT(const BIGUINT &b) {
  llist l = llist();

  for (node *p = b._data; p != nullptr; p = p->link()) {
    l.push(p->data());
  }

  _data = l.head;

  if (_data == nullptr) {
    _data = new node(0);
  }
}

BIGUINT::~BIGUINT() { list_clear(this->_data); }

BIGUINT::digit_type BIGUINT::operator[](size_type pos) const {
  if (pos > size())
    return 0;
  return list_locate(_data, pos)->data();
}

BIGUINT::size_type BIGUINT::size() const {
  llist l = llist(_data);
  return l.len();
}

int BIGUINT::compare(const BIGUINT &n) const {}
void BIGUINT::operator=(const BIGUINT &source) {}

void BIGUINT::ls(size_type n) {
  for (int i = 0; i < n; i++) {
    list_insert(_data, 0);
  }
}

void BIGUINT::rs(size_type n) {
  for (int i = 0; i < n; i++) {
    if (_data == nullptr) {
      _data = new node(0);
      return;
    }
    list_head_remove(_data);
  }
}

void BIGUINT::operator+=(const BIGUINT &b) {}
void BIGUINT::operator-=(const BIGUINT &b) {}
void BIGUINT::operator*=(digit_type d) {}
void BIGUINT::operator*=(const BIGUINT &b) {}
void BIGUINT::operator/=(const BIGUINT &b) {}
void BIGUINT::operator%=(const BIGUINT &b) {}

BIGUINT BIGUINT::operator++() {
  *this += 1;
  return BIGUINT(*this);
}

BIGUINT BIGUINT::operator--() {
  *this -= 1;
  return BIGUINT(*this);
}

BIGUINT BIGUINT::operator++(int) {
  BIGUINT ret = BIGUINT(*this);
  *this += 1;
  return ret;
}

BIGUINT BIGUINT::operator--(int) {
  BIGUINT ret = BIGUINT(*this);
  *this -= 1;
  return ret;
}

// NON-MEMBER OPERATORS
std::ostream &operator<<(std::ostream &os, const BIGUINT &);
std::istream &operator>>(std::istream &is, BIGUINT &);

// PERF: Everything here is done. There is no code it is all boilerplate.

BIGUINT operator+(const BIGUINT &lhs, const BIGUINT &rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret += lhs;
  return ret;
}

BIGUINT operator-(const BIGUINT &lhs, const BIGUINT &rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret -= lhs;
  return ret;
}

BIGUINT operator*(const BIGUINT &lhs, const BIGUINT &rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret *= lhs;
  return ret;
}

BIGUINT operator/(const BIGUINT &lhs, const BIGUINT &rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret /= lhs;
  return ret;
}

BIGUINT operator%(const BIGUINT &lhs, const BIGUINT &rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret %= lhs;
  return ret;
}

bool operator<(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) == -1;
}
bool operator<=(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) != 1;
}
bool operator==(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) == 0;
}
bool operator!=(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) != 0;
}
bool operator>=(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) != -1;
}
bool operator>(const BIGUINT &lhs, const BIGUINT &rhs) {
  return lhs.compare(rhs) == 1;
}

BIGUINT operator<<(const BIGUINT &lhs, unsigned int rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret.ls(rhs);
  return ret;
}

BIGUINT operator>>(const BIGUINT &lhs, unsigned int rhs) {
  BIGUINT ret = BIGUINT(lhs);
  ret.rs(rhs);
  return ret;
}
