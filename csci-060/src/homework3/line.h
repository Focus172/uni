#ifndef LINE_H
#define LINE_H

#include <iostream>

class line {
public:
  // pre-condition: (init_x0, init_y0) and (init_x1, init_y1) are different
  // points post-condition:  this line has been initialized with the given
  // points
  line(double init_x0 = 0.0, double init_y0 = 0.0, double init_x1 = 1.0,
       double init_y1 = 0.0); // constructor

  bool is_vertical() const;
  //  pre-condition: none
  //  post-condition: true if this line is vertical

  bool is_horizontal() const;
  // pre-condition: none
  // post-condition: true if this line is horizontal

  bool contains(double x, double y) const;
  // pre-condition: none
  // post-condition: true if (x, y) is on this line

  bool is_parallel_to(const line &l) const;
  // pre-condition: none
  // post-condition: true if this line is parallel to line l

  double slope() const;
  // pre-condition: this line is not vertical;
  // post-condition: slope of this line is returned

  double x_intercept() const;
  // pre-condition: this line is not horizontal
  // post-condition: x-intercept of this line is returned

  /// Returns the y-intercept of the line.
  ///
  /// # Safety
  /// This function has undefined behavior weh the line is vertical
  double y_intercept() const;

  /// Outputs line in format "(x0, y0), (x1, y1)" to stdout
  void print() const;

  /// Reads in the line from stdin, replacing the content in it.
  /// reads new values for x0, y0, x1, y1 from input
  ///
  /// # Panics
  /// panics if (x0, y0) != (x1, y 1) for the new line
  void read();

private:
  double x0, y0, x1, y1;
  // invariant: (x0, y0) and (x1, y1) are two distinct points
  //            on the line
};

#endif // LINE_H
