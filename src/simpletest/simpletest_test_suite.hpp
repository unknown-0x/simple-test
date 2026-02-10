#ifndef SIMPLETEST_SIMPLETEST_TEST_SUITE_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_SUITE_HPP_

#include "simpletest_test_case.hpp"

namespace simpletest {
class SIMPLETEST_API TestSuite {
 public:
  TestSuite(const char* name);
  ~TestSuite() = default;

  TestCase& AddTestCase(const char* name, TestCase::Function func);

  const std::vector<TestCase>& GetTestCases() const { return test_cases_; }
  const char* GetName() const { return name_; }

 private:
  std::vector<TestCase> test_cases_;
  const char* name_;
};
}  // namespace simpletest

#endif