#include "trie/multiway_trie.h"

#include <cassert>
#include <unordered_map>

struct MultiwayTrie::Node {
  bool                                            accept = false;
  std::unordered_map<char, std::unique_ptr<Node>> next;
};

MultiwayTrie::MultiwayTrie()
    : root_(new Node)
{}

MultiwayTrie::~MultiwayTrie() = default;

void MultiwayTrie::add(const std::string& pattern) {
  assert(!pattern.empty());

  Node* node = root_.get();
  for (char c : pattern) {
    if (node->next.find(c) == node->next.end()) {
      node->next[c].reset(new Node);
    }
    node = node->next[c].get();
  }
  node->accept = true;
}

std::vector<std::string>
MultiwayTrie::prefixes_of(const std::string& text) const {
  std::vector<std::string> prefixes;

  Node* node = root_.get();
  for (size_t i = 0; i < text.size(); i++) {
    char c = text[i];
    if (node->next.find(c) == node->next.end()) break;
    node = node->next[c].get();

    if (node->accept) {
      prefixes.push_back(text.substr(0, i + 1));
    }
  }

  return prefixes;
}
