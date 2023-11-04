#include "Biguint.h"

/// -------------------------------- cslice.h ------------------------------ ///
#ifndef CONST_SLICE_H
#define CONST_SLICE_H 1

#include <cstddef>
#include <tuple>

/// Repersents an array in memory.
///
/// Invariants: start < end and all the memory between the pointers is allocated
template <typename T> class ConstSlice {
public:
  const T *start;
  const T *end;

  ConstSlice(const T *start, const T *end);

  std::tuple<ConstSlice<T>, ConstSlice<T>> split_at(size_t i);

  /// Returns the length of the slice
  size_t len() const;

  /// Gets a const referance to the value at the index panicing if out of
  /// bounds.
  const T &get(size_t i) const;

  /// returns of subslice of range from the two bounds, panics if bounds are
  /// invalid.
  ConstSlice<T> sub_slice(size_t, size_t) const;
  /// return a subslice of range from the start bound to the end.
  ConstSlice<T> sub_slice(size_t) const;
};

#endif // !CONST_SLICE_H
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ cslice.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
///
/// --------------------------------- slice.h ------------------------------ ///
#ifndef SLICEH
#define SLICEH 1

#include "cslice.h"
#include <cstddef>
#include <tuple>

/// Repersents an array in memory.
///
/// Invariants: start < end and all the memory between the pointers is allocated
template <typename T> class Slice {
public:
  T *start;
  T *end;

  Slice(T *start, T *end);

  std::tuple<ConstSlice<T>, ConstSlice<T>> split_at(size_t i) const;
  std::tuple<Slice<T>, Slice<T>> split_at_mut(size_t i);

  size_t len() const;

  void set(size_t i, T v);

  const T &get(size_t i) const;
  T &get_mut(size_t i);

  /// returns of subslice of range from the two bounds, panics if bounds are
  /// invalid.
  Slice<T> sub_slice(size_t, size_t) const;
  /// return a subslice of range from the start bound to the end.
  Slice<T> sub_slice(size_t) const;
};

#endif // !SLICEH
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ slice.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///

/// ------------------------------ util.h ---------------------------------- ///
#include "Biguint.h"
#include "cslice.h"
#include "slice.h"
#include <cstdint>
#include <tuple>

typedef Slice<uint32_t> MutU32Slice;
typedef ConstSlice<uint32_t> U32Slice;

/// Orders the slice by their length, the shorter slice is returned in the
/// first position.
std::tuple<U32Slice, U32Slice> order_lengths(const U32Slice, const U32Slice);

/// Add and carry operation
///
/// Adds the numbers together with overflow storing value into `out`
///
/// Return the overflow (always either 0 or 1).
uint32_t adc(uint32_t a, uint32_t b, uint32_t &out);

/// subtract with a borrow.
uint32_t sbb(uint32_t borrow, uint32_t a, uint32_t b, uint32_t &out);

/// Multiply accumulate where the second argument is only 1 diget.
/// In essance does this:
/// acc += b * c
void mac_digit(MutU32Slice acc, const U32Slice b, const uint32_t c);

/// Multiply Accumulate.
/// `acc += b * c`
void mac(MutU32Slice acc, const U32Slice b, const U32Slice c);

std::tuple<Biguint, Biguint> div_rem(const Biguint, const Biguint);

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ util.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
/// ------------------------------- cslice.cpp ----------------------------- ///
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstdlib>
// #include "cslice.h"

using std::tuple;

template <typename T> ConstSlice<T>::ConstSlice(const T *start, const T *end) {
  this->start = start;
  this->end = end;
}

template <typename T>
std::tuple<ConstSlice<T>, ConstSlice<T>> ConstSlice<T>::split_at(size_t i) {
  if (i > this->len()) {
    return {ConstSlice{start, end}, ConstSlice{end, end}};
  } else {
    return {ConstSlice{start, start + i}, ConstSlice{start + i, end}};
  }
}

template <typename T> size_t ConstSlice<T>::len() const {
  return this->end - this->start;
}

template <typename T> const T &ConstSlice<T>::get(size_t i) const {
  return this->start[i];
}

template <typename T>
ConstSlice<T> ConstSlice<T>::sub_slice(size_t x, size_t y) const {
  assert(x < y && y <= this->len());
  return {start + x, start + y};
}
template <typename T> ConstSlice<T> ConstSlice<T>::sub_slice(size_t x) const {
  assert(x <= this->len());
  return {start + x, end};
}
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ cslice.cpp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
/// -------------------------------- slice.cpp ----------------------------- ///
#include <cassert>
#include <cstdlib>

