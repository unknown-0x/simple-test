#ifndef SIMPLETEST_SIMPLETEST_TEST_MACROS_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_MACROS_HPP_

#include "simpletest_test_suite.hpp"

#include <cmath>
#include <string_view>

namespace simpletest {
namespace internal {
template <typename Fixture>
void RunTestFixture(TestCase::Result& result) {
  Fixture fixture{};
  fixture.Run(result);
}

SIMPLETEST_API void CheckTrueImpl(TestCase::Result& result,
                                  bool value,
                                  const char* file,
                                  int line);

SIMPLETEST_API bool CheckStrEqImpl(std::string_view lhs, std::string_view rhs);
SIMPLETEST_API bool CheckStrEqImpl(std::wstring_view lhs,
                                   std::wstring_view rhs);
#if defined(__cpp_char8_t)
SIMPLETEST_API bool CheckStrEqImpl(std::u8string_view lhs,
                                   std::u8string_view rhs);
#endif
SIMPLETEST_API bool CheckStrEqImpl(std::u16string_view lhs,
                                   std::u16string_view rhs);
SIMPLETEST_API bool CheckStrEqImpl(std::u32string_view lhs,
                                   std::u32string_view rhs);

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

SIMPLETEST_API TestCase& RegisterTestCase(const char* suite_name,
                                          const char* test_case_name,
                                          TestCase::Function test_func);
}  // namespace simpletest

#define SIMPLETEST_RESULT_NAME __test_case_result__

#define TEST_CASE(suite_name, test_case_name)                             \
  void Test##suite_name##test_case_name(::simpletest::TestCase::Result&); \
  static ::simpletest::TestCase& TestCase##suite_name##test_case_name =   \
      ::simpletest::RegisterTestCase(#suite_name, #test_case_name,        \
                                     Test##suite_name##test_case_name);   \
  void Test##suite_name##test_case_name(                                  \
      ::simpletest::TestCase::Result& SIMPLETEST_RESULT_NAME)

#define TEST_FIXTURE(fixture_name, test_case_name)                        \
  class Fixture##fixture_name##test_case_name : public fixture_name {     \
   public:                                                                \
    void Run(::simpletest::TestCase::Result&);                            \
  };                                                                      \
  static ::simpletest::TestCase& TestCase##fixture_name##test_case_name = \
      ::simpletest::RegisterTestCase(                                     \
          #fixture_name, #test_case_name,                                 \
          ::simpletest::internal::RunTestFixture<                         \
              Fixture##fixture_name##test_case_name>);                    \
  void Fixture##fixture_name##test_case_name::Run(                        \
      ::simpletest::TestCase::Result& SIMPLETEST_RESULT_NAME)

#define CHECK_TRUE(...)                                                      \
  ::simpletest::internal::CheckTrueImpl(SIMPLETEST_RESULT_NAME, __VA_ARGS__, \
                                        __FILE__, __LINE__);
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

#endif