/// --------------------------------- slice.h ------------------------------ ///
#ifndef SLICEH
#define SLICEH 1

#include <cstddef>
#include <tuple>
#include "cslice.h"

/// Repersents an array in memory.
///
/// Invariants: start < end and all the memory between the pointers is allocated
template <typename T> class Slice {
public:
  T *start;
  T *end;

  Slice(T *start, T *end);

  std::tuple<ConstSlice<T>, ConstSlice<T>> split_at(size_t i) const;
  std::tuple<Slice<T>, Slice<T>> split_at_mut(size_t i);

  size_t len() const;

  void set(size_t i, T v);

  const T &get(size_t i) const;
  T &get_mut(size_t i);

  /// returns of subslice of range from the two bounds, panics if bounds are
  /// invalid.
  Slice<T> sub_slice(size_t, size_t) const;
  /// return a subslice of range from the start bound to the end.
  Slice<T> sub_slice(size_t) const;
};

#endif // !SLICEH
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ slice.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
