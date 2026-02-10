#ifndef SIMPLETEST_SIMPLETEST_TEST_RUNNER_HPP_
#define SIMPLETEST_SIMPLETEST_TEST_RUNNER_HPP_

#include "simpletest_test_suite.hpp"
#include "simpletest_utils.hpp"

namespace simpletest {
class Reporter;
class SIMPLETEST_API TestRunner {
 public:
  TestRunner(const std::vector<TestSuite>& test_suites, Reporter* reporter);

  void RunAllTests();

 private:
  void ProcessTestSuite(const TestSuite& test_suite);
  void ProcessTestCase(const TestCase& test_case);

  const std::vector<TestSuite>& test_suites_;
  Reporter* reporter_;
  TestSummary summary_{};
};
}  // namespace simpletest

#endif