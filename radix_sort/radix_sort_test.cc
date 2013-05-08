#include "radix_sort/radix_sort.h"

#include <climits>
#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;

using testing::IsEmpty;
using testing::ElementsAre;

TEST(RadixSortTest, Empty) {
  EXPECT_THAT(radix_sort(vector<int>{}), IsEmpty());
}

TEST(RadixSortTest, OneElement) {
  EXPECT_THAT(radix_sort(vector<int>{0}), ElementsAre(0));
  EXPECT_THAT(radix_sort(vector<int>{1}), ElementsAre(1));
}

TEST(RadixSortTest, AllTheSame) {
  EXPECT_THAT(radix_sort(vector<int>{0, 0, 0}), ElementsAre(0, 0, 0));
}

TEST(RadixSortTest, DifferentLengths) {
  EXPECT_THAT(radix_sort(vector<int>{1, 20, 300}), ElementsAre(1, 20, 300));
  EXPECT_THAT(radix_sort(vector<int>{100, 20, 3}), ElementsAre(3, 20, 100));
}

TEST(RadixSortTest, Negative) {
  EXPECT_THAT(radix_sort(vector<int>{-100, 0, 99}),  ElementsAre(-100, 0, 99));
  EXPECT_THAT(radix_sort(vector<int>{-99,  0, 100}), ElementsAre(-99,  0, 100));
}

TEST(RadixSortTest, Unsigned) {
  EXPECT_THAT(radix_sort(vector<unsigned>{0, INT_MAX, UINT_MAX}),
              ElementsAre(0, INT_MAX, UINT_MAX));
}
