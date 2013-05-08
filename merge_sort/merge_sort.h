#ifndef MERGE_SORT_H_
#define MERGE_SORT_H_

#include <algorithm>

namespace detail {

template <typename ForwardIt>
void merge_with_buffer(ForwardIt first, ForwardIt middle, ForwardIt last,
                       ForwardIt buffer_first) {
  ForwardIt first1      = first;
  ForwardIt first2      = middle;
  ForwardIt buffer_last = buffer_first;

  while (first1 < middle && first2 < last) {
    if (*first1 < *first2) {
      *buffer_last++ = *first1++;
    } else {
      *buffer_last++ = *first2++;
    }
  }

  std::copy(first1, middle, buffer_last);
  std::copy(first2, last,   buffer_last);

  std::copy_n(buffer_first, std::distance(first, last), first);
}

template <typename RandomIt>
void merge_sort_in_place(RandomIt first, RandomIt last,
                         RandomIt buffer_first) {
  if (last - first < 2) return;

  RandomIt middle = first + (last - first) / 2;
  merge_sort_in_place(first,  middle, buffer_first);
  merge_sort_in_place(middle, last,   buffer_first);

  merge_with_buffer(first, middle, last, buffer_first);
}

}  // namespace detail

template <typename Container>
Container merge_sort(Container xs) {
  Container buffer(xs.size());

  detail::merge_sort_in_place(std::begin(xs), std::end(xs), std::begin(buffer));

  return xs;
}

#endif  // MERGE_SORT_H_
