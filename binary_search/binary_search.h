#ifndef BINARY_SEARCH_H_
#define BINARY_SEARCH_H_

// Returns an iterator pointing to
// the _first_ element equal to `key` in [`first`, `last`),
// or `last` if not found.
template <typename T, typename RandomIt>
RandomIt binary_search(const T& key, RandomIt first, RandomIt last) {
  if (first >= last) return last;

  RandomIt left  = first;
  RandomIt right = last - 1;

  while (left < right) {
    RandomIt middle = left + (right - left) / 2;
    if (*middle < key) left  = middle + 1;
    else               right = middle;
  }

  return (*left == key) ? left : last;
}

#endif  // BINARY_SEARCH_H_
