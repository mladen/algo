#include "min_heap/min_heap.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;

TEST(MinHeapTest, Empty) {
  MinHeap<int> h;

  EXPECT_THAT(h.empty(), Eq(true));
  EXPECT_THAT(h.size(),  Eq(0));

  EXPECT_DEATH(h.delete_min(), "");
  EXPECT_DEATH(h.min(),        "");
}

TEST(MinHeapTest, OneElement) {
  MinHeap<int> h;

  h.insert(0);

  EXPECT_THAT(h.empty(), Eq(false));
  EXPECT_THAT(h.size(),  Eq(1));
  EXPECT_THAT(h.min(),   Eq(0));

  h.delete_min();

  EXPECT_THAT(h.empty(), Eq(true));
  EXPECT_THAT(h.size(),  Eq(0));
}

TEST(MinHeapTest, AllTheSame) {
  MinHeap<int> h;

  h.insert(0);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(0);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(0);
  EXPECT_THAT(h.min(), Eq(0));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(0));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(0));
  h.delete_min();

  EXPECT_THAT(h.empty(), Eq(true));
}

TEST(MinHeapTest, MoreElements) {
  MinHeap<int> h;

  h.insert(2);
  EXPECT_THAT(h.min(), Eq(2));
  h.insert(1);
  EXPECT_THAT(h.min(), Eq(1));
  h.insert(0);
  EXPECT_THAT(h.min(), Eq(0));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(1));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(2));
  h.delete_min();

  EXPECT_THAT(h.empty(), Eq(true));

  h.insert(0);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(9);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(1);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(8);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(2);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(7);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(3);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(6);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(4);
  EXPECT_THAT(h.min(), Eq(0));
  h.insert(5);
  EXPECT_THAT(h.min(), Eq(0));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(1));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(2));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(3));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(4));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(5));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(6));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(7));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(8));
  h.delete_min();
  EXPECT_THAT(h.min(), Eq(9));
  h.delete_min();

  EXPECT_THAT(h.empty(), Eq(true));
}
