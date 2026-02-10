#include <simpletest/simpletest.hpp>

int Add(int a, int b) {
  return a + b;
}

TEST_CASE(Math, Comparision) {
  const int a = 1;
  const int b = 4;
  const int c = 1;

  CHECK_EQ(a, c);
  CHECK_NE(b, c);
  CHECK_LT(a, b);
  CHECK_GT(b, a);
  CHECK_LE(a, c);
  CHECK_LE(a, b);
  CHECK_GE(b, a);
  CHECK_GE(c, a);
}

TEST_CASE(Math, Add) {
  CHECK_TRUE(Add(1, 2) == 3);
  CHECK_FALSE(Add(1, 2) != 3);
}