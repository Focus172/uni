//  Classes are similar to structs.
// You use classes when you want to add complicated functions to the objects.
//  Example of a class for triangles represented by three vertices.
#include <cmath>
#include <iostream>
using namespace std;
struct Point {
  double x;
  double y;
};

class Triangle {
private:
  Point vertex1;
  Point vertex2;
  Point vertex3;

public:
  // Constructor for initializing triangle
  Triangle(Point v1, Point v2, Point v3) {
    vertex1 = v1;
    vertex2 = v2;
    vertex3 = v3;
  }

  // Calculate the distance between two points
  double distance(Point p1, Point p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx * dx + dy * dy);
  }

  // Check if the three points form a valid triangle
  bool isValid() {
    double side1 = distance(vertex1, vertex2);
    double side2 = distance(vertex2, vertex3);
    double side3 = distance(vertex3, vertex1);
    // Find the longest side and sum of two smaller sides
    double max_side = max(max(side1, side2), side3);
    double smaller_sides = side1 + side2 + side3 - max_side;
    // Check if the longest side is smaller than the sum of
    // other two sides
    return max_side < smaller_sides;
  }

  // Calculate the perimeter of the triangle
  double perimeter() {
    double side1 = distance(vertex1, vertex2);
    double side2 = distance(vertex2, vertex3);
    double side3 = distance(vertex3, vertex1);
    return side1 + side2 + side3;
  }

  bool is_right() {
    double side1 = distance(vertex1, vertex2);
    double side2 = distance(vertex2, vertex3);
    double side3 = distance(vertex3, vertex1);

    double sq1 = side1 * side1;
    double sq2 = side2 * side2;
    double sq3 = side3 * side3;

    return (sq1 + sq2 == sq3) || (sq1 + sq3 == sq2) || (sq3 + sq2 == sq1);
  }

  double area() {
    double s = this->perimeter() / 2;
    double side1 = distance(vertex1, vertex2);
    double side2 = distance(vertex2, vertex3);
    double side3 = distance(vertex3, vertex1);
    return sqrt(s * (s - side1) * (s - side2) * (s - side3));
  }
};

int main() {
  Point p1;
  p1.x = 0;
  p1.y = 0;
  Point p2;
  p2.x = 3;
  p2.y = 0;
  Point p3;
  p3.x = 0;
  p3.y = 4;
  Triangle t(p1, p2, p3);
  if (t.isValid())
    cout << "This is a valid triangle." << endl;
  else
    cout << "This is not a valid triangle." << endl;
  cout << "Perimeter of the triangle: " << t.perimeter() << endl;

  if (t.is_right()) {
    cout << "It is a right triangle" << endl;
  } else {
    cout << "It is not a right triangle" << endl;
  }

  cout << "Area of the triangle: " << t.area() << endl;

  return 0;
}
