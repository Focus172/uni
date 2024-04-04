#include "line.h"
#include "assert.h"
#include <cstdio>
#include <iostream>
#include <math.h>

line::line(double init_x0, double init_y0, double init_x1, double init_y1) {
  this->x0 = init_x0;
  this->y0 = init_y0;
  this->x1 = init_x1;
  this->y1 = init_y1;
}

bool line::is_vertical() const { return x0 == x1; }

bool line::is_horizontal() const { return y0 == y1; }

bool line::contains(double x, double y) const {
  return (x - x0) == this->slope() * (y - y0);
}

bool line::is_parallel_to(const line &l) const {
  return this->slope() == l.slope();
}

double line::slope() const { return (y1 - y0) / (x1 - x0); }

double line::x_intercept() const {
  assert(!this->is_vertical());
  return y0 - (x0 * this->slope());
}

double line::y_intercept() const {
  assert(!this->is_horizontal());
  return x0 - (y0 * this->slope());
}

void line::print() const { printf("(%f, %f), (%f, %f)", x0, y0, x1, y1); }

void line::read() {
  printf("Enter x_1, y_1, x_2, y_2: ");
  std::cin >> x0 >> y0 >> x1 >> y1;
  assert(x0 != x1 && y0 != y1);
}
