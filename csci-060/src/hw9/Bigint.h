#ifndef BIGINT_H
#define BIGINT_H

#include "Biguint.h"
#include <string>

class Bigint : public Biguint {
public:
  // pre: none
  // post: this Bigint has been created with initial value n, default to 0
  Bigint(int n = 0);

  // pre: string s consists of decimal digits plus an optional leading -
  // post: this Bigint has been created with initial value specified by s
  Bigint(const std::string &s);

  // pre: none
  // post: return 0 if this Bigint ==  b
  //             -1 if this Bigint < b
  //              1 if this Bigint > b
  int compare(const Bigint &b) const;

  // pre: none
  // pre: b has been added to this Bigint
  void operator+=(const Bigint &b);

private:
  bool _is_neg; // invariant: true if this Bigint is negative
};

std::ostream &operator<<(std::ostream &os, const Bigint &value);
std::istream &operator>>(std::istream &is, Bigint &init);

Bigint operator+(const Bigint &lhs, const Bigint &rhs);

#endif
