#include "simpletest_test_suite.hpp"

#include <cassert>
#include <cstring>

namespace simpletest {
TestSuite::TestSuite(const char* name) : test_cases_{}, name_(name) {}

TestCase& TestSuite::AddTestCase(const char* name, TestCase::Function func) {
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
}  // namespace simpletest