#include "trie/multiway_trie.h"
#include "trie/ternary_search_trie.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::IsEmpty;
using testing::ElementsAre;

template <typename TRIE>
class TrieTest : public testing::Test {
 protected:
  TRIE trie_;
};

typedef testing::Types<MultiwayTrie, TernarySearchTrie> Implementations;
TYPED_TEST_CASE(TrieTest, Implementations);

TYPED_TEST(TrieTest, RejectEmptyPattern) {
  EXPECT_DEATH(this->trie_.add(""), "");
}

TYPED_TEST(TrieTest, NoPatterns) {
  EXPECT_THAT(this->trie_.prefixes_of(""),  IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("a"), IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("a"), IsEmpty());
}

TYPED_TEST(TrieTest, NoMatches) {
  this->trie_.add("b");
  this->trie_.add("a");
  this->trie_.add("c");
  EXPECT_THAT(this->trie_.prefixes_of("def"), IsEmpty());
}

TYPED_TEST(TrieTest, OnePattern) {
  this->trie_.add("bac");
  EXPECT_THAT(this->trie_.prefixes_of(""),     IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("a"),    IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("b"),    IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("ba"),   IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("bac"),  ElementsAre("bac"));
  EXPECT_THAT(this->trie_.prefixes_of("bacd"), ElementsAre("bac"));
}

TYPED_TEST(TrieTest, Distract) {
  this->trie_.add("edf");
  this->trie_.add("abc");
  this->trie_.add("gih");
  EXPECT_THAT(this->trie_.prefixes_of("abc"), ElementsAre("abc"));
  EXPECT_THAT(this->trie_.prefixes_of("edf"), ElementsAre("edf"));
  EXPECT_THAT(this->trie_.prefixes_of("gih"), ElementsAre("gih"));
  EXPECT_THAT(this->trie_.prefixes_of("aeg"), IsEmpty());
}

TYPED_TEST(TrieTest, Overlap) {
  this->trie_.add("b");
  this->trie_.add("ba");
  this->trie_.add("bac");
  EXPECT_THAT(this->trie_.prefixes_of(""),     IsEmpty());
  EXPECT_THAT(this->trie_.prefixes_of("b"),    ElementsAre("b"));
  EXPECT_THAT(this->trie_.prefixes_of("ba"),   ElementsAre("b", "ba"));
  EXPECT_THAT(this->trie_.prefixes_of("bac"),  ElementsAre("b", "ba", "bac"));
  EXPECT_THAT(this->trie_.prefixes_of("bacd"), ElementsAre("b", "ba", "bac"));
}

TYPED_TEST(TrieTest, Chinese) {
  this->trie_.add("中文");
  EXPECT_THAT(this->trie_.prefixes_of("中文字符串"), ElementsAre("中文"));
}
