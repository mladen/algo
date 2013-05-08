#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include <cassert>
#include <vector>
#include <algorithm>
#include <functional>

template <typename E, typename Less = std::less<E>>
class MinHeap {
 public:
  MinHeap()  = default;
  ~MinHeap() = default;

  MinHeap(MinHeap&&)            = default;
  MinHeap& operator=(MinHeap&&) = default;

  MinHeap(const MinHeap&)            = default;
  MinHeap& operator=(const MinHeap&) = default;

  bool empty() const {
    return elements_.empty();
  }

  size_t size() const {
    return elements_.size();
  }

  void insert(const E& x) {
    elements_.push_back(x);
    swim(size() - 1);
  }

  void delete_min() {
    assert(!empty());
    std::swap(elements_[0], elements_[size() - 1]);
    elements_.pop_back();
    sink(0);
  }

  E min() const {
    assert(!empty());
    return elements_[0];
  }

 private:
  static size_t parent_index_of(size_t i) {
    return (i - 1) / 2;
  }

  static size_t left_child_index_of(size_t i) {
    return i * 2 + 1;
  }

  static size_t right_child_index_of(size_t i) {
    return left_child_index_of(i) + 1;
  }

  void swim(size_t i) {
    while (i > 0 && less_(elements_[i], elements_[parent_index_of(i)])) {
      std::swap(elements_[i], elements_[parent_index_of(i)]);
      i = parent_index_of(i);
    }
  }

  void sink(size_t i) {
    while (left_child_index_of(i) < size()) {
      size_t min_child_index = left_child_index_of(i);

      if (right_child_index_of(i) < size() &&
          less_(elements_[right_child_index_of(i)],
                elements_[min_child_index])) {
        min_child_index = right_child_index_of(i);
      }

      if (less_(elements_[i], elements_[min_child_index])) break;

      std::swap(elements_[i], elements_[min_child_index]);
      i = min_child_index;
    }
  }

  std::vector<E> elements_;
  Less           less_;
};

#endif  // MIN_HEAP_H_
