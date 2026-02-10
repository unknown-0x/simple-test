#include <simpletest/simpletest.hpp>

#include <vector>

class Vector {
 public:
  Vector() : vec{1, 2, 3} {}

  void Clear() { vec.clear(); }

  std::vector<int> vec;
};

TEST_FIXTURE(Vector, InitialSize) {
  CHECK_EQ(vec.size(), 3);
}

TEST_FIXTURE(Vector, IsNotEmpty) {
  CHECK_FALSE(vec.empty());
}

TEST_FIXTURE(Vector, PushBack) {
  vec.push_back(4);
  CHECK_EQ(vec[0], 1);
  CHECK_EQ(vec[1], 2);
  CHECK_EQ(vec[2], 3);
  CHECK_EQ(vec[3], 4);
}

TEST_FIXTURE(Vector, Clear) {
  Clear();
  CHECK_TRUE(vec.empty());
}