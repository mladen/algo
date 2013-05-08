#ifndef QUICK_SORT_H_
#define QUICK_SORT_H_

#include <algorithm>

namespace detail {

template <typename RandomIt>
void quick_sort_in_place(RandomIt first, RandomIt last) {
  if (last - first < 2) return;

  auto pivot = *first;

  RandomIt last_lt  = first;
  RandomIt last_eq  = first + 1;
  RandomIt first_gt = last;

  while (last_eq < first_gt) {
    if (*last_eq < pivot) {
      std::iter_swap(last_eq++, last_lt++);
    } else if (pivot < *last_eq) {
      std::iter_swap(last_eq, --first_gt);
    } else {
      ++last_eq;
    }
  }

  quick_sort_in_place(first,    last_lt);
  quick_sort_in_place(first_gt, last);
}

}  // namespace detail

template <typename Container>
Container quick_sort(Container xs) {
#ifndef DEBUG
  std::random_shuffle(std::begin(xs), std::end(xs));
#endif

  detail::quick_sort_in_place(std::begin(xs), std::end(xs));

  return xs;
}

#endif  // QUICK_SORT_H_
