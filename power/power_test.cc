#include "power/power.h"

#include <cmath>
#include <functional>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using testing::Eq;

TEST(PowerTest, NegetiveExponent) {
  EXPECT_DEATH(power(0, -1, 0, std::plus<int>()), "");
}

TEST(PowerTest, Multiply) {
  for (int i = 0; i < 20; i++) {
    EXPECT_THAT(power(2, i, 0, std::plus<int>()), Eq(2 * i));
  }
}

TEST(PowerTest, Power) {
  for (int i = 0; i < 20; i++) {
    EXPECT_THAT(power(2, i, 1, std::multiplies<int>()), Eq(pow(2, i)));
  }
}
