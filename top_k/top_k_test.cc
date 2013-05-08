#include "top_k/top_k.h"

#include <vector>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using std::vector;

using testing::IsEmpty;
using testing::ElementsAre;
using testing::WhenSorted;

TEST(TopKTest, NumberOfElementsLessThanK) {
  EXPECT_DEATH(top_k(vector<int>{}, 1), "");
}

TEST(TopKTest, Empty) {
  EXPECT_THAT(top_k(vector<int>{}, 0), WhenSorted(IsEmpty()));
}

TEST(TopKTest, OneElement) {
  EXPECT_THAT(top_k(vector<int>{0}, 1), WhenSorted(ElementsAre(0)));
}

TEST(TopKTest, TwoElements) {
  EXPECT_THAT(top_k(vector<int>{0, 1}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{1, 0}, 1), WhenSorted(ElementsAre(0)));

  EXPECT_THAT(top_k(vector<int>{0, 1}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{1, 0}, 2), WhenSorted(ElementsAre(0, 1)));
}

TEST(TopKTest, ThreeElements) {
  EXPECT_THAT(top_k(vector<int>{0, 1, 2}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{1, 0, 2}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{0, 2, 1}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{1, 2, 0}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{2, 0, 1}, 1), WhenSorted(ElementsAre(0)));
  EXPECT_THAT(top_k(vector<int>{2, 1, 0}, 1), WhenSorted(ElementsAre(0)));

  EXPECT_THAT(top_k(vector<int>{0, 1, 2}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{1, 0, 2}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{0, 2, 1}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{1, 2, 0}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{2, 0, 1}, 2), WhenSorted(ElementsAre(0, 1)));
  EXPECT_THAT(top_k(vector<int>{2, 1, 0}, 2), WhenSorted(ElementsAre(0, 1)));

  EXPECT_THAT(top_k(vector<int>{0, 1, 2}, 3), WhenSorted(ElementsAre(0, 1, 2)));
  EXPECT_THAT(top_k(vector<int>{1, 0, 2}, 3), WhenSorted(ElementsAre(0, 1, 2)));
  EXPECT_THAT(top_k(vector<int>{0, 2, 1}, 3), WhenSorted(ElementsAre(0, 1, 2)));
  EXPECT_THAT(top_k(vector<int>{1, 2, 0}, 3), WhenSorted(ElementsAre(0, 1, 2)));
  EXPECT_THAT(top_k(vector<int>{2, 0, 1}, 3), WhenSorted(ElementsAre(0, 1, 2)));
  EXPECT_THAT(top_k(vector<int>{2, 1, 0}, 3), WhenSorted(ElementsAre(0, 1, 2)));
}

TEST(TopKTest, AllTheSame) {
  EXPECT_THAT(top_k(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 5),
              WhenSorted(ElementsAre(0, 0, 0, 0, 0)));
}

TEST(TopKTest, MoreElements) {
  EXPECT_THAT(top_k(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 5),
              WhenSorted(ElementsAre(0, 1, 2, 3, 4)));
  EXPECT_THAT(top_k(vector<int>{5, 6, 7, 8, 9, 0, 1, 2, 3, 4}, 5),
              WhenSorted(ElementsAre(0, 1, 2, 3, 4)));
  EXPECT_THAT(top_k(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 5),
              WhenSorted(ElementsAre(0, 1, 2, 3, 4)));
}
