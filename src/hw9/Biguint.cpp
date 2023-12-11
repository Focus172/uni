#include "Biguint.h"
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#define ASCII_ZERO 48 // '0'
#define DIGIT_WIDTH UINT32_WIDTH

// Long divison in base two using bit shifts
std::tuple<Biguint, Biguint> div_rem(const Biguint lhs, const Biguint rhs) {
  Biguint div = Biguint(0);
  Biguint rem = Biguint(lhs);

  while (rem >= rhs) {
    Biguint divisor = Biguint(rhs);
    Biguint count = Biguint(1);
    while ((divisor >> 1) <= rem) {
      divisor = divisor >> 1;
      count = count >> 1;
    }
    rem -= divisor;
    div += count;
  }
  return {div, rem};
}

Biguint::Biguint(std::size_t i, size_t c) {
  assert(c != 0);

  this->_capacity = 0;
  this->_data = nullptr;
  this->reserve(c);

  this->_data[0] = i;
}

Biguint::Biguint(const std::string &s) {
  this->_capacity = 0;
  this->_data = nullptr;

  int size = s.size();
  this->reserve(size);

  for (int i = 0; i < size; i++) {
    // beacuse of precondition we assume this works
    char c = s.at(i);
    digit_type d = c - ASCII_ZERO;
    this->_data[size - i - 1] = d;
  }
}

Biguint::~Biguint() { delete[] this->_data; }

Biguint::Biguint(const Biguint &b) {
  this->_data = nullptr;
  this->_capacity = 0;

  this->reserve(b._capacity);

  for (int i = 0; i < b._capacity; i++) {
    this->_data[i] = b._data[i];
  }
}

Biguint::digit_type Biguint::operator[](size_type pos) const {
  return this->_data[pos];
}

Biguint::size_type Biguint::size() const {
  size_type index = _capacity - 1;
  while (index > 0 && this->_data[index] == 0)
    index--;

  return index + 1;
}

int Biguint::compare(const Biguint &n) const {
  if (this->size() > n.size()) {
    return 1;
  } else if (this->size() < n.size()) {
    return -1;
  } else {
    for (int i = this->size(); i >= 0; i--) {
      digit_type d1 = this->_data[i];
      digit_type d2 = n._data[i];
      if (d1 > d2) {
        return 1;
      } else if (d2 > d1) {
        return -1;
      }
    }
  }

  return 0;
}

void Biguint::reserve(size_type new_capacity) {
  // PERF: Done
  if (new_capacity < _capacity) {

    // printf("not reserving for size %zu, beacuse already %zu.\n",
    // new_capacity, _capacity);
    return;
  }
  // printf("reserving %zu size beacuse only %zu right now.\n", new_capacity,
  // _capacity);

  digit_type *old = this->_data;
  this->_data = new digit_type[new_capacity];

  if (old == nullptr) {
    for (int i = 0; i < new_capacity; i++)
      _data[i] = 0;
  } else {
    for (int i = 0; i < _capacity; i++)
      _data[i] = old[i];
    for (int i = _capacity; i < new_capacity; i++)
      _data[i] = 0;
    delete old;
  }

  this->_capacity = new_capacity;
}

void Biguint::operator=(const Biguint &source) {
  delete[] this->_data;
  this->_data = new digit_type[source._capacity];
  this->_capacity = source._capacity;
  for (int i = 0; i < _capacity; i++) {
    _data[i] = source._data[i];
  }
}

void Biguint::rs(size_type n) {
  for (int i = 0; i + n < _capacity; i++) {
    _data[i] = _data[i + n];
  }
  for (int i = _capacity - n; i < _capacity; i++) {
    _data[i] = 0;
  }

  // size_type full_digits = n / DIGIT_WIDTH;
  //
  // MutDigitSlice data = {this->_data, this->_data + _capacity - 1};
  //
  // // iterate in reverse reaching over to grab data into new position
  // for (int i = _capacity - 1; i > full_digits; i--) {
  //   data.set(i, data.get(i - full_digits));
  // }
  // for (int i = full_digits - 1; i >= 0; i--) {
  //   data.set(i, 0);
  // }
  //
  // size_type shift = n % DIGIT_WIDTH;
  // size_type carry_shift = DIGIT_WIDTH - shift;
  //
  // digit_type carry = 0;
  //
  // for (int i = 0; i < data.len(); i++) {
  //   digit_type &elem = data.get_mut(i);
  //   digit_type new_carry = elem >> carry_shift;
  //   elem = (elem << shift) | carry;
  //   carry = new_carry;
  // }
}

void Biguint::ls(size_type n) {
  for (int i = _capacity - 1; i > n; i--) {
    _data[i] = _data[i - n];
  }
  for (int i = n; i < _capacity; i--) {
    _data[i] = 0;
  }

  // size_type full_digits = n / DIGIT_WIDTH;
  //
  // MutDigitSlice data = {this->_data, this->_data + _capacity - 1};
  //
  // for (int i = 0; i < _capacity - full_digits; i++) {
  //   data.set(i, data.get(i + full_digits));
  // }
  // for (int i = _capacity - full_digits; i < _capacity; i++) {
  //   data.set(i, 0);
  // }
  //
  // size_type shift = n % DIGIT_WIDTH;
  // size_type carry_shift = DIGIT_WIDTH - shift;
  //
  // digit_type carry = 0;
  // int i = 0;
  //
  // for (uint32_t *i = data.end; i >= data.start; i--) {
  //   digit_type new_carry = *i << carry_shift;
  //   *i = (*i >> shift) | carry;
  //   carry = new_carry;
  // }
}

