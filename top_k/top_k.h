#ifndef TOP_K_H_
#define TOP_K_H_

#include <cassert>
#include <algorithm>

namespace detail {

template <typename RandomIt>
void top_k_in_place(RandomIt first, RandomIt last, long k) {
  assert(last - first >= k);

  if (last - first == k) return;

  auto pivot = *first;

  RandomIt left  = first + 1;
  RandomIt right = last  - 1;

  while (true) {
    while (left  <  last  && *left  < pivot) ++left;
    while (right >= first && pivot < *right) --right;

    if (left >= right) break;

    std::iter_swap(left++, right--);
  }

  std::iter_swap(first, left - 1);

  long elements_before_pivot = left - first;
  if (elements_before_pivot < k) {
    top_k_in_place(left, last, k - elements_before_pivot);
  } else if (elements_before_pivot > k) {
    top_k_in_place(first, left - 1, k);
  }
}

}  // namespace detail

template <typename Container>
Container top_k(Container xs, int k) {
  assert(xs.size() >= k);

#ifndef DEBUG
  std::random_shuffle(std::begin(xs), std::end(xs));
#endif

  detail::top_k_in_place(std::begin(xs), std::end(xs), k);
  xs.resize(k);

  return xs;
}

#endif  // TOP_K_H_
