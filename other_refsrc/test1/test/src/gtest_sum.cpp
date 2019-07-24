#include <stdio.h>
#include <gtest/gtest.h>

#include "sum.h"

TEST(test_suit_example1, addtest1) {
  EXPECT_EQ(2, sum(1,1));
}

TEST(test_suit_example1, addtest2) 
{
  EXPECT_EQ(5, sum(2,3));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
