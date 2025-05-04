#include "../include/tagged_t.h"
#include <gtest/gtest.h>

TEST(tagged_t, Test) {
  MAKE_TAGGED(SpecialInt, int);
  SpecialInt foo{10};
  foo++;
  ++foo;
  foo--;
  --foo;
  EXPECT_EQ(foo.get(), 10);

  SpecialInt bar{10};

  EXPECT_TRUE(foo == bar);

  auto moo = foo + bar;
  auto loo = moo - SpecialInt{1};
  loo++;
  EXPECT_TRUE(moo == loo);

  int test_conv = moo;
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
