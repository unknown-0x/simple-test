#ifndef SIMPLETEST_SIMPLETEST_TEST_SUITE_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_SUITE_HPP_

#include "simpletest_test_case.hpp"

#include <cassert>
#include <cstring>

namespace simpletest {
class TestSuite {
 public:
  TestSuite(const char* name) : test_cases_{}, name_(name) {}
  ~TestSuite() = default;

  TestCase& AddTestCase(const char* name, TestCase::Function func) {
    bool found = false;
    for (auto& test_case : test_cases_) {
      if (strcmp(test_case.GetName(), name) == 0) {
        found = true;
      }
    }
    assert(!found);

    test_cases_.emplace_back(name, func);
    return test_cases_.back();
  }

  const std::vector<TestCase>& GetTestCases() const noexcept {
    return test_cases_;
  }
  std::vector<TestCase>& GetTestCases() noexcept { return test_cases_; }
  const char* GetName() const noexcept { return name_; }

 private:
  std::vector<TestCase> test_cases_;
  const char* name_;
};
}  // namespace simpletest

#endif