/// --------------------- BEGIN HEADER FILE -------------------------------- ///

#include <climits>
#include <cstdio>
#include <deque>
#include <iostream>
#include <iterator>
#include <ostream>
#include <random>
#include <sstream>
#include <stack>
#include <string>
#include <sys/types.h>
#include <vector>

/// ----------------------- END HEADER FILE -------------------------------- ///

/// Add and carry operation
uint adc(uint a, uint b, uint c, uint &out) {
  unsigned long long sum = (unsigned long long)a + b + c;
  // mask of the first 32 bits of the ulonglong
  out = (uint)sum;
  // return the rest as the carry
  return sum >> 32;
}

class BigUInteger {
  std::deque<uint> data;

public:
  BigUInteger() { this->data.push_front(0); };
  BigUInteger(uint x) { this->data.push_front(x); }
  BigUInteger(std::deque<uint> data) { this->data = data; };

  /// Iterate backwards through the vector adding things until there is no more
  /// carry
  void add(uint x) {
    uint carry = 0;
    uint index_from_last = 0;
    uint current_len = this->data.size() - 1;
    while (index_from_last <= current_len) {
      uint &ptr = this->data.at(current_len - index_from_last);

      carry = adc(ptr, x, carry, ptr);
      x = 0;
      index_from_last++;

      if (carry == 0) {
        return;
      } else if (index_from_last + 1 >= current_len) {
        this->data.push_front(0);
        current_len++;
      }
    }
  };

  void add(BigUInteger other){
      // uint max_len = std::max(this->data.size(), other.data.size());
      // uint num_iter = std::min(this->data.size(), other.data.size());
      //
      //   uint *ptr = x.data.data();
      // uint arr_len = other_size;
      //
      // // grab the tailend of the data if it is larger than the current data
      // if (other_size > this_size) {
      //   ptr += (other_size - this_size);
      //   arr_len = this_size;
      // }
      //
  };

  bool is_zero() { return this->data.size() == 1 && this->data.back() == 0; };

  bool operator==(const BigUInteger &other) {
    // TODO: iterat through both and make sure the values are the same
    return false;
  };

  void div(const uint other) {
        // // Iterate through it in reverse
        //   d in a.data.iter_mut().rev() {
        //     let(q, r) = div_wide(rem, *d, b);
        //     *d = q;
        //     rem = r;
        //   }
  };

  BigUInteger clone() const {
        std::deque<uint> cloned_data;
        for (int i = 0; i < this->data.size(); i++)
          cloned_data.push_back(this->data[i]);

        return BigUInteger(cloned_data);
  };

  void print() const {
        BigUInteger x = this->clone();
        uint index = 0;
        char buffer[100];

        while (!x.is_zero()) {
          uint last_dig = x.data.back() % 10;
          buffer[index] = last_dig + 48;
          index++;
        }

        // TODO: find out how to do this shit
  };

  void debug() const { this->debug(stderr); };

  void debug(FILE *w) const {
        fprintf(w, "BigUInteger {\n");
        fprintf(w, "    data: [");
        for (uint i : data) {
          if (i == data.back())
            fprintf(w, "%u]\n", i);
          else
            fprintf(w, "%u, ", i);
        }
        fprintf(w, "};\n");
  }
};

class BigInteger {
  bool sign; // true is positive
  BigUInteger inner;

public:
  BigInteger() {}
  BigInteger(int x) {
        if (x < 0) {
          this->sign = false;
          inner = BigUInteger(-x);
        } else {
          this->sign = true;
          inner = BigUInteger(x);
        }
  };

  void debug() const { this->debug(stderr); };

  void debug(FILE *w) const {
        int SIZE = 100;
        char buffer[SIZE];
        FILE *f = fmemopen(buffer, SIZE, "w");
        this->inner.debug(f);
        fclose(f);
        std::stringstream ss = std::stringstream(buffer);
        std::string out;

        printf("BigInteger {\n");
        printf("    sign: %d,\n", this->sign);

        std::getline(ss, out, '\n');
        printf("    inner: %s\n", out.c_str());
        while (std::getline(ss, out, '\n')) {
          printf("    %s\n", out.c_str());
        }

        printf("};\n");
  };
};

#define IS_TRUE(x)                                                             \
  {                                                                            \
        if (!(x))                                                              \
          std::cout << __FUNCTION__ << " failed on line " << __LINE__          \
                    << std::endl;                                              \
  }

void test_biguint_add(void) {
  BigUInteger x = BigUInteger(2000000000);
  x.debug();
  x.add(4005003000);
  x.debug();
}

// void test_overflow_add_with_overflow(void) {
//   std::tuple x = add_with_overflow(INT_MAX - 5, 10);
//   IS_TRUE(std::get<0>(x) == INT_MAX)
//   IS_TRUE(std::get<1>(x) == 5)
// }
//
// void test_underflow_add_with_overflow(void) {
//   std::tuple x = add_with_overflow(INT_MIN + 5, -12);
//   IS_TRUE(std::get<0>(x) == INT_MIN)
//   IS_TRUE(std::get<1>(x) == -7)
// }

int main(int argc, char **argv) {
  test_biguint_add();
  return EXIT_SUCCESS;
}
