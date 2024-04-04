// ----------------------------- begin sol2.h ------------------------------- //

#include <cmath>
#include <cstdio>
#include <iostream>
#include <sys/types.h>
bool quadratic_solver(double, double, double, double &, double &);

// ------------------------------ end sol2.h -------------------------------- //

// -------------------------- begin as_double.h ----------------------------- //

// #include <optional>
// #include <string>
// #define ASCII_0 48
// #define ASCII_9 57
//
// std::optional<double> as_double(std::string *buf) {
//   double ret = 0;
//
//   uint index_of_decimal = 0;
//   for (auto c : *buf) {
//     if (c == '.') {
//       break;
//     } else {
//       index_of_decimal++;
//     }
//   }
//
//   int index = 0;
//   for (char c : *buf) {
//     if (index == 0) {
//       if (c == '-') {
//         ret = -0;
//       }
//     }
//     if (c < ASCII_0 || c > ASCII_9) {
//       return std::nullopt;
//     } else {
//       // ret += (c - ASCII_0) * std::pow(10, pow--);
//     }
//   }
//   return std::optional<double>(ret);
// }

// --------------------------- end as_double.h ------------------------------ //

/// Write a C++ function
/// ```c
/// bool quadratic_solver(double a, double b, double c, double & r1, double &
/// r2)
/// ```
///
/// The function should find the real roots of quadratic equations of the form
/// ax2+bx+c=0. Your function should return true if the input equation has real
/// roots, which will be put in r1 and r2; your function should return false if
/// the input equation has no real roots.
///
/// Use a loop in main() to test your function for various input triples a, b, c
// until the user enters 0 for a.
///
/// Test cases to screenshot:
/// 1, −5, 6;
/// 1, 2, 1;
/// 1, 1, 1;
int main(int argc, char **argv) {
  while (true) {
    double a;
    double b;
    double c;
    // std::string buf1;
    // std::string buf2;
    // std::string buf3;
    // std::cin >> buf1 >> buf2 >> buf3;
    // auto value1 = as_double(&buf1);
    // auto value2 = as_double(&buf2);
    // auto value3 = as_double(&buf3);
    // if (value1.has_value() && value2.has_value() && value3.has_value()) {
    {
      printf("Enter three doubles: ");
      // double a = value1.value();
      // double b = value2.value();
      // double c = value3.value();
      std::cin >> a >> b >> c;
      double r1;
      double r2;

      if (a == 0.0) {
        return 0;
      }

      if (quadratic_solver((double)a, (double)b, (double)c, r1, r2)) {
        printf("Solutions are %f and %f\n", r1, r2);
      } else {
        printf("No real roots\n");
      }
    }
  }
  return 0;
}

bool quadratic_solver(double a, double b, double c, double &r1, double &r2) {
  double det = (b * b) - (4 * a * c);
  if (det < 0) {
    // printf("Deubg: no roots beacuse %f is less than 0\n", det);
    r1 = 0;
    r2 = 0;
    return false;
  } else {
    double square = std::sqrt(det);
    r1 = (-b + square) / (2 * a);
    r2 = (-b - square) / (2 * a);

    return true;
  }
}
