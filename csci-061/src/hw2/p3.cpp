#include <vector>

/// This assumes that only the root node is (potentially) out of place and the
/// two subheaps to its left and right are both valid
void __heapify(int *v, int size, int n) {
  int l = n * 2 + 1;
  int r = n * 2 + 2;

  // if
  // - both nodes are valid AND
  // - the minimum of all three nodes is the right
  // then
  // - swap the node and right
  // - heapify the right
  if (r < size && v[r] < v[n] && v[r] <= v[l]) {
    // swap
    int t = v[r];
    v[r] = v[n];
    v[n] = t;

    __heapify(v, size, r);

    // dont run the second conditon
    return;
  }

  // given
  // - the right is either
  //  - greater than root OR
  //  - doesnt exist
  // if
  // - the left is vaild AND
  // - less than the node
  // then
  // - swap the node and right AND
  // - heapify the right
  //
  // # Notes
  // The preconditon of r means that l < n insures l < r
  if (l < size && v[l] < v[n]) {

    // swap
    int t = v[l];
    v[l] = v[n];
    v[n] = t;

    __heapify(v, size, l);
  }

  // if neither r nor l is valid then this is a leaf node and has nothing to
  // swap with. In terms of optimizations all the comparisons are short
  // ciruitings so there will still only be two comparisons for this case.
}

/// Implement the heapification operation.
/// Assume that you have an array of integers. You may choose max
/// or min heap and you may choose whichever method discussed in class
void heapify(std::vector<int> &v) { __heapify(v.data(), v.size(), 0); }

// BAD TESTER
#include <iostream>
int main(int argc, char *argv[]) {
  std::vector<int> v{2, 32, -1, 33, 72, 0, 9, 56};

  for (auto d : v) {
    std::cout << d << ", ";
  }
  std::cout << "\n";

  heapify(v);

  for (auto d : v) {
    std::cout << d << ", ";
  }
  std::cout << "\n";

  // TODO
  return 0;
}
