#include "hash_map/hash_map.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;
using testing::IsEmpty;
using testing::ElementsAre;

TEST(HashMapTest, Empty) {
  HashMap<int, int> m;

  EXPECT_THAT(m.empty(),    Eq(true));
  EXPECT_THAT(m.size(),     Eq(0));
  EXPECT_THAT(m.has_key(0), Eq(false));
  EXPECT_THAT(m.keys(),     IsEmpty());

  EXPECT_DEATH(m.get(0), "");
}

TEST(HashMapTest, OneElement) {
  HashMap<int, int> m;

  m.insert(0, 1);

  EXPECT_THAT(m.empty(),    Eq(false));
  EXPECT_THAT(m.size(),     Eq(1));
  EXPECT_THAT(m.has_key(0), Eq(true));
  EXPECT_THAT(m.keys(),     ElementsAre(0));
  EXPECT_THAT(m.get(0),     Eq(1));

  m.remove(0);

  EXPECT_THAT(m.empty(),    Eq(true));
  EXPECT_THAT(m.size(),     Eq(0));
  EXPECT_THAT(m.has_key(0), Eq(false));
  EXPECT_THAT(m.keys(),     IsEmpty());
}

TEST(HashMapTest, Replace) {
  HashMap<int, int> m;

  m.insert(0, 1);
  m.insert(0, 2);
  m.insert(0, 3);

  EXPECT_THAT(m.size(), Eq(1));
  EXPECT_THAT(m.keys(), ElementsAre(0));
  EXPECT_THAT(m.get(0), Eq(3));

  m.remove(0);

  EXPECT_THAT(m.empty(),    Eq(true));
  EXPECT_THAT(m.has_key(0), Eq(false));
  EXPECT_THAT(m.keys(),     IsEmpty());
}

TEST(HashMapTest, MoreElements) {
  const int N = 1024;

  HashMap<int, int> m;

  for (int i = 0; i < N; i++) {
    m.insert(i, i);
  }

  EXPECT_THAT(m.size(), Eq(N));
  for (int i = 0; i < N; i++) {
    EXPECT_THAT(m.has_key(i), Eq(true));
    EXPECT_THAT(m.get(i),     Eq(i));
  }

  for (int i = 0; i < N; i++) {
    m.remove(i);
  }

  EXPECT_THAT(m.empty(), Eq(true));
  for (int i = 0; i < N; i++) {
    EXPECT_THAT(m.has_key(i), Eq(false));
  }
}
