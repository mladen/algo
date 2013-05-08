#ifndef RADIX_SORT_H_
#define RADIX_SORT_H_

#include <cassert>
#include <climits>
#include <vector>
#include <algorithm>
#include <type_traits>

namespace detail {

template <typename Container>
int longest_digit_length(const Container& xs, int radix) {
  assert(!xs.empty());

  auto max   = *std::max_element(std::begin(xs), std::end(xs));
  int  count = 1;
  while ((max /= radix) > 0) count++;
  return count;
}

template <typename Integral>
Integral flip_first_bit(Integral x) {
  return x ^ (1 << (CHAR_BIT * sizeof(x) - 1));
}

}  // namespace detail

template <typename Container>
Container radix_sort(const Container& xs, int radix = 10) {
  static_assert(std::is_integral<typename Container::value_type>::value,
                "Elements should be integral.");

  assert(radix >= 2);

  typedef typename Container::value_type              Integral;
  typedef typename std::make_unsigned<Integral>::type UIntegral;

  if (xs.size() < 2) return xs;

  std::vector<UIntegral> xs_unsigned(std::begin(xs), std::end(xs));
  if (std::is_signed<Integral>::value) {
    std::transform(std::begin(xs_unsigned), std::end(xs_unsigned),
                   std::begin(xs_unsigned),
                   detail::flip_first_bit<UIntegral>);
  }

  UIntegral power = 1;
  for (int t = detail::longest_digit_length(xs_unsigned, radix); t > 0; t--) {
    std::vector<std::vector<UIntegral>> buckets(radix);

    for (auto x : xs_unsigned) {
      buckets[x / power % radix].push_back(x);
    }

    xs_unsigned.clear();

    for (const auto& bucket : buckets) {
      std::copy(std::begin(bucket), std::end(bucket),
                std::back_inserter(xs_unsigned));
    }

    power *= radix;
  }

  Container result(std::begin(xs_unsigned), std::end(xs_unsigned));
  if (std::is_signed<Integral>::value) {
    std::transform(std::begin(result), std::end(result),
                   std::begin(result),
                   detail::flip_first_bit<Integral>);
  }

  return result;
}

#endif  // RADIX_SORT_H_
