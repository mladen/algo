#ifndef TERNARY_SEARCH_TRIE_H_
#define TERNARY_SEARCH_TRIE_H_

#include <string>
#include <vector>
#include <memory>

class TernarySearchTrie {
 public:
  TernarySearchTrie();
  ~TernarySearchTrie();

  TernarySearchTrie(TernarySearchTrie&&)            = default;
  TernarySearchTrie& operator=(TernarySearchTrie&&) = default;

  TernarySearchTrie(const TernarySearchTrie&)            = delete;
  TernarySearchTrie& operator=(const TernarySearchTrie&) = delete;

  void add(const std::string& pattern);

  std::vector<std::string> prefixes_of(const std::string& text) const;

 private:
  struct Node;

  static void add_aux(const std::string& pattern, std::unique_ptr<Node>* node);

  std::unique_ptr<Node> root_;
};

#endif  // TERNARY_SEARCH_TRIE_H_
