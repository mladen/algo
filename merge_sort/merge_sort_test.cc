#include "merge_sort/merge_sort.h"

#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::IsEmpty;
using testing::ElementsAre;

TEST(MergeSortTest, Empty) {
  EXPECT_THAT(merge_sort(std::vector<int>{}), IsEmpty());
}

TEST(MergeSortTest, OneElement) {
  EXPECT_THAT(merge_sort(std::vector<int>{0}), ElementsAre(0));
  EXPECT_THAT(merge_sort(std::vector<int>{1}), ElementsAre(1));
}

TEST(MergeSortTest, TwoElements) {
  EXPECT_THAT(merge_sort(std::vector<int>{0, 1}), ElementsAre(0, 1));
  EXPECT_THAT(merge_sort(std::vector<int>{1, 0}), ElementsAre(0, 1));
}

TEST(MergeSortTest, ThreeElements) {
  EXPECT_THAT(merge_sort(std::vector<int>{0, 1, 2}), ElementsAre(0, 1, 2));
  EXPECT_THAT(merge_sort(std::vector<int>{0, 2, 1}), ElementsAre(0, 1, 2));
  EXPECT_THAT(merge_sort(std::vector<int>{1, 0, 2}), ElementsAre(0, 1, 2));
  EXPECT_THAT(merge_sort(std::vector<int>{1, 2, 0}), ElementsAre(0, 1, 2));
  EXPECT_THAT(merge_sort(std::vector<int>{2, 0, 1}), ElementsAre(0, 1, 2));
  EXPECT_THAT(merge_sort(std::vector<int>{2, 1, 0}), ElementsAre(0, 1, 2));
}

TEST(MergeSortTest, AllTheSame) {
  EXPECT_THAT(merge_sort(std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}),
              ElementsAre(0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
}

TEST(MergeSortTest, MoreElements) {
  EXPECT_THAT(merge_sort(std::vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}),
              ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
  EXPECT_THAT(merge_sort(std::vector<int>{5, 6, 7, 8, 9, 0, 1, 2, 3, 4}),
              ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
  EXPECT_THAT(merge_sort(std::vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}),
              ElementsAre(0, 1, 2, 3, 4, 5, 6, 7, 8, 9));
}
