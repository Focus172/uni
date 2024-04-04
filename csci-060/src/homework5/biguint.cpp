#include "biguint.h"
#include "cslice.h"
#include "slice.h"
#include "util.h"

/// ------------------------------- cslice.cpp ----------------------------- ///
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
tuple<biguint, biguint> div_rem(const biguint lhs, const biguint rhs) {
  biguint div = biguint(0);
  biguint rem = biguint(lhs);

  while (rem >= rhs) {
    biguint divisor = biguint(rhs);
    biguint count = biguint(1);
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

using digit_type = biguint::digit_type;
typedef ConstSlice<digit_type> DigitSlice;
typedef Slice<digit_type> MutDigitSlice;

biguint::biguint(std::size_t i) {
  // zero the bits to start with
  for (size_t i = 0; i < CAPACITY; i++) {
    this->_data[i] = 0;
  }

  this->_data[0] = i;
}

biguint::biguint(const std::string &s) {
  // zero the bits to start with
  for (size_t i = 0; i < CAPACITY; i++) {
    this->_data[i] = 0;
  }

  uint power = 0;
  for (int index = s.length() - 1; index >= 0; index--) {
    char l = s.at(index);
    digit_type d =
        l - ASCII_ZERO; // beacuse of precondition we assume this works

    // just doing math::pow will cause an overflow very quickly so
    // the didgets must be built the hard way.
    //
    // this is a right shift of `d` by `power` in base 10.
    biguint add = biguint(d);
    for (uint _i = 0; _i < power; _i++) {
      add *= biguint(10);
    }

    // adding the didget to the thing we are building.
    *this += add;
    power++;
  }
}

biguint::biguint(const biguint &b) {
  for (size_t i = 0; i < CAPACITY; i++) {
    this->_data[i] = b._data[i];
  }
}

biguint::digit_type biguint::operator[](size_type pos) const {
  // biguint tmp = biguint(*this);
  // // does `pos` base 10  right shifts
  // for (int _i = 0; _i < pos; _i++) {
  //   tmp /= 10;
  // }
  // // retruns the least signifigent base 10 diget.
  // return tmp._data[0] % 10;
  return this->_data[pos];
}

biguint::size_type biguint::size() const {
  // implementation: searches from the most signifigent didgets until it
  // finds a non-zero one.
  int index = this->CAPACITY - 1;
  while (index >= 0 && this->_data[index] == 0) {
    index--;
  }
  // When it is all zeros, the index will become -1 before exiting. So this
  // implicit cast always sucseeds beacuse 0 will always cast into a ulong.
  return size_type(index + 1);
}

int biguint::compare(const biguint &n) const {
  for (int i = CAPACITY - 1; i >= 0; i--) {
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
  return 0;
}

void biguint::rs(size_type n) {
  size_type full_digits = n / DIGIT_WIDTH;

  MutDigitSlice data = {this->_data, this->_data + CAPACITY - 1};

  // iterate in reverse reaching over to grab data into new position
  for (int i = CAPACITY - 1; i > full_digits; i--) {
    data.set(i, data.get(i - full_digits));
  }
  for (int i = full_digits - 1; i >= 0; i--) {
    data.set(i, 0);
  }

  size_type shift = n % DIGIT_WIDTH;
  size_type carry_shift = DIGIT_WIDTH - shift;

  digit_type carry = 0;

  for (int i = 0; i < CAPACITY; i++) {
    digit_type &elem = data.get_mut(i);
    digit_type new_carry = elem >> carry_shift;
    elem = (elem << shift) | carry;
    carry = new_carry;
  }
}

void biguint::ls(size_type n) {
  size_type full_digits = n / DIGIT_WIDTH;

  MutDigitSlice data = {this->_data, this->_data + CAPACITY - 1};

  for (int i = 0; i < CAPACITY - full_digits; i++) {
    data.set(i, data.get(i + full_digits));
  }
  for (int i = CAPACITY - full_digits; i < CAPACITY; i++) {
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

void biguint::operator+=(const biguint &b) {
  digit_type overflow = 0;
  for (size_type i = 0; i < CAPACITY; i++) {
    digit_type &d1 = this->_data[i];
    digit_type d2 = b._data[i];
    overflow = adc(d1, overflow, d1); // add last loops overflow checking again
    overflow += adc(d1, d2, d1);      // add the digets checking again
  }
}

void biguint::operator-=(const biguint &b) {
  if (*this < b) {
    printf("debug: setting to 0 beacuse big numb subtracted.\n");
    *this = biguint(0);
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

void biguint::operator*=(digit_type d) {
  biguint buf = biguint(0);
  MutDigitSlice zero = {buf._data, buf._data + buf.CAPACITY - 1};

  DigitSlice slc = {_data, _data + this->size()};
  mac_digit(zero, slc, d);
  *this = buf;
}

void biguint::operator*=(const biguint &b) {
  biguint buf = biguint(0);
  digit_type *p = buf._data;
  MutDigitSlice zero = MutDigitSlice(p, p + this->CAPACITY - 1);

  DigitSlice lhs = DigitSlice(this->_data, this->_data + this->size());
  DigitSlice rhs = DigitSlice(b._data, b._data + b.size());

  mac(zero, lhs, rhs);
  *this = buf;
}

void biguint::operator/=(const biguint &b) {
  auto [div, rem] = div_rem(*this, b);
  *this = div;
}

void biguint::operator%=(const biguint &b) {
  auto [div, rem] = div_rem(*this, b);
  *this = rem;
}

biguint biguint::operator++() {
  *this += biguint(1);
  return biguint(*this);
}
biguint biguint::operator--() {
  *this -= biguint(1);
  return biguint(*this);
}

biguint biguint::operator++(int) { return this->operator++(); }
biguint biguint::operator--(int) { return this->operator--(); }

std::ostream &operator<<(std::ostream &os, const biguint &value) {
  biguint tmp = biguint(value);
  std::string buf;
  while (tmp > 0) {
    biguint rem = tmp % 10;
    buf.push_back(rem[0] + ASCII_ZERO);
    tmp /= 10;
  }
  for (auto ptr = buf.end() - 1; ptr != buf.begin(); ptr--) {
    os << *ptr;
  }
  os << *buf.begin();

  return os;
}
std::istream &operator>>(std::istream &is, biguint &init) {
  std::string buf;
  is >> buf;
  init = biguint(buf);
  return is;
}

biguint operator+(const biguint &lhs, const biguint &rhs) {
  biguint ret = biguint(lhs);
  ret += rhs;
  return ret;
}

biguint operator-(const biguint &lhs, const biguint &rhs) {
  biguint ret = biguint(lhs);
  ret -= rhs;
  return ret;
}

biguint operator*(const biguint &lhs, const biguint &rhs) {
  biguint ret = biguint(lhs);
  ret *= rhs;
  return ret;
}

biguint operator/(const biguint &lhs, const biguint &rhs) {
  biguint ret = biguint(lhs);
  ret /= rhs;
  return ret;
}
biguint operator%(const biguint &lhs, const biguint &rhs) {
  biguint ret = biguint(lhs);
  ret %= rhs;
  return ret;
}

bool operator<(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) == -1;
}
bool operator<=(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) != 1;
}
bool operator==(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) == 0;
}
bool operator!=(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) != 0;
}
bool operator>=(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) != -1;
}
bool operator>(const biguint &lhs, const biguint &rhs) {
  return lhs.compare(rhs) == 1;
}

biguint operator<<(const biguint &lhs, unsigned int rhs) {
  biguint ret = biguint(lhs);
  ret.ls(rhs);
  return ret;
}

biguint operator>>(const biguint &lhs, unsigned int rhs) {
  biguint ret = biguint(lhs);
  ret.rs(rhs);
  return ret;
}

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ biguint.cpp ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //

#include <iostream>

int main(int argc, char **argv) {
  std::cout << "a := 2" << std::endl;
  biguint a = biguint("2");
  std::cout << "a = " << a << std::endl;
  std::cout << "a += 4" << std::endl;
  a += 4;
  std::cout << "a = " << a << std::endl;
  std::cout << "a += " << 0xFFFFFFF5 << std::endl;
  a += 0xFFFFFFF5;
  std::cout << "a = " << a << std::endl;
  a += 7;
  std::cout << a << std::endl;
  a += 0xF;
  a -= 4;
  std::cout << a << std::endl;
  a -= 19;
  std::cout << a << std::endl;
  a = biguint(5);
  std::cout << a << std::endl;

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
