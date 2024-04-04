#include <cstdlib>
#include <iostream>
#include <limits>

/// Write a C++ function double slope(double x1, double y1, double x2, double
/// y2) to compute the slope of the line going through the points (x1, y1) and
/// (x2, y2). If the line is vertical, return
/// numeric_limits<double>::infinity().

double slope(double x1, double y1, double x2, double y2);

int main(int argc, char *argv[]) { 
    std::cout << slope(3.0, 4.1, 5.2, 9.2) << std::endl;
    std::cout << slope(3.0, 5.3, 5.3, 5.3) << std::endl;
    std::cout << slope(0, 0, 3, 3) << std::endl;
    return EXIT_SUCCESS;
}

double slope(double x1, double y1, double x2, double y2) {
  double d_x = x2 - x1;
  double d_y = y2 - y1;

  if (d_y == 0.0) {
    return std::numeric_limits<double>::infinity();
  } else {
    return d_x / d_y;
  }
}
