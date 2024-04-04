/// -------------------------------- cslice.h ------------------------------ ///
#ifndef CONST_SLICE_H
#define CONST_SLICE_H 1

#include <cstddef>
#include <tuple>

/// Repersents an array in memory.
///
/// Invariants: start < end and all the memory between the pointers is allocated
template <typename T> class ConstSlice {
public:
  const T *start;
  const T *end;

  ConstSlice(const T *start, const T *end);

  std::tuple<ConstSlice<T>, ConstSlice<T>> split_at(size_t i);

  /// Returns the length of the slice
  size_t len() const;

  /// Gets a const referance to the value at the index panicing if out of
  /// bounds.
  const T &get(size_t i) const;

  /// returns of subslice of range from the two bounds, panics if bounds are
  /// invalid.
  ConstSlice<T> sub_slice(size_t, size_t) const;
  /// return a subslice of range from the start bound to the end.
  ConstSlice<T> sub_slice(size_t) const;
};

#endif // !CONST_SLICE_H
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ cslice.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
