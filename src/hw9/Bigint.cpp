#include "Bigint.h"
#include "Biguint.h"
#include <iostream>
#include <sys/types.h>

#define ASCII_ZERO 48 // '0'

Bigint::Bigint(int n) {
  if (n < 0) {
    digit_type d = digit_type(-n);
    *(Biguint *)this += Biguint(d);
    this->_is_neg = true;
  } else {
    digit_type d = (digit_type)n;
    *(Biguint *)this += Biguint(d);
    this->_is_neg = false;
  }
}

Bigint::Bigint(const std::string &s) {
  if (s.at(0) == '-') {
    this->_is_neg = true;
    *(Biguint *)this = Biguint(s.substr(1));
  } else {
    *(Biguint *)this = Biguint(s);
    this->_is_neg = false;
  }
}

int Bigint::compare(const Bigint &b) const {
  if (this->_is_neg) {
    if (b._is_neg) {
      return ((Biguint *)this)->compare((Biguint &)b);
    } else {
      return -1;
    }
  } else {
    if (b._is_neg) {
      return 1;
    } else {
      return ((Biguint *)this)->compare((Biguint &)b);
    }
  }

  return 0;
}

void Bigint::operator+=(const Bigint &b) {
  if (this->_is_neg) {
    if (b._is_neg) {
      *(Biguint *)this += (Biguint &)b;
    } else {
      if (((Biguint *)this)->compare((Biguint &)b) == 1) {
        *(Biguint *)this -= (Biguint &)b;
      } else {
        *(Biguint *)this = (Biguint &)b - *(Biguint *)this;
        this->_is_neg = false;
      }
    }
  } else {
    if (b._is_neg) {
      if (((Biguint *)this)->compare((Biguint &)b) == 1) {
        *(Biguint *)this -= (Biguint &)b;
      } else {
        *(Biguint *)this = (Biguint &)b - *(Biguint *)this;
        this->_is_neg = true;
      }
    } else {
      *(Biguint *)this += (Biguint &)b;
    }
  }

  if (this->size() == 1 && this[0] == 0) {
    this->_is_neg = false;
  }
}

std::ostream &operator<<(std::ostream &os, const Bigint &value) {
  if (value.compare(0) == -1) {
    os << "-";
  }
  os << (Biguint &)value;
  return os;
}

std::istream &operator>>(std::istream &is, Bigint &init) {
  std::string buf;
  is >> buf;
  init = Bigint(buf);
  return is;
}

Bigint operator+(const Bigint &lhs, const Bigint &rhs) {
  Bigint ret = Bigint(lhs);
  ret += rhs;
  return ret;
}
