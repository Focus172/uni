#include <cstdint>
#include <cstdio>
#include <iostream>
#include <type_traits>

using namespace std;

struct Point {
  double x;
  double y;
};

Point average_of_list(Point *, int);

int main() {
  int N;
  cout << "Enter the number of points (N): ";
  cin >> N;
  Point points[N]; // Declare an array to store the points
  // Read N points from the user
  for (int i = 0; i < N; i++) {
    cout << "Enter the x-coordinate of point " << i + 1 << ": ";
    cin >> points[i].x;
    cout << "Enter the y-coordinate of point " << i + 1 << ": ";
    cin >> points[i].y;
  }
  // Display the entered points
  cout << "You entered the following points:" << endl;
  for (int i = 0; i < N; i++) {
    cout << "Point " << i + 1 << ": (" << points[i].x;
    cout << ", " << points[i].y << ")" << endl;
  }
  auto p = average_of_list(points, N);

  printf("Average of the points is: (%f, %f)\n", p.x, p.y);
  return 0; // Exit program successfully
}

Point average_of_list(Point *points, int len) {
  Point ret;
  for (int i = 0; i < len; i++) {
    auto p = points[i];
    ret.x += p.x;
    ret.y += p.y;
  }
  ret.x /= len;
  ret.y /= len;
  return ret;
}