using std::tuple;

template <typename T> Slice<T>::Slice(T *start, T *end) {
  assert(start != NULL && end != NULL);
  assert(start <= end);
  this->start = start;
  this->end = end;
}

template <typename T>
tuple<Slice<T>, Slice<T>> Slice<T>::split_at_mut(size_t i) {
  if (i >= this->len()) {
    return {Slice{start, end}, Slice{end, end}};
  } else {
    return {Slice{start, start + i}, Slice{start + i, end}};
  }
}

template <typename T>
tuple<ConstSlice<T>, ConstSlice<T>> Slice<T>::split_at(size_t i) const {
  if (i >= this->len()) {
    return {Slice{start, end}, Slice{end, end}};
  } else {
    return {Slice{start, start + i}, Slice{start + i, end}};
  }
}

template <typename T> size_t Slice<T>::len() const {
  return this->end - this->start;
}

template <typename T> void Slice<T>::set(size_t i, T v) {
  assert(i >= 0 && i <= this->len());
  start[i] = v;
}

template <typename T> const T &Slice<T>::get(size_t i) const {
  assert(i >= 0 && i <= this->len());
  return start[i];
}

template <typename T> T &Slice<T>::get_mut(size_t i) {
  assert(i <= this->len());
  return start[i];
}

template <typename T> Slice<T> Slice<T>::sub_slice(size_t x, size_t y) const {
  assert(y >= x && y <= this->len());
  return {start + x, start + y};
}

