#include "simpletest_test_macros.hpp"

#include "simpletest_unit_test.hpp"

namespace simpletest {
TestCase& RegisterTestCase(const char* suite_name,
                           const char* test_case_name,
                           TestCase::Function test_func) {
  return UnitTest::Get()
      .GetOrAddTestSuite(suite_name)
      .AddTestCase(test_case_name, test_func);
}

namespace internal {
void CheckTrueImpl(TestCase::Result& result,
                   bool value,
                   const char* file,
                   int line) {
  if (!value) {
    TestCase::Result::AddFailureLocation(result, FailureLocation{file, line});
  }
}

bool CheckStrEqImpl(std::string_view lhs, std::string_view rhs) {
  return lhs.compare(rhs) == 0;
}

bool CheckStrEqImpl(std::wstring_view lhs, std::wstring_view rhs) {
  return lhs.compare(rhs) == 0;
}
#if defined(__cpp_char8_t)
bool CheckStrEqImpl(std::u8string_view lhs, std::u8string_view rhs) {
  return lhs.compare(rhs) == 0;
}
#endif
bool CheckStrEqImpl(std::u16string_view lhs, std::u16string_view rhs) {
  return lhs.compare(rhs) == 0;
}
bool CheckStrEqImpl(std::u32string_view lhs, std::u32string_view rhs) {
  return lhs.compare(rhs) == 0;
}
}  // namespace internal
}  // namespace simpletest