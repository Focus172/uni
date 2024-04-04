/// ------------------------------ util.h ---------------------------------- ///
#include "biguint.h"
#include "cslice.h"
#include "slice.h"
#include <cstdint>
#include <tuple>

typedef Slice<uint32_t> MutU32Slice;
typedef ConstSlice<uint32_t> U32Slice;

/// Orders the slice by their length, the shorter slice is returned in the
/// first position.
std::tuple<U32Slice, U32Slice> order_lengths(const U32Slice, const U32Slice);

/// Add and carry operation
///
/// Adds the numbers together with overflow storing value into `out`
///
/// Return the overflow (always either 0 or 1).
uint32_t adc(uint32_t a, uint32_t b, uint32_t &out);

/// subtract with a borrow.
uint32_t sbb(uint32_t borrow, uint32_t a, uint32_t b, uint32_t &out);

/// Multiply accumulate where the second argument is only 1 diget.
/// In essance does this:
/// acc += b * c
void mac_digit(MutU32Slice acc, const U32Slice b, const uint32_t c);

/// Multiply Accumulate.
/// `acc += b * c`
void mac(MutU32Slice acc, const U32Slice b, const U32Slice c);

std::tuple<biguint, biguint> div_rem(const biguint, const biguint);

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ util.h ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ ///
