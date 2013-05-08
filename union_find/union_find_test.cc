#include "union_find/union_find.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;

TEST(UnionFindTest, All) {
  UnionFind<int> uf;

  for (int i = -10; i < 10; i++) {
    EXPECT_THAT(uf.find_root(i), Eq(uf.find_root(i)));
    EXPECT_THAT(uf.find_root(i), Eq(i));
  }

  uf.union_sets(0, 1);
  EXPECT_THAT(uf.find_root(0), Eq(uf.find_root(1)));

  uf.union_sets(1, 2);
  uf.union_sets(3, 2);
  uf.union_sets(3, 4);
  uf.union_sets(5, 4);
  uf.union_sets(5, 6);
  EXPECT_THAT(uf.find_root(0), Eq(uf.find_root(6)));

  for (int i = -10; i < 9; i++) {
    uf.union_sets(i, i + 1);
  }

  for (int i = -10; i < 10; i++) {
    for (int j = -10; j < 10; j++) {
      EXPECT_THAT(uf.find_root(i), Eq(uf.find_root(j)));
    }
  }
}