void Biguint::operator+=(const Biguint &b) {
  size_type max_len = std::max(this->size(), b.size());
  Biguint rhs = Biguint(b);
  rhs.reserve(max_len + 1);
  this->reserve(max_len + 1);

  digit_type carry = 0;
  for (int i = 0; i < this->size() + 1; i++) {
    // printf("debug: %d + %d + %d = ", _data[i], rhs._data[i], carry);
    this->_data[i] = _data[i] + rhs._data[i] + carry;
    // printf("%d\n", this->_data[i]);
    carry = _data[i] / 10;
    _data[i] %= 10;
  }
}

void Biguint::operator-=(const Biguint &b) {
  if (*this < b) {
    // printf("debug: setting to 0 beacuse big num subtracted.\n");
    *this = Biguint(0);
    return;
  }

  size_type max = std::max(_capacity, b._capacity);
  Biguint rhs = Biguint(b);
  this->reserve(max);
  rhs.reserve(max);

  digit_type borrow = 0;
  for (int i = 0; i < _capacity; i++) {
    digit_type &d1 = this->_data[i];
    digit_type d2 = rhs._data[i];
    if (d1 >= d2 + borrow) {
      d1 -= d2 + borrow;
      borrow = 0;
    } else {
      d1 = (d2 + borrow) - d1;
      borrow = 1;
    }
  }

  // by the end the borrow is always 0 otherwise the first gaurd should have
  // failed.
  assert(borrow == 0);
}

void Biguint::operator*=(digit_type d) {
  this->reserve(_capacity + 1);

  digit_type carry = 0;

  for (int i = 0; i < _capacity; i++) {
    this->_data[i] = _data[i] * d + carry;
    carry = _data[i] / 10;
    _data[i] %= 10;
  }

  // Biguint buf = Biguint(0);
  // buf.reserve(this->_capacity + 2);
  // MutDigitSlice zero = {buf._data, buf._data + buf._capacity - 1};
  //
  // DigitSlice slc = {_data, _data + this->size()};
  // mac_digit(zero, slc, d);
  // *this = buf;
}

void Biguint::operator*=(const Biguint &b) {
  this->reserve(_capacity + b._capacity + 1);

  digit_type carry = 0;

  for (int i = 0; i < b._capacity; i++) {
    this->_data[i] = _data[i] + b._data[i] + carry;
    carry = _data[i] / 10;
    _data[i] %= 10;
  }
  // Biguint buf = Biguint(0);
  // buf.reserve(this->_capacity + b._capacity + 1);
  // MutDigitSlice zero = MutDigitSlice(buf._data, buf._data + buf._capacity -
  // 1);
  //
  // DigitSlice lhs = DigitSlice(this->_data, this->_data + this->size());
  // DigitSlice rhs = DigitSlice(b._data, b._data + b.size());
  //
  // mac(zero, lhs, rhs);
  // *this = buf;
}

void Biguint::operator/=(const Biguint &b) {
  auto [div, rem] = div_rem(*this, b);
  *this = div;
}

void Biguint::operator%=(const Biguint &b) {
  auto [div, rem] = div_rem(*this, b);
  *this = rem;
}

Biguint Biguint::operator++() {
  *this += Biguint(1);
  return Biguint(*this);
}
Biguint Biguint::operator--() {
  *this -= Biguint(1);
  return Biguint(*this);
}

Biguint Biguint::operator++(int _) { return this->operator++(); }
Biguint Biguint::operator--(int _) { return this->operator--(); }

std::ostream &operator<<(std::ostream &os, const Biguint &value) {
  for (int i = value.size() - 1; i >= 0; i--) {
    os << value[i];
  }

  return os;
}

std::istream &operator>>(std::istream &is, Biguint &init) {
  std::string buf;
  is >> buf;
  init = Biguint(buf);
  return is;
}

Biguint operator+(const Biguint &lhs, const Biguint &rhs) {
  Biguint ret = Biguint(lhs);
  ret += rhs;
  return ret;
}

Biguint operator-(const Biguint &lhs, const Biguint &rhs) {
  Biguint ret = Biguint(lhs);
  ret -= rhs;
  return ret;
}

Biguint operator*(const Biguint &lhs, const Biguint &rhs) {
  Biguint ret = Biguint(lhs);
  ret *= rhs;
  return ret;
}

Biguint operator/(const Biguint &lhs, const Biguint &rhs) {
  Biguint ret = Biguint(lhs);
  ret /= rhs;
  return ret;
}
Biguint operator%(const Biguint &lhs, const Biguint &rhs) {
  Biguint ret = Biguint(lhs);
  ret %= rhs;
  return ret;
}

bool operator<(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) == -1;
}
bool operator<=(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) != 1;
}
bool operator==(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) == 0;
}
bool operator!=(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) != 0;
}
bool operator>=(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) != -1;
}
bool operator>(const Biguint &lhs, const Biguint &rhs) {
  return lhs.compare(rhs) == 1;
}

Biguint operator<<(const Biguint &lhs, unsigned int rhs) {
  Biguint ret = Biguint(lhs);
  ret.ls(rhs);
  return ret;
}

Biguint operator>>(const Biguint &lhs, unsigned int rhs) {
  Biguint ret = Biguint(lhs);
  ret.rs(rhs);
  return ret;
}
