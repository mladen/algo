#ifndef MULTIWAY_TRIE_H_
#define MULTIWAY_TRIE_H_

#include <string>
#include <vector>
#include <memory>

class MultiwayTrie {
 public:
  MultiwayTrie();
  ~MultiwayTrie();

  MultiwayTrie(MultiwayTrie&&)            = default;
  MultiwayTrie& operator=(MultiwayTrie&&) = default;

  MultiwayTrie(const MultiwayTrie&)            = delete;
  MultiwayTrie& operator=(const MultiwayTrie&) = delete;

  void add(const std::string& pattern);

  std::vector<std::string> prefixes_of(const std::string& text) const;

 private:
  struct Node;

  std::unique_ptr<Node> root_;
};

#endif  // MULTIWAY_TRIE_H_
