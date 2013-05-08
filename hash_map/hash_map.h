#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include <cstddef>
#include <cassert>
#include <vector>
#include <forward_list>
#include <utility>

template <typename K, typename V>
class HashMap {
 public:
  HashMap()
      : HashMap(MIN_BUCKETS_SIZE)
  {}

  ~HashMap() = default;

  HashMap(HashMap&&)            = default;
  HashMap& operator=(HashMap&&) = default;

  HashMap(const HashMap&)            = default;
  HashMap& operator=(const HashMap&) = default;

  bool empty() const {
    return element_count_ == 0;
  }

  size_t size() const {
    return element_count_;
  }

  void insert(const K& key, const V& value) {
    remove(key);

    buckets_[bucket_index_of(key)].emplace_front(key, value);
    element_count_++;
    try_expand();
  }

  void remove(const K& key) {
    auto& bucket = buckets_[bucket_index_of(key)];
    for (auto it = bucket.before_begin(); std::next(it) != bucket.end(); ++it) {
      if (std::next(it)->first == key) {
        bucket.erase_after(it);
        element_count_--;
        try_shrink();
        return;
      }
    }
  }

  bool has_key(const K& key) const {
    return find(key) != not_found();
  }

  std::vector<K> keys() const {
    std::vector<K> ks;
    ks.reserve(element_count_);
    for (const auto& bucket : buckets_) {
      for (const auto& entry : bucket) {
        ks.push_back(entry.first);
      }
    }
    return ks;
  }

  V get(const K& key) const {
    assert(has_key(key));
    return find(key)->second;
  }

 private:
  static constexpr size_t MIN_BUCKETS_SIZE = 16;
  static constexpr double MAX_LOAD_FACTOR  = 0.75;
  static constexpr double MIN_LOAD_FACTOR  = MAX_LOAD_FACTOR / 2;

  typedef typename std::pair<K, V>          Entry;
  typedef typename std::forward_list<Entry> Bucket;
  typedef typename Bucket::const_iterator   const_iterator;

  explicit HashMap(size_t bucket_size)
      : buckets_(bucket_size)
  {}

  size_t bucket_index_of(const K& key) const {
    return hash_function_(key) % buckets_.size();
  }

  double load_factor() const {
    return 1.0 * element_count_ / buckets_.size();
  }

  void resize(size_t bucket_size) {
    HashMap new_map(bucket_size);
    for (auto k : keys()) {
      new_map.insert(k, get(k));
    }
    *this = new_map;
  }

  void try_expand() {
    if (load_factor() > MAX_LOAD_FACTOR) {
      resize(2 * buckets_.size());
    }
  }

  void try_shrink() {
    if (buckets_.size() / 2 >= MIN_BUCKETS_SIZE &&
        load_factor() < MIN_LOAD_FACTOR) {
      resize(buckets_.size() / 2);
    }
  }

  const_iterator find(const K& key) const {
    auto& bucket = buckets_[bucket_index_of(key)];
    for (auto it = std::begin(bucket); it != std::end(bucket); ++it) {
      if (it->first == key) {
        return it;
      }
    }
    return not_found();
  }

  static constexpr const_iterator not_found() {
    return const_iterator(nullptr);
  }

  size_t              element_count_ = 0;
  std::hash<K>        hash_function_;
  std::vector<Bucket> buckets_;
};

#endif  // HASH_MAP_H_
