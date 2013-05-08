#include "binary_search/binary_search.h"

#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::begin;
using std::end;

using testing::Eq;

TEST(BinarySearchTest, Empty) {
  std::vector<int> xs;
  EXPECT_THAT(binary_search(0, begin(xs), end(xs)), Eq(end(xs)));
}

TEST(BinarySearchTest, OneElement) {
  std::vector<int> xs{1};
  EXPECT_THAT(binary_search(0, begin(xs), end(xs)), Eq(end(xs)));
  EXPECT_THAT(binary_search(1, begin(xs), end(xs)), Eq(begin(xs)));
  EXPECT_THAT(binary_search(2, begin(xs), end(xs)), Eq(end(xs)));
}

TEST(BinarySearchTest, TwoElements) {
  std::vector<int> xs{1, 2};
  EXPECT_THAT(binary_search(0, begin(xs), end(xs)), Eq(end(xs)));
  EXPECT_THAT(binary_search(1, begin(xs), end(xs)), Eq(begin(xs)));
  EXPECT_THAT(binary_search(2, begin(xs), end(xs)), Eq(begin(xs) + 1));
  EXPECT_THAT(binary_search(3, begin(xs), end(xs)), Eq(end(xs)));
}

TEST(BinarySearchTest, ThreeElements) {
  std::vector<int> xs{1, 2, 3};
  EXPECT_THAT(binary_search(0, begin(xs), end(xs)), Eq(end(xs)));
  EXPECT_THAT(binary_search(1, begin(xs), end(xs)), Eq(begin(xs)));
  EXPECT_THAT(binary_search(2, begin(xs), end(xs)), Eq(begin(xs) + 1));
  EXPECT_THAT(binary_search(3, begin(xs), end(xs)), Eq(begin(xs) + 2));
  EXPECT_THAT(binary_search(4, begin(xs), end(xs)), Eq(end(xs)));
}


TEST(BinarySearchTest, Duplicate) {
  std::vector<int> xs{1, 1, 2, 2, 3, 3, 4, 4};
  EXPECT_THAT(binary_search(0, begin(xs), end(xs)), Eq(end(xs)));
  EXPECT_THAT(binary_search(1, begin(xs), end(xs)), Eq(begin(xs)));
  EXPECT_THAT(binary_search(2, begin(xs), end(xs)), Eq(begin(xs) + 2));
  EXPECT_THAT(binary_search(3, begin(xs), end(xs)), Eq(begin(xs) + 4));
  EXPECT_THAT(binary_search(4, begin(xs), end(xs)), Eq(begin(xs) + 6));
  EXPECT_THAT(binary_search(5, begin(xs), end(xs)), Eq(end(xs)));
}

TEST(BinarySearchTest, MoreElements) {
  std::vector<int> xs{1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_THAT(binary_search(0,  begin(xs), end(xs)), Eq(end(xs)));
  EXPECT_THAT(binary_search(1,  begin(xs), end(xs)), Eq(begin(xs)));
  EXPECT_THAT(binary_search(5,  begin(xs), end(xs)), Eq(begin(xs) + 4));
  EXPECT_THAT(binary_search(9,  begin(xs), end(xs)), Eq(begin(xs) + 8));
  EXPECT_THAT(binary_search(10, begin(xs), end(xs)), Eq(end(xs)));
}
