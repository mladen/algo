#ifndef HEAP_SORT_H_
#define HEAP_SORT_H_

#include "min_heap/min_heap.h"

template <typename Container>
Container heap_sort(const Container& xs) {
  typedef typename Container::value_type E;

  MinHeap<E> heap;
  Container  result;

  for (auto x : xs) {
    heap.insert(x);
  }

  while (!heap.empty()) {
    result.push_back(heap.min());
    heap.delete_min();
  }

  return result;
}

#endif  // HEAP_SORT_H_
