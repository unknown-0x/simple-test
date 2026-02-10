#include <simpletest/simpletest.hpp>

TEST_CASE(FloatingPoint, CheckNear_Float) {
  const float kEpsilon = 0.001f;

  CHECK_NEAR(1.0f, 1.0f, kEpsilon);
  CHECK_NEAR(1.0f, 1.0009f, kEpsilon);
  CHECK_NEAR(1.0f, 0.9991f, kEpsilon);
  CHECK_NEAR(1.0f, 1.001f, kEpsilon);
  CHECK_NOT_NEAR(1.0f, 1.002f, kEpsilon);
  CHECK_NOT_NEAR(1.0f, 0.998f, kEpsilon);
}

TEST_CASE(FloatingPoint, CheckNear_Double) {
  const double kEpsilon = 0.001;

  CHECK_NEAR(1.0, 1.0, kEpsilon);
  CHECK_NEAR(1.0, 1.0009, kEpsilon);
  CHECK_NEAR(1.0, 0.9991, kEpsilon);
  CHECK_NEAR(1.0, 1.001, kEpsilon);
  CHECK_NOT_NEAR(1.0, 1.002, kEpsilon);
  CHECK_NOT_NEAR(1.0, 0.998, kEpsilon);
}

TEST_CASE(FloatingPoint, CheckNear_LongDouble) {
  const long double kEpsilon = 0.001;

  CHECK_NEAR((long double)1.0, (long double)1.0, kEpsilon);
  CHECK_NEAR((long double)1.0, (long double)1.0009, kEpsilon);
  CHECK_NEAR((long double)1.0, (long double)0.9991, kEpsilon);
  CHECK_NEAR((long double)1.0, (long double)1.001, kEpsilon);
  CHECK_NOT_NEAR((long double)1.0, (long double)1.002, kEpsilon);
  CHECK_NOT_NEAR((long double)1.0, (long double)0.998, kEpsilon);
}

TEST_CASE(FloatingPoint, HandlesNegativeValues_Float) {
  CHECK_NEAR(-1.0f, -1.0001f, 0.001f);
  CHECK_NOT_NEAR(-1.0f, -1.1f, 0.001f);
}

TEST_CASE(FloatingPoint, HandlesNegativeValues_Double) {
  CHECK_NEAR(-1.0, -1.0001, 0.001);
  CHECK_NOT_NEAR(-1.0, -1.1, 0.001);
}

TEST_CASE(FloatingPoint, HandlesNegativeValues_LongDouble) {
  CHECK_NEAR((long double)-1.0, (long double)-1.0001, (long double)0.001);
  CHECK_NOT_NEAR((long double)-1.0, (long double)-1.1, (long double)0.001);
}