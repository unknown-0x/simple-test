#ifndef SIMPLETEST_SIMPLETEST_TEST_MACROS_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_MACROS_HPP_

#include "simpletest_test_suite.hpp"
#include "simpletest_unit_test.hpp"

#include <cmath>
#include <string_view>

namespace simpletest {
namespace internal {
template <typename Fixture>
void RunTestFixture() {
  Fixture fixture{};
  fixture.Run();
}

inline void CheckTrueImpl(bool value, const char* file, int line) {
  if (!value) {
    TestCase::Result::AddFailureLocation(
        UnitTest::Get().GetCurrentTestCase().GetResult(),
        FailureLocation{file, line});
  }
}

inline bool CheckStrEqImpl(std::string_view lhs, std::string_view rhs) {
  return lhs.compare(rhs) == 0;
}

inline bool CheckStrEqImpl(std::wstring_view lhs, std::wstring_view rhs) {
  return lhs.compare(rhs) == 0;
}

#if defined(__cpp_char8_t)
inline bool CheckStrEqImpl(std::u8string_view lhs, std::u8string_view rhs) {
  return lhs.compare(rhs) == 0;
}
#endif

inline bool CheckStrEqImpl(std::u16string_view lhs, std::u16string_view rhs) {
  return lhs.compare(rhs) == 0;
}

inline bool CheckStrEqImpl(std::u32string_view lhs, std::u32string_view rhs) {
  return lhs.compare(rhs) == 0;
}

template <typename Float>
bool CheckNearImpl(Float lhs, Float rhs, Float epsilon) {
  Float diff = std::abs(lhs - rhs);
  if (diff <= epsilon) {
    return true;
  }

  lhs = std::abs(lhs);
  rhs = std::abs(rhs);
  Float largest = (rhs > lhs) ? rhs : lhs;

  return diff <= (largest * epsilon);
}
}  // namespace internal

inline TestCase& RegisterTestCase(const char* suite_name,
                                  const char* test_case_name,
                                  TestCase::Function test_func) {
  return UnitTest::Get()
      .GetOrAddTestSuite(suite_name)
      .AddTestCase(test_case_name, test_func);
}
}  // namespace simpletest

#define TEST_CASE(suite_name, test_case_name)                           \
  void Test##suite_name##test_case_name();                              \
  static ::simpletest::TestCase& TestCase##suite_name##test_case_name = \
      ::simpletest::RegisterTestCase(#suite_name, #test_case_name,      \
                                     Test##suite_name##test_case_name); \
  void Test##suite_name##test_case_name()

#define TEST_FIXTURE(fixture_name, test_case_name)                        \
  class Fixture##fixture_name##test_case_name : public fixture_name {     \
   public:                                                                \
    void Run();                                                           \
  };                                                                      \
  static ::simpletest::TestCase& TestCase##fixture_name##test_case_name = \
      ::simpletest::RegisterTestCase(                                     \
          #fixture_name, #test_case_name,                                 \
          ::simpletest::internal::RunTestFixture<                         \
              Fixture##fixture_name##test_case_name>);                    \
  void Fixture##fixture_name##test_case_name::Run()

#define CHECK_TRUE(...) \
  ::simpletest::internal::CheckTrueImpl(__VA_ARGS__, __FILE__, __LINE__);
#define CHECK_FALSE(...) CHECK_TRUE(!(__VA_ARGS__))

#define CHECK_EQ(lhs, rhs) CHECK_TRUE(lhs == rhs)
#define CHECK_NE(lhs, rhs) CHECK_TRUE(lhs != rhs)
#define CHECK_LT(lhs, rhs) CHECK_TRUE(lhs < rhs)
#define CHECK_GT(lhs, rhs) CHECK_TRUE(lhs > rhs)
#define CHECK_LE(lhs, rhs) CHECK_TRUE(lhs <= rhs)
#define CHECK_GE(lhs, rhs) CHECK_TRUE(lhs >= rhs)

#define CHECK_STR_EQ(lhs, rhs) \
  CHECK_TRUE(::simpletest::internal::CheckStrEqImpl(lhs, rhs))
#define CHECK_STR_NE(lhs, rhs) \
  CHECK_TRUE(!::simpletest::internal::CheckStrEqImpl(lhs, rhs))

#define CHECK_NEAR(lhs, rhs, epsilon) \
  CHECK_TRUE(::simpletest::internal::CheckNearImpl(lhs, rhs, epsilon))

#define CHECK_NOT_NEAR(lhs, rhs, epsilon) \
  CHECK_TRUE(!::simpletest::internal::CheckNearImpl(lhs, rhs, epsilon))

#define SIMPLETEST_CONCAT_IMPL(x, y) x##y
#define SIMPLETEST_CONCAT(x, y) SIMPLETEST_CONCAT_IMPL(x, y)

#define CHECK_THROWS(...)                         \
  do {                                            \
    bool AXIO_CONCAT(__threw_, __LINE__) = false; \
    try {                                         \
      __VA_ARGS__;                                \
    } catch (...) {                               \
      AXIO_CONCAT(__threw_, __LINE__) = true;     \
    }                                             \
    CHECK(AXIO_CONCAT(__threw_, __LINE__));       \
  } while (false)

#define CHECK_THROWS_AS(exception_type, ...)      \
  do {                                            \
    bool AXIO_CONCAT(__threw_, __LINE__) = false; \
    try {                                         \
      __VA_ARGS__;                                \
    } catch (const exception_type&) {             \
      AXIO_CONCAT(__threw_, __LINE__) = true;     \
    } catch (...) {                               \
    }                                             \
    CHECK(AXIO_CONCAT(__threw_, __LINE__));       \
  } while (false)

#define SIMPLETEST_MAIN()                             \
  int main(int argc, char** argv) {                   \
    (void)argc;                                       \
    (void)argv;                                       \
    return simpletest::UnitTest::Get().RunAllTests(); \
  }

#endif