template <typename T> Slice<T> Slice<T>::sub_slice(size_t x) const {
  assert(x <= this->len());
  return {start + x, end};
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ slice.cpp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
/// -------------------------------- util.cpp ------------------------------ ///

using std::tuple;

tuple<U32Slice, U32Slice> order_lengths(const U32Slice a, const U32Slice b) {

  if (a.len() > b.len()) {
    return {b, a};
  } else {
    return {a, b};
  }
}

/// Add and carry operation
///
/// Adds the numbers together with overflow storing value into `out`
///
/// Return the overflow (always either 0 or 1).
uint32_t adc(uint32_t a, uint32_t b, uint32_t &out) {
  // check if the addtion would overflow
  if (b > UINT32_MAX - a) {
    // return the overflow of the additon.
    out = b - (UINT32_MAX - a);
    // indicate that some overflow happened.
    return 1;
  } else {
    // do the addtion not accounting for overflow
    out = a + b;
    // indicate that no overflow happened.
    return 0;
  }
}

/// subtract with a borrow.
uint32_t sbb(uint32_t borrow, uint32_t a, uint32_t b, uint32_t &out) {
  int64_t a1 = a;
  int64_t b1 = b;
  int64_t bor = borrow;
  int64_t diff = a1 - b1 - bor;

  // this will likely just get optimized out as taking the first 32 bytes
  uint64_t tmp = *reinterpret_cast<uint64_t *>(&diff);
  tmp = tmp & UINT32_MAX; // masks off the last 32 bits
  out = uint32_t(tmp);    // converstion always works bc of above

  return static_cast<uint32_t>(diff < 0);
}

/// Given that a is the origonal diget. Computes:
/// `a += b * c + carry`
///
/// any overflow of `a` is stored in `&carry`
/// returns new value of a
uint32_t mac_digit_carry(uint32_t a, uint32_t b, uint32_t c, uint64_t &carry) {
  carry += uint64_t(a);
  carry += uint64_t(b) * uint64_t(c);
  uint32_t low_bits = uint32_t(carry & UINT32_MAX);
  carry = carry >> UINT32_WIDTH;
  return low_bits;
}

/// Multiply accumulate where the second argument is only 1 diget.
/// In essance does this:
/// acc += b * c
void mac_digit(MutU32Slice acc, const U32Slice b, const uint32_t c) {
  if (c == 0) {
    return;
  }

  uint64_t carry = 0;

  auto [a_lo, a_hi] = acc.split_at_mut(b.len());

  for (int i = 0; a_lo.start + i != a_lo.end; i++) {
    uint32_t &a_v = a_lo.get_mut(i);
    uint32_t b_v = b.get(i);
    a_v = mac_digit_carry(a_v, b_v, c, carry);
    // a_lo.start[i] = a_v;
  }
  uint32_t carry_lo = uint32_t(carry);
  uint32_t carry_hi = uint32_t(carry >> 32);

  a_hi.set(0, carry_lo);
  a_hi.set(1, carry_hi);
}

/// Multiply Accumulate.
/// `acc += b * c`
void mac(MutU32Slice acc, const U32Slice b, const U32Slice c) {
  // assign sorter slice to x and longer to y
  auto [x, y] = order_lengths(b, c);

  for (int i = 0; x.start + i != x.end; i++) {
    mac_digit(acc, y, x.get(i));
    acc = acc.sub_slice(1); // this should be after
  }
}

// Long divison in base two using bit shifts
tuple<Biguint, Biguint> div_rem(const Biguint lhs, const Biguint rhs) {
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

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ util.cpp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
/// ------------------------------- biguint.cpp ---------------------------- ///

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ostream>
#include <string>
#include <valarray>

#define ASCII_ZERO 48 // '0'
#define DIGIT_WIDTH UINT32_WIDTH

using digit_type = Biguint::digit_type;
typedef ConstSlice<digit_type> DigitSlice;
typedef Slice<digit_type> MutDigitSlice;

Biguint::Biguint(std::size_t i, size_t c) {
  // PERF: instead of zeroing bytes could keep track of allocated data.
  // Function done.
  this->_capacity = 0;
  this->_data = nullptr;
  this->reserve(c);

  this->_data[0] = i;
}

Biguint::Biguint(const std::string &s) {
  this->_capacity = 0;
  this->_data = nullptr;
  this->reserve(DEFAULT_CAPACITY);

  size_t power = 0;
  for (int index = s.length() - 1; index >= 0; index--) {
    char l = s.at(index);
    // beacuse of precondition we assume this works
    digit_type d = l - ASCII_ZERO;

    // just doing math::pow will cause an overflow very quickly so
    // the didgets must be built the hard way.
    //
    // this is a right shift of `d` by `power` in base 10.
    Biguint add = Biguint(d);
    for (uint _i = 0; _i < power; _i++) {
      add *= Biguint(10);
    }

    // adding the digit to the thing we are building.
    // PERF: this will alloc more memory when needed
    *this += add;
    power++;
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
  // PERF: Should gaurd aginst ioob but just follow the spec
  return this->_data[pos];
}

Biguint::size_type Biguint::size() const {
  // PERF: searches from the right.

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
        // printf("debug: %d > %d at diget %d.\n", d1, d2, i);
        return 1;
      } else if (d2 > d1) {
        // printf("debug: %d < %d at diget %d.\n", d1, d2, i);
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
  // PERF: done
  size_type full_digits = n / DIGIT_WIDTH;

  MutDigitSlice data = {this->_data, this->_data + _capacity - 1};

  // iterate in reverse reaching over to grab data into new position
  for (int i = _capacity - 1; i > full_digits; i--) {
    data.set(i, data.get(i - full_digits));
  }
  for (int i = full_digits - 1; i >= 0; i--) {
    data.set(i, 0);
  }

  size_type shift = n % DIGIT_WIDTH;
  size_type carry_shift = DIGIT_WIDTH - shift;

  digit_type carry = 0;

  for (int i = 0; i < data.len(); i++) {
    digit_type &elem = data.get_mut(i);
    digit_type new_carry = elem >> carry_shift;
    elem = (elem << shift) | carry;
    carry = new_carry;
  }
}

void Biguint::ls(size_type n) {
  // PERF: Done
  size_type full_digits = n / DIGIT_WIDTH;

  MutDigitSlice data = {this->_data, this->_data + _capacity - 1};

  for (int i = 0; i < _capacity - full_digits; i++) {
    data.set(i, data.get(i + full_digits));
  }
  for (int i = _capacity - full_digits; i < _capacity; i++) {
    data.set(i, 0);
  }

  size_type shift = n % DIGIT_WIDTH;
  size_type carry_shift = DIGIT_WIDTH - shift;

  digit_type carry = 0;
  int i = 0;

  for (uint32_t *i = data.end; i >= data.start; i--) {
    digit_type new_carry = *i << carry_shift;
    *i = (*i >> shift) | carry;
    carry = new_carry;
  }
}

void Biguint::operator+=(const Biguint &b) {
  size_type max_len = std::max(this->size(), b.size());
  size_type min_len = std::min(this->size(), b.size());

  this->reserve(max_len + 1);

  digit_type overflow = 0;

  for (int i = 0; i < min_len; i++) {
    digit_type &d1 = this->_data[i];
    digit_type d2 = b._data[i];
    overflow = adc(d1, overflow, d1); // add last loops overflow checking again
    overflow += adc(d1, d2, d1);      // add the digets checking again
  }

  for (int i = min_len; i < _capacity; i++) {
    digit_type &d1 = this->_data[i];
    overflow = adc(d1, overflow, d1);
  }
}

void Biguint::operator-=(const Biguint &b) {
  if (*this < b) {
    // printf("debug: setting to 0 beacuse big num subtracted.\n");
    *this = Biguint(0);
    return;
  }

  digit_type borrow = 0;
  for (size_type i = 0; i < this->size(); i++) {
    digit_type &d1 = this->_data[i];
    digit_type d2 = b._data[i];
    borrow = sbb(borrow, d1, d2, d1);
  }
  // by the end the borrow is always 0 otherwise the first gaurd should have
  // failed.
  if (borrow != 0) {
    abort();
  }
}

void Biguint::operator*=(digit_type d) {
  Biguint buf = Biguint(0);
  buf.reserve(this->_capacity + 2);
  MutDigitSlice zero = {buf._data, buf._data + buf._capacity - 1};

  DigitSlice slc = {_data, _data + this->size()};
  mac_digit(zero, slc, d);
  *this = buf;
}

void Biguint::operator*=(const Biguint &b) {
  // PERF: pre-reserves capacity for the output buffer
  Biguint buf = Biguint(0);
  buf.reserve(this->_capacity + b._capacity + 1);
  MutDigitSlice zero = MutDigitSlice(buf._data, buf._data + buf._capacity - 1);

  DigitSlice lhs = DigitSlice(this->_data, this->_data + this->size());
  DigitSlice rhs = DigitSlice(b._data, b._data + b.size());

  mac(zero, lhs, rhs);
  *this = buf;
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
  Biguint tmp = Biguint(value);
  std::string buf;
  while (tmp > 0) {
    Biguint rem = tmp % 10;
    buf.push_back(rem[0] + ASCII_ZERO);
    tmp /= 10;
  }
  for (auto ptr = buf.end() - 1; ptr != buf.begin(); ptr--) {
    os << *ptr;
  }
  os << *buf.begin();
  // for (int i = 0; i < value.size(); i++) {
  //   os << value[i] << ", ";
  // }

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

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ biguint.cpp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#include <iostream>

int main(int argc, char **argv) {
  std::cout << "a := 2" << std::endl;
  Biguint a = Biguint(2);
  std::cout << "a = " << a << std::endl;
  std::cout << "a += 4" << std::endl;
  a += Biguint(4);
  std::cout << "a = " << a << std::endl;
  std::cout << "a += " << 0xFFFFFFF5 << std::endl;
  a += 0xFFFFFFF5;
  std::cout << "a = " << a << std::endl;
  std::cout << "a += 7" << std::endl;
  a += 7;
  std::cout << "a = " << a << std::endl;
  std::cout << "a += " << 0xF << std::endl;
  a += 0xF;
  std::cout << "a = " << a << std::endl;
  std::cout << "a -= 4" << std::endl;
  a -= 4;
  std::cout << "a = " << a << std::endl;
  std::cout << "a -= 19" << std::endl;
  a -= 19;
  std::cout << "a = " << a << std::endl;

  std::cout << "a := 5" << std::endl;
  a = Biguint("5");
  std::cout << "a = " << a << std::endl;

  std::cout << "a *= " << a << std::endl;
  a *= a;
  std::cout << "a = " << a << std::endl;

  std::cout << "a = a >> 2" << std::endl;
  a = a >> 2;
  std::cout << "a = " << a << std::endl;

  std::cout << "a = a << 1" << std::endl;
  a = a << 1;
  std::cout << "a = " << a << std::endl;

  std::cout << "a = a >> 10" << std::endl;
  a = a >> 10;
  std::cout << "a = " << a << std::endl;

  std::cout << "a = a >> 30" << std::endl;
  a = a >> 30;
  std::cout << "a = " << a << std::endl;

  std::cout << "a = a << 29" << std::endl;
  a = a << 29;
  std::cout << "a = " << a << std::endl;

  std::cout << "a /= 2" << std::endl;
  a /= 2;
  std::cout << "a = " << a << std::endl;

  std::cout << "a /= 10" << std::endl;
  a /= 10;
  std::cout << "a = " << a << std::endl;

  std::cout << "a /= 250" << std::endl;
  a /= 250;
  std::cout << "a = " << a << std::endl;

  std::cout << "a / 4 = " << a / 4 << std::endl;

  // a *= 0xFFFFFF55;
  // std::cout << a << std::endl;
  // a *= a;
  // std::cout << a << std::endl;
  // a *= a;
  // std::cout << a << std::endl;

  return 0;
}
