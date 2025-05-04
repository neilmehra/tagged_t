#include "../include/tagged_t.h"
#include <gtest/gtest.h>
#include <sstream>
#include <unordered_set>

MAKE_TAGGED(Id, int)
MAKE_TAGGED(Count, std::size_t)

TEST(TaggedBasic, ConstructionAndGet) {
  Id x{42};
  Count c{100u};

  EXPECT_EQ(static_cast<int>(x), 42);
  EXPECT_EQ(c.get(), 100u);
}

TEST(TaggedOps, IncrementAndDecrement) {
  Count c{5u};
  ++c;
  EXPECT_EQ(c.get(), 6u);
  c++;
  EXPECT_EQ(c.get(), 7u);
  --c;
  EXPECT_EQ(c.get(), 6u);
  c--;
  EXPECT_EQ(c.get(), 5u);
}

TEST(TaggedArithmetic, BinaryOps) {
  Count a{3}, b{4};
  auto sum = a + b;
  auto diff = b - a;
  EXPECT_EQ(sum.get(), 7u);
  EXPECT_EQ(diff.get(), 1u);

  sum += a;
  EXPECT_EQ(sum.get(), 10u);

  diff *= Count{2};
  EXPECT_EQ(diff.get(), 2u);
}

TEST(TaggedComparison, EqualityAndThreeWay) {
  Id a{10}, b{20}, c{10};
  EXPECT_TRUE(a == c);
  EXPECT_FALSE(a == b);
  EXPECT_LT(a, b);
  EXPECT_GT(b, a);
}

TEST(TaggedHash, UnorderedSet) {
  std::unordered_set<Id> ids;
  ids.insert(Id{1});
  ids.insert(Id{2});
  ids.insert(Id{1}); // duplicate
  EXPECT_EQ(ids.size(), 2u);
}

TEST(TaggedIO, StreamOperators) {
  std::stringstream ss;
  Id x{7};
  ss << x;
  Id y{0};
  ss >> y;
  EXPECT_EQ(y.get(), 7);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
