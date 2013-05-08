#ifndef UNION_FIND_H_
#define UNION_FIND_H_

#include <unordered_map>

template <typename E>
class UnionFind {
 public:
  UnionFind()  = default;
  ~UnionFind() = default;

  UnionFind(UnionFind&&)            = default;
  UnionFind& operator=(UnionFind&&) = default;

  UnionFind(const UnionFind&)            = default;
  UnionFind& operator=(const UnionFind&) = default;

  E find_root(const E& x) {
    auto found = parents_.find(x);

    if (found == std::end(parents_) || parents_[x] == x) {
      parents_[x] = x;
      return x;
    }

    return (parents_[x] = find_root(parents_[x]));
  }

  void union_sets(const E& x, const E& y) {
    E root_of_x = find_root(x);
    E root_of_y = find_root(y);

    if (root_of_x != root_of_y) {
      parents_[root_of_x] = root_of_y;
    }
  }

 private:
  std::unordered_map<E, E> parents_;
};

#endif  // UNION_FIND_H_
