#include "trie/ternary_search_trie.h"

#include <cassert>

struct TernarySearchTrie::Node {
  char                  key;
  bool                  accept = false;
  std::unique_ptr<Node> left;
  std::unique_ptr<Node> middle;
  std::unique_ptr<Node> right;
};

TernarySearchTrie::TernarySearchTrie() = default;

TernarySearchTrie::~TernarySearchTrie() = default;

void TernarySearchTrie::add(const std::string& pattern) {
  assert(!pattern.empty());
  add_aux(pattern, &root_);
}

void TernarySearchTrie::add_aux(const std::string& pattern,
                                std::unique_ptr<Node>* node) {
  char  c = pattern[0];
  auto& p = *node;

  if (!p) {
    p.reset(new Node);
    p->key = c;
  }

  if (c < p->key) {
    add_aux(pattern, &p->left);
  } else if (c > p->key) {
    add_aux(pattern, &p->right);
  } else if (pattern.size() > 1) {
    add_aux(pattern.substr(1), &p->middle);
  } else {
    p->accept = true;
  }
}

std::vector<std::string>
TernarySearchTrie::prefixes_of(const std::string& text) const {
  std::vector<std::string> prefixes;

  Node* node = root_.get();
  for (size_t i = 0; i < text.size() && node; /* no-op */) {
    char c = text[i];

    if (c < node->key) {
      node = node->left.get();
    } else if (c > node->key) {
      node = node->right.get();
    } else {
      if (node->accept) {
        prefixes.push_back(text.substr(0, i + 1));
      }
      node = node->middle.get();
      i++;
    }
  }

  return prefixes;
}